// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

using global::System;
using global::FlatBuffers;

public struct fEquipSome : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static fEquipSome GetRootAsfEquipSome(ByteBuffer _bb) { return GetRootAsfEquipSome(_bb, new fEquipSome()); }
  public static fEquipSome GetRootAsfEquipSome(ByteBuffer _bb, fEquipSome obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public fEquipSome __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public Class CType { get { int o = __p.__offset(4); return o != 0 ? (Class)__p.bb.GetInt(o + __p.bb_pos) : Class.Base; } }
  public int PID { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int ObjNum { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int SlotNum { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<fEquipSome> CreatefEquipSome(FlatBufferBuilder builder,
      Class cType = Class.Base,
      int pID = 0,
      int objNum = 0,
      int slotNum = 0) {
    builder.StartObject(4);
    fEquipSome.AddSlotNum(builder, slotNum);
    fEquipSome.AddObjNum(builder, objNum);
    fEquipSome.AddPID(builder, pID);
    fEquipSome.AddCType(builder, cType);
    return fEquipSome.EndfEquipSome(builder);
  }

  public static void StartfEquipSome(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddCType(FlatBufferBuilder builder, Class cType) { builder.AddInt(0, (int)cType, 0); }
  public static void AddPID(FlatBufferBuilder builder, int pID) { builder.AddInt(1, pID, 0); }
  public static void AddObjNum(FlatBufferBuilder builder, int objNum) { builder.AddInt(2, objNum, 0); }
  public static void AddSlotNum(FlatBufferBuilder builder, int slotNum) { builder.AddInt(3, slotNum, 0); }
  public static Offset<fEquipSome> EndfEquipSome(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<fEquipSome>(o);
  }
};

