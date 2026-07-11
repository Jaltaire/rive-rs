#pragma once

#include "metal.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char metal[] = R"===(#ifndef _ARE_TOKEN_NAMES_PRESERVED
#define g half
#define G half2
#define A half3
#define i half4
#define c0 ushort
#define c float2
#define a0 float3
#define a4 packed_float3
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
#define e inline
#define j1(P1) thread P1&
#define i4(P1) thread P1&
#define equal(o,r) ((o)==(r))
#define notEqual(o,r) ((o)!=(r))
#define lessThan(o,r) ((o)<(r))
#define C0(o,r) ((o)*(r))
#define inversesqrt rsqrt
#define f5(d,a) struct a{
#define Y5(a) };
#define U0(a) struct a{
#define i0(d,X,a) X a
#define V0 };
#define l0(K7,B,a,X) X a=B[K7].a
#define n1 struct k0{
#define H(d,X,a) X a
#define K2 [[flat]]
#define n0 [[center_no_perspective]]
#ifndef PB
#define PB
#endif
#define o1 f f1[[position]][[invariant]];};
#define L(a,X) thread X&a=Y.a
#define Q(a)
#define O(a,X) X a=Y.a
#define E3 struct Q7{
#define F3 };
#define w3 struct J4{
#define x3 };
#define g4(d,e1,a) constant N0*a[[buffer(P0(d))]]
#define P3(d,e1,a) constant M*a[[buffer(P0(d))]]
#define h4(d,e1,a) constant f*a[[buffer(P0(d))]]
#define w0(a,v0) W1.a[v0]
#define k4(a,v0) W1.a[v0]
#define O2 struct R7{
#define P2 };
#define Q2 struct k3{
#define R2 };
#define p4 struct y6{
#define q4 };
#define I3(S,d,a) [[texture(d)]]texture2d<uint>a
#define r4(S,d,a) [[texture(d)]]texture2d<float>a
#define B2(S,d,a) [[texture(d)]]texture2d<g>a
#define z4(S,d,a) [[texture(d)]]texture2d<g>a
#define n5(S,d,a) [[texture(d)]]texture1d_array<g>a
#define Q3(E4,a) constexpr sampler a(filter::linear,mip_filter::none);
#define G3(S,d,a) [[sampler(d)]]sampler a;
#define x1(z0,l) K0.z0.read(N0(l))
#define F4(z0,p,l) K0.z0.sample(p,l)
#define T1(z0,p,l,G0) K0.z0.sample(p,l,level(G0))
#define r5(z0,p,l,W2) K0.z0.gather(p,(l)*(W2))
#define o4(z0,p,l) K0.z0.sample(K4.p,l)
#define y7(z0,p,l,G0) K0.z0.sample(K4.p,l,level(G0))
#define V5(z0,p,m,y5,N7,G0) K0.z0.sample(p,m,y5)
#define v5 ,constant WB&q,R7 K0,Q7 W1
#define Y1 ,q,K0,W1
#ifdef OD
#define p1(a,f0,B,n,K) __attribute__((visibility("default")))k0 vertex a(uint n[[vertex_id]],uint K[[instance_id]],constant uint&Fe[[buffer(P0(Ya))]],constant WB&q[[buffer(P0(K3))]],constant f0*B[[buffer(0)]],R7 K0,Q7 W1){K+=Fe;k0 Y;
#else
#define p1(a,f0,B,n,K) __attribute__((visibility("default")))k0 vertex a(uint n[[vertex_id]],uint K[[instance_id]],constant WB&q[[buffer(P0(K3))]],constant f0*B[[buffer(0)]],R7 K0,Q7 W1){k0 Y;
#endif
#define H6(a,f0,B,n,K) __attribute__((visibility("default")))k0 vertex a(uint n[[vertex_id]],constant WB&q[[buffer(P0(K3))]],constant FC&m0[[buffer(P0(g5))]],constant f0*B[[buffer(0)]],R7 K0,Q7 W1){k0 Y;
#define P4(a,a2,c2,r2,v2,n) __attribute__((visibility("default")))k0 vertex a(uint n[[vertex_id]],constant WB&q[[buffer(P0(K3))]],constant FC&m0[[buffer(P0(g5))]],constant a2*c2[[buffer(0)]],constant r2*v2[[buffer(1)]]){k0 Y;
#define g1(x6) Y.f1=x6;}return Y;
#define e2(G4,a) G4 __attribute__((visibility("default")))fragment a(k0 Y[[stage_in]],k3 K0){
#define f2(F) return F;}
#define E5 ,c B0,k3 K0,J4 W1,y6 K4
#define X2 ,B0,K0,W1,K4
#define p5 ,k3 K0
#define w1 ,K0
#ifdef LE
#define w2 struct z1{
#ifdef ME
#define I0(d,a) device uint*a[[buffer(P0(d+h5)),raster_order_group(0)]]
#define Y0(d,a) device uint*a[[buffer(P0(d+h5)),raster_order_group(0)]]
#define f4(d,a) device atomic_uint*a[[buffer(P0(d+h5)),raster_order_group(0)]]
#else
#define I0(d,a) device uint*a[[buffer(P0(d+h5))]]
#define Y0(d,a) device uint*a[[buffer(P0(d+h5))]]
#define f4(d,a) device atomic_uint*a[[buffer(P0(d+h5))]]
#endif
#define x2 };
#define y3 ,z1 E0,uint J2
#define G1 ,E0,J2
#define J0(h) unpackUnorm4x8(E0.h[J2])
#define i1(h) E0.h[J2]
#define m4(h) atomic_load_explicit(&E0.h[J2],memory_order::memory_order_relaxed)
#define T0(h,F) E0.h[J2]=packUnorm4x8(F)
#define k1(h,F) E0.h[J2]=(F)
#define n4(h,F) atomic_store_explicit(&E0.h[J2],F,memory_order::memory_order_relaxed)
#define C2(h)
#define i2(h)
#define I5(h,m) atomic_fetch_max_explicit(&E0.h[J2],m,memory_order::memory_order_relaxed)
#define J5(h,m) atomic_fetch_add_explicit(&E0.h[J2],m,memory_order::memory_order_relaxed)
#define h2
#define j2
#define z6(a) __attribute__((visibility("default")))fragment a(z1 E0,constant WB&q[[buffer(P0(K3))]],k0 Y[[stage_in]],k3 K0,y6 K4,J4 W1){c B0=Y.f1.xy;N0 I=N0(metal::floor(B0));uint J2=I.y*q.Ka+I.x;
#define Vb(a) __attribute__((visibility("default")))fragment a(z1 E0,constant WB&q[[buffer(P0(K3))]],constant FC&m0[[buffer(P0(g5))]],k0 Y[[stage_in]],y6 K4,k3 K0,J4 W1){c B0=Y.f1.xy;N0 I=N0(metal::floor(B0));uint J2=I.y*q.Ka+I.x;
#define y2(a) void z6(a)
#define S4(a) void Vb(a)
#define L2 }
#define A3(a) i z6(a){i K1;
#define H5(a) i Vb(a){i K1;
#define Q4 }return K1;L2
#else
#define w2 struct z1{
#define I0(d,a) [[color(d)]]i a
#define Y0(d,a) [[color(d)]]uint a
#define f4 Y0
#define x2 };
#define y3 ,thread z1&l3,thread z1&E0
#define G1 ,l3,E0
#define J0(h) l3.h
#define i1(h) l3.h
#define m4(h) i1
#define T0(h,F) E0.h=(F)
#define k1(h,F) E0.h=(F)
#define n4(h) k1
#define C2(h) E0.h=l3.h
#define i2(h) E0.h=l3.h
e uint v6(thread uint&h0,uint x){uint B1=h0;h0=metal::max(B1,x);return B1;}
#define I5(h,m) v6(E0.h,m)
e uint w6(thread uint&h0,uint x){uint B1=h0;h0=B1+x;return B1;}
#define J5(h,m) w6(E0.h,m)
#define h2
#define j2
#define z6(a,...) z1 __attribute__((visibility("default")))fragment a(__VA_ARGS__){c B0[[maybe_unused]]=Y.f1.xy;z1 E0;
#define y2(a,...) z6(a,z1 l3,constant WB&q[[buffer(P0(K3))]],k0 Y[[stage_in]],y6 K4,k3 K0,J4 W1)
#define S4(a) z6(a,z1 l3,k0 Y[[stage_in]],k3 K0,J4 W1,y6 K4,constant FC&m0[[buffer(P0(g5))]])
#define L2 }return E0;
#define Wb(a,...) struct Ge{i He[[j(0)]];z1 E0;};Ge __attribute__((visibility("default")))fragment a(__VA_ARGS__){c B0[[maybe_unused]]=Y.f1.xy;i K1;z1 E0;
#define A3(a) Wb(a,z1 l3,k0 Y[[stage_in]],k3 K0,J4 W1)
#define H5(a) Wb(a,z1 l3,k0 Y[[stage_in]],k3 K0,J4 W1,__VA_ARGS__ constant FC&m0[[buffer(P0(g5))]])
#define Q4 }return{.He=K1,.E0=E0};
#endif
#define q3 I0
#define discard discard_fragment()
using namespace metal;template<int y1>e vec<uint,y1>floatBitsToUint(vec<float,y1>x){return as_type<vec<uint,y1>>(x);}template<int y1>e vec<int,y1>floatBitsToInt(vec<float,y1>x){return as_type<vec<int,y1>>(x);}e uint floatBitsToUint(float x){return as_type<uint>(x);}e int floatBitsToInt(float x){return as_type<int>(x);}template<int y1>e vec<float,y1>uintBitsToFloat(vec<uint,y1>x){return as_type<vec<float,y1>>(x);}e float uintBitsToFloat(uint x){return as_type<float>(x);}e G unpackHalf2x16(uint x){return as_type<G>(x);}e uint packHalf2x16(G x){return as_type<uint>(x);}e i unpackUnorm4x8(uint x){return unpack_unorm4x8_to_half(x);}e uint packUnorm4x8(i x){return pack_half_to_unorm4x8(x);}e V inverse(V W0){V G9=V(W0[1][1],-W0[0][1],-W0[1][0],W0[0][0]);float Ie=(G9[0][0]*W0[0][0])+(G9[0][1]*W0[1][0]);return G9*(1/Ie);}e A mix(A k,A b,J7 A0){A A6;for(int C=0;C<3;++C)A6[C]=A0[C]?b[C]:k[C];return A6;}e c mix(c k,c b,c5 A0){c A6;for(int C=0;C<2;++C)A6[C]=A0[C]?b[C]:k[C];return A6;}e c mix(c k,c b,float t){return mix(k,b,c(t));}e float mod(float x,float y){return fmod(x,y);}
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive