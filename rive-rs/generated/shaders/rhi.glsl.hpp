#pragma once

#include "rhi.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char rhi[] = R"===(#pragma warning(disable:3550)
#pragma warning(disable:4000)
#ifndef _ARE_TOKEN_NAMES_PRESERVED
#define g half
#define G half2
#define A half3
#define i half4
#define c0 ushort
#define c float2
#define a0 float3
#define f float4
#define c5 bool2
#define J7 bool3
#define N0 uint2
#define M uint4
#define g0 int2
#define j7 int4
#define c0 ushort
#define V float2x2
#define W5 half3x3
#define X5 half2x3
#endif
typedef a0 a4;
#ifdef PD
#if Me
typedef min16uint c0;
#endif
#else
#if Me
typedef uint c0;
#endif
#endif
#define Xb(o,r) o##r
#define e inline
#define j1(P1) out P1
#define i4(P1) inout P1
#define U0(a) struct a{
#define i0(d,X,a) X a:Xb(Wf,d)
#define V0 };
#define l0(K7,B,a,X) X a=B.a
#define f5(d,a) cbuffer a{struct{
#define Y5(a) }a;}
#define n1 struct k0{
#define n0 noperspective
#define PB nointerpolation
#define K2 nointerpolation
#define H(d,X,a) X a:Xb(TEXCOORD,d)
#define o1 f f1:SV_Position;};
#define L(a,X) X a
#define Q(a) Y.a=a
#define O(a,X) X a=Y.a
#ifdef AB
#define O2
#define P2
#endif
#ifdef HB
#define Q2
#define R2
#endif
#define p4
#define q4
#define I3(S,d,a) uniform Texture2D<M>a
#define r4(S,d,a) uniform Texture2D<f>a
#define B2(S,d,a) uniform Texture2D<Ne i>a
#define z4(S,d,a) uniform Texture2D<g>a
#define n5(S,d,a) uniform Texture2DArray<g>a
#define H4(d,a) SamplerState a;
#define Q3 H4
#define G3(S,d,a) H4(d,a)
#define x1(a,l) a[l]
#define F4(a,p,l) a.Sample(p,l)
#define T1(a,p,l,G0) a.SampleLevel(p,l,G0)
#define r5(a,p,l,W2) a.Gather(p,(l)*(W2))
#define V5(a,p,m,y5,N7,G0) a.SampleLevel(p,a0(m,0.5,y5),G0)
#define o4(z0,p,l) F4(z0,p,l)
#define y7(z0,p,l,G0) T1(z0,p,l,G0)
#define h2
#define j2
#ifdef QD
#define m2 RasterizerOrderedTexture2D
#else
#define m2 RWTexture2D
#endif
#define w2
#ifdef GC
#define I0(d,a) uniform m2<Ne i>a
#else
#define I0(d,a) uniform m2<uint>a
#endif
#define q3 I0
#define Y0(d,a) uniform m2<uint>a
#define f4 Y0
#define m4 i1
#define n4 k1
#define x2
#ifdef GC
#define J0(h) h[I]
#else
#define J0(h) unpackUnorm4x8(h[I])
#endif
#define i1(h) h[I]
#ifdef GC
#define T0(h,F) h[I]=(F)
#else
#define T0(h,F) h[I]=packUnorm4x8(F)
#endif
#define k1(h,F) h[I]=(F)
e uint v6(m2<uint>I4,g0 I,uint x){uint B1;InterlockedMax(I4[I],x,B1);return B1;}
#define I5(h,m) v6(h,I,m)
e uint w6(m2<uint>I4,g0 I,uint x){uint B1;InterlockedAdd(I4[I],x,B1);return B1;}
#define J5(h,m) w6(h,I,m)
#define C2(h)
#define i2(h)
#define v5
#define Y1
#define p5
#define w1
#define p1(a,f0,B,n,K) uint baseInstance;k0 a(f0 B,uint n:SV_VertexID,uint E9:SV_InstanceID){uint K=E9+baseInstance;k0 Y;
#define H6(a,f0,B,n,K) k0 a(f0 B,uint n:SV_VertexID){k0 Y;f f1;
#define P4(a,a2,c2,r2,v2,n) k0 a(a2 c2,r2 v2,uint n:SV_VertexID){k0 Y;f f1;
#define g1(x6) Y.f1=x6;}return Y;
#define e2(G4,a) G4 a(k0 Y):SV_Target{
#define f2(F) return F;}
#define E5 ,c B0
#define X2 ,B0
#define y3 ,g0 I
#define G1 ,I
#define y2(a) Oe void a(k0 Y){c B0=Y.f1.xy;g0 I=g0(floor(B0));
#define S4(a) y2(a)
#define L2 }
#define A3(a) Oe i a(k0 Y):SV_Target{c B0=Y.f1.xy;g0 I=g0(floor(B0));i K1;
#define H5(a) A3(a)
#define Q4 }return K1;
#define uintBitsToFloat asfloat
#define floatBitsToInt asint
#define floatBitsToUint asuint
#define inversesqrt rsqrt
#define equal(o,r) ((o)==(r))
#define notEqual(o,r) ((o)!=(r))
#define lessThan(o,r) ((o)<(r))
#define C0(o,r) mul(r,o)
#define E3
#define F3
#define w3
#define x3
#define g4(d,e1,a) StructuredBuffer<N0>a
#define P3(d,e1,a) StructuredBuffer<M>a
#define h4(d,e1,a) StructuredBuffer<f>a
#define w0(a,v0) a[v0]
#define k4(a,v0) a[v0]
e G unpackHalf2x16(uint u){uint y=(u>>16);uint x=u&0xffffu;return G(f16tof32(x),f16tof32(y));}e uint packHalf2x16(c M1){uint x=f32tof16(M1.x);uint y=f32tof16(M1.y);return(y<<16)|x;}e i unpackUnorm4x8(uint u){M A1=M(u&0xffu,(u>>8)&0xffu,(u>>16)&0xffu,u>>24);return i(A1)*(1./255.);}e uint packUnorm4x8(i j){M A1=(M(j*255.)&0xff)<<M(0,8,16,24);A1.xy|=A1.zw;A1.x|=A1.y;return A1.x;}e V inverse(V W0){V F9=V(W0[1][1],-W0[0][1],-W0[1][0],W0[0][0]);return F9*(1./determinant(W0));}e float mix(float x,float y,float s){return lerp(x,y,s);}e c mix(c x,c y,c s){return lerp(x,y,s);}e a0 mix(a0 x,a0 y,a0 s){return lerp(x,y,s);}e f mix(f x,f y,f s){return lerp(x,y,s);}e float fract(float x){return frac(x);}e c fract(c x){return frac(x);}e a0 fract(a0 x){return frac(x);}e f fract(f x){return frac(x);}e float mod(float x,float y){return fmod(x,y);}e float n2(float x){return sign(x);}e c n2(c x){return sign(x);}e a0 n2(a0 x){return sign(x);}e f n2(f x){return sign(x);}
#define sign n2
e float o2(float x){return abs(x);}e c o2(c x){return abs(x);}e a0 o2(a0 x){return abs(x);}e f o2(f x){return abs(x);}
#define abs o2
e float p2(float x){return sqrt(x);}e c p2(c x){return sqrt(x);}e a0 p2(a0 x){return sqrt(x);}e f p2(f x){return sqrt(x);}
#define sqrt p2
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive