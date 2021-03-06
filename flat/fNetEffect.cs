// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

using global::System;
using global::FlatBuffers;

public struct fNetEffect : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static fNetEffect GetRootAsfNetEffect(ByteBuffer _bb) { return GetRootAsfNetEffect(_bb, new fNetEffect()); }
  public static fNetEffect GetRootAsfNetEffect(ByteBuffer _bb, fNetEffect obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public fNetEffect __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public Class CType { get { int o = __p.__offset(4); return o != 0 ? (Class)__p.bb.GetInt(o + __p.bb_pos) : Class.Base; } }
  public int EffectType { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int Target { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int TargetMonster { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public Vec3? TargetPos { get { int o = __p.__offset(12); return o != 0 ? (Vec3?)(new Vec3()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public Vec3? StartPos { get { int o = __p.__offset(14); return o != 0 ? (Vec3?)(new Vec3()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartfNetEffect(FlatBufferBuilder builder) { builder.StartObject(6); }
  public static void AddCType(FlatBufferBuilder builder, Class cType) { builder.AddInt(0, (int)cType, 0); }
  public static void AddEffectType(FlatBufferBuilder builder, int EffectType) { builder.AddInt(1, EffectType, 0); }
  public static void AddTarget(FlatBufferBuilder builder, int target) { builder.AddInt(2, target, 0); }
  public static void AddTargetMonster(FlatBufferBuilder builder, int targetMonster) { builder.AddInt(3, targetMonster, 0); }
  public static void AddTargetPos(FlatBufferBuilder builder, Offset<Vec3> targetPosOffset) { builder.AddStruct(4, targetPosOffset.Value, 0); }
  public static void AddStartPos(FlatBufferBuilder builder, Offset<Vec3> StartPosOffset) { builder.AddStruct(5, StartPosOffset.Value, 0); }
  public static Offset<fNetEffect> EndfNetEffect(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<fNetEffect>(o);
  }
};

