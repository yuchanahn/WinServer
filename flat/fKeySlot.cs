// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

using global::System;
using global::FlatBuffers;

public struct fKeySlot : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static fKeySlot GetRootAsfKeySlot(ByteBuffer _bb) { return GetRootAsfKeySlot(_bb, new fKeySlot()); }
  public static fKeySlot GetRootAsfKeySlot(ByteBuffer _bb, fKeySlot obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public fKeySlot __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public Class CType { get { int o = __p.__offset(4); return o != 0 ? (Class)__p.bb.GetInt(o + __p.bb_pos) : Class.Base; } }
  public int SlotNum(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.GetInt(__p.__vector(o) + j * 4) : (int)0; }
  public int SlotNumLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
  public ArraySegment<byte>? GetSlotNumBytes() { return __p.__vector_as_arraysegment(6); }

  public static Offset<fKeySlot> CreatefKeySlot(FlatBufferBuilder builder,
      Class cType = Class.Base,
      VectorOffset slotNumOffset = default(VectorOffset)) {
    builder.StartObject(2);
    fKeySlot.AddSlotNum(builder, slotNumOffset);
    fKeySlot.AddCType(builder, cType);
    return fKeySlot.EndfKeySlot(builder);
  }

  public static void StartfKeySlot(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddCType(FlatBufferBuilder builder, Class cType) { builder.AddInt(0, (int)cType, 0); }
  public static void AddSlotNum(FlatBufferBuilder builder, VectorOffset slotNumOffset) { builder.AddOffset(1, slotNumOffset.Value, 0); }
  public static VectorOffset CreateSlotNumVector(FlatBufferBuilder builder, int[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddInt(data[i]); return builder.EndVector(); }
  public static void StartSlotNumVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<fKeySlot> EndfKeySlot(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<fKeySlot>(o);
  }
};

