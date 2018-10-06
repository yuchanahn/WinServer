// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

using global::System;
using global::FlatBuffers;

public struct FirstCharacterData : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static FirstCharacterData GetRootAsFirstCharacterData(ByteBuffer _bb) { return GetRootAsFirstCharacterData(_bb, new FirstCharacterData()); }
  public static FirstCharacterData GetRootAsFirstCharacterData(ByteBuffer _bb, FirstCharacterData obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public FirstCharacterData __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public Class CType { get { int o = __p.__offset(4); return o != 0 ? (Class)__p.bb.GetInt(o + __p.bb_pos) : Class.Base; } }
  public Vec3? Pos { get { int o = __p.__offset(6); return o != 0 ? (Vec3?)(new Vec3()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public string Name { get { int o = __p.__offset(8); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
  public ArraySegment<byte>? GetNameBytes() { return __p.__vector_as_arraysegment(8); }
  public int HP { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int HPLim { get { int o = __p.__offset(12); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int MP { get { int o = __p.__offset(14); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int MPLim { get { int o = __p.__offset(16); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int EXP { get { int o = __p.__offset(18); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int Attack { get { int o = __p.__offset(20); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int LV { get { int o = __p.__offset(22); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int ID { get { int o = __p.__offset(24); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static void StartFirstCharacterData(FlatBufferBuilder builder) { builder.StartObject(11); }
  public static void AddCType(FlatBufferBuilder builder, Class cType) { builder.AddInt(0, (int)cType, 0); }
  public static void AddPos(FlatBufferBuilder builder, Offset<Vec3> PosOffset) { builder.AddStruct(1, PosOffset.Value, 0); }
  public static void AddName(FlatBufferBuilder builder, StringOffset NameOffset) { builder.AddOffset(2, NameOffset.Value, 0); }
  public static void AddHP(FlatBufferBuilder builder, int HP) { builder.AddInt(3, HP, 0); }
  public static void AddHPLim(FlatBufferBuilder builder, int HPLim) { builder.AddInt(4, HPLim, 0); }
  public static void AddMP(FlatBufferBuilder builder, int MP) { builder.AddInt(5, MP, 0); }
  public static void AddMPLim(FlatBufferBuilder builder, int MPLim) { builder.AddInt(6, MPLim, 0); }
  public static void AddEXP(FlatBufferBuilder builder, int EXP) { builder.AddInt(7, EXP, 0); }
  public static void AddAttack(FlatBufferBuilder builder, int Attack) { builder.AddInt(8, Attack, 0); }
  public static void AddLV(FlatBufferBuilder builder, int LV) { builder.AddInt(9, LV, 0); }
  public static void AddID(FlatBufferBuilder builder, int ID) { builder.AddInt(10, ID, 0); }
  public static Offset<FirstCharacterData> EndFirstCharacterData(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<FirstCharacterData>(o);
  }
};

