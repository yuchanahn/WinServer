

//ASE
#include <modes.h>
#include <filters.h>
#include <aes.h>

//RSA
#include <cryptlib.h>
#include <integer.h>
#include <nbtheory.h>
#include <osrng.h>
#include <rsa.h>
#include <sha.h>

//SHA256
#include <sha.h>
#include <filters.h>
#include <base64.h>

//MD5
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>

#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::runtime_error;

#if CRYPTOPP_MSC_VERSION
# pragma warning(disable: 4505 4355)
#endif



using namespace CryptoPP;

void _AES() {
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    std::string plaintext = "Now is the time for all good men to come to the aide...";
    std::string ciphertext;
    std::string decryptedtext;

    std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
    std::cout << plaintext;
    std::cout << std::endl << std::endl;

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption
            , new CryptoPP::StringSink(ciphertext));

    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str())
                     , plaintext.length() + 1);
    stfEncryptor.MessageEnd();

    std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;

    for (int i = 0; i < ciphertext.size(); i++) {

        std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
    }

    std::cout << std::endl << std::endl;

    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption
            , new CryptoPP::StringSink(decryptedtext));

    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
    stfDecryptor.MessageEnd();

    //
    // Dump Decrypted Text
    //
    std::cout << "Decrypted Text: " << std::endl;
    std::cout << decryptedtext;
    std::cout << std::endl << std::endl;
}

void _RSA() {
    // Bob artificially small key pair
    AutoSeededRandomPool prng;
    RSA::PrivateKey privKey;

    privKey.GenerateRandomWithKeySize(prng, 64);
    RSA::PublicKey pubKey(privKey);

    // Convenience
    const Integer& n = pubKey.GetModulus();
    const Integer& e = pubKey.GetPublicExponent();
    const Integer& d = privKey.GetPrivateExponent();

    // Print params
    cout << "Pub mod: " << std::hex << pubKey.GetModulus() << endl;
    cout << "Pub exp: " << std::hex << e << endl;
    cout << "Priv mod: " << std::hex << privKey.GetModulus() << endl;
    cout << "Priv exp: " << std::hex << d << endl;

    // For sizing the hashed message buffer. This should be SHA256 size.
    const size_t SIG_SIZE = UnsignedMin(SHA256::BLOCKSIZE, n.ByteCount());

    // Scratch
    SecByteBlock buff1, buff2, buff3;

    // Alice original message to be signed by Bob
    SecByteBlock orig((const byte*)"secret", 6);
    Integer m(orig.data(), orig.size());
    cout << "Message: " << std::hex << m << endl;

    // Hash message per Rabin (1979)
    buff1.resize(SIG_SIZE);
    SHA256 hash1;
    hash1.CalculateTruncatedDigest(buff1, buff1.size(), orig, orig.size());

    // H(m) as Integer
    Integer hm(buff1.data(), buff1.size());
    cout << "H(m): " << std::hex << hm << endl;

    // Alice blinding
    Integer r;
    do {
        r.Randomize(prng, Integer::One(), n - Integer::One());
    } while (!RelativelyPrime(r, n));

    // Blinding factor
    Integer b = a_exp_b_mod_c(r, e, n);
    cout << "Random: " << std::hex << b << endl;

    // Alice blinded message
    Integer mm = a_times_b_mod_c(hm, b, n);
    cout << "Blind msg: " << std::hex << mm << endl;

    // Bob sign
    Integer ss = privKey.CalculateInverse(prng, mm);
    cout << "Blind sign: " << ss << endl;

    // Alice checks s(s'(x)) = x. This is from Chaum's paper
    Integer c = pubKey.ApplyFunction(ss);
    cout << "Check sign: " << c << endl;
    if (c != mm)
        throw runtime_error("Alice cross-check failed");

    // Alice remove blinding
    Integer s = a_times_b_mod_c(ss, r.InverseMod(n), n);
    cout << "Unblind sign: " << s << endl;

    // Eve verifies
    Integer v = pubKey.ApplyFunction(s);
    cout << "Verify: " << std::hex << v << endl;

    // Convert to a string
    size_t req = v.MinEncodedSize();
    buff2.resize(req);
    v.Encode(&buff2[0], buff2.size());

    // Hash message per Rabin (1979)
    buff3.resize(SIG_SIZE);
    SHA256 hash2;
    hash2.CalculateTruncatedDigest(buff3, buff3.size(), orig, orig.size());

    // Constant time compare
    bool equal = buff2.size() == buff3.size() && VerifyBufsEqual(
                     buff2.data(), buff3.data(), buff3.size());

    if (!equal)
        throw runtime_error("Eve verified failed");

    cout << "Verified signature" << endl;
}

std::string SHA256HashString(std::string aString) {
    std::string digest;
    CryptoPP::SHA256 hash;

    CryptoPP::StringSource foo(aString, true
                               , new CryptoPP::HashFilter(hash
                                       , new CryptoPP::Base64Encoder(new CryptoPP::StringSink(digest))));

    return digest;
}

void _MD5() {
    byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];
    std::string message = "foobarbat";

    CryptoPP::Weak::MD5 hash;
    hash.CalculateDigest(digest, (byte*)message.c_str(), message.length());

    CryptoPP::HexEncoder encoder;
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    cout << output;
}

int main2() {
    _MD5();

    return 0;
}