#pragma once

#include "glsl.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char glsl[] = R"===(#define Da
#ifndef XB
#define XB __VERSION__
#endif
#define c vec2
#define a0 vec3
#define a4 vec3
#define f vec4
#define g mediump float
#define G mediump vec2
#define A mediump vec3
#define i mediump vec4
#define W5 mediump mat3x3
#define X5 mediump mat2x3
#define g0 ivec2
#define j7 ivec4
#define N0 uvec2
#define M uvec4
#define c0 mediump uint
#define c5 bvec2
#define J7 bvec3
#define V mat2
#define e
#define j1(P1) out P1
#define i4(P1) inout P1
#ifdef GL_ANGLE_base_vertex_base_instance_shader_builtin
#extension GL_ANGLE_base_vertex_base_instance_shader_builtin:require
#endif
#ifdef KD
#extension GL_KHR_blend_equation_advanced:require
#endif
#if defined(CB)&&defined(BB)&&defined(GL_ES)
#ifdef GL_EXT_clip_cull_distance
#extension GL_EXT_clip_cull_distance:require
#elif defined(GL_ANGLE_clip_cull_distance)
#extension GL_ANGLE_clip_cull_distance:require
#endif
#endif
#if XB>=310
#define f5(d,a) layout(binding=d,std140)uniform a{
#else
#define f5(d,a) layout(std140)uniform a{
#endif
#define Y5(a) }a;
#define U0(a)
#define i0(d,X,a) layout(location=d)in X a
#define V0
#define l0(K7,B,a,X)
#ifdef AB
#if XB>=310
#define H(d,X,a) layout(location=d)out X a
#else
#define H(d,X,a) out X a
#endif
#else
#if XB>=310
#define H(d,X,a) layout(location=d)in X a
#else
#define H(d,X,a) in X a
#endif
#endif
#define K2 flat
#define n1
#define o1
#ifdef YB
#define n0
#else
#ifdef GL_NV_shader_noperspective_interpolation
#extension GL_NV_shader_noperspective_interpolation:require
#define n0 noperspective
#else
#define n0
#endif
#endif
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
#ifdef YB
#define I3(S,d,a) layout(set=S,binding=d)uniform highp utexture2D a
#define r4(S,d,a) layout(set=S,binding=d)uniform highp texture2D a
#define B2(S,d,a) layout(set=S,binding=d)uniform mediump texture2D a
#define z4(S,d,a) layout(binding=d)uniform mediump texture2D a
#if defined(HB)&&defined(CB)
#define r7(a) layout(input_attachment_index=0,binding=L6,set=i5)uniform lowp subpassInputMS a
#endif
#elif XB>=310
#define I3(S,d,a) layout(binding=d)uniform highp usampler2D a
#define r4(S,d,a) layout(binding=d)uniform highp sampler2D a
#define B2(S,d,a) layout(binding=d)uniform mediump sampler2D a
#define z4(S,d,a) layout(binding=d)uniform mediump sampler2D a
#define r7(a) B2(T2,db,a)
#else
#define I3(S,d,a) uniform highp usampler2D a
#define r4(S,d,a) uniform highp sampler2D a
#define B2(S,d,a) uniform mediump sampler2D a
#define z4(S,d,a) uniform mediump sampler2D a
#define r7(a) B2(T2,db,a)
#endif
#ifdef YB
#define Q3(E4,a) layout(set=eb,binding=E4)uniform mediump sampler a;
#define G3(S,d,a) layout(set=S,binding=d)uniform mediump sampler a;
#define F4(a,p,l) texture(sampler2D(a,p),l)
#define T1(a,p,l,G0) textureLod(sampler2D(a,p),l,G0)
#if defined(HB)&&defined(CB)
#extension GL_OES_sample_variables:require
#define i9(a) Ae(mat4(subpassLoad(a,0),subpassLoad(a,1),subpassLoad(a,2),subpassLoad(a,3)))
#endif
#else
#define Q3(E4,a)
#define G3(S,d,a)
#define F4(a,p,l) texture(a,l)
#define T1(a,p,l,G0) textureLod(a,l,G0)
#define i9(a) texelFetch(a,ivec2(floor(B0.xy)),0)
#endif
#define o4(z0,p,l) F4(z0,p,l)
#define y7(z0,p,l,G0) T1(z0,p,l,G0)
#define n5(S,d,a) z4(S,d,a)
#define V5(a,p,m,y5,N7,G0) T1(a,p,c(m,N7),G0)
#define Be(S,d,a) I3(S,d,a)
#define p5
#define w1
#define x1(a,l) texelFetch(a,l,0)
#ifdef YB
#define r5(a,p,l,W2) textureGather(sampler2D(a,p),(l)*(W2))
#elif XB>=310
#define r5(a,p,l,W2) textureGather(a,(l)*(W2))
#else
#define r5(a,p,l,W2) E1(x1(a,g0(l)+g0(-1,0)).x,x1(a,g0(l)+g0(0,0)).x,x1(a,g0(l)+g0(0,-1)).x,x1(a,g0(l)+g0(-1,-1)).x)
#endif
#define E3
#define F3
#define w3
#define x3
#ifdef FE
#define g4(d,e1,a) I3(T2,d,a)
#define P3(d,e1,a) Be(T2,d,a)
#define h4(d,e1,a) r4(T2,d,a)
#define w0(a,v0) x1(a,g0((v0)&Sa,(v0)>>Ra))
#define k4(a,v0) x1(a,g0((v0)&Sa,(v0)>>Ra)).xy
#else
#ifdef GL_ARB_shader_storage_buffer_object
#extension GL_ARB_shader_storage_buffer_object:require
#endif
#define g4(d,e1,a) layout(std430,binding=d)readonly buffer e1{N0 V3[];}a
#define P3(d,e1,a) layout(std430,binding=d)readonly buffer e1{M V3[];}a
#define h4(d,e1,a) layout(std430,binding=d)readonly buffer e1{f V3[];}a
#define Md(d,e1,a) layout(std430,binding=d)buffer e1{uint V3[];}a
#define w0(a,v0) a.V3[v0]
#define k4(a,v0) a.V3[v0]
#define Sd(a,v0) a.V3[v0]
#define f9(a,v0,m) atomicMax(a.V3[v0],m)
#define ib(a,v0,m) atomicAdd(a.V3[v0],m)
#endif
#ifdef _EXPORTED_PLS_IMPL_ANGLE
#extension GL_ANGLE_shader_pixel_local_storage:require
#define w2
#define I0(d,a) layout(binding=d,rgba8)uniform lowp pixelLocalANGLE a
#define Y0(d,a) layout(binding=d,r32ui)uniform highp upixelLocalANGLE a
#define x2
#define J0(h) pixelLocalLoadANGLE(h)
#define i1(h) pixelLocalLoadANGLE(h).x
#define T0(h,F) pixelLocalStoreANGLE(h,F)
#define k1(h,F) pixelLocalStoreANGLE(h,uvec4(F))
#define C2(h)
#define i2(h)
#define h2
#define j2
#endif
#ifdef GE
#extension GL_EXT_shader_pixel_local_storage:enable
#define w2 __pixel_localEXT z1{
#define I0(d,a) layout(rgba8)lowp vec4 a
#define Y0(d,a) layout(r32ui)highp uint a
#define x2 };
#define J0(h) h
#define i1(h) h
#define T0(h,F) h=(F)
#define k1(h,F) h=(F)
#define C2(h) h=h
#define i2(h) h=h
#define h2
#define j2
#endif
#ifdef HE
#extension GL_EXT_shader_framebuffer_fetch:require
#define w2
#define I0(d,a) layout(location=d)inout lowp vec4 a
#define Y0(d,a) layout(location=d)inout highp uvec4 a
#define x2
#define J0(h) h
#define i1(h) h.x
#define T0(h,F) h=(F)
#define k1(h,F) h.x=(F)
#define C2(h) T0(h,J0(h))
#define i2(h) k1(h,i1(h))
#define h2
#define j2
#endif
#ifdef IE
#ifdef GL_ARB_shader_image_load_store
#extension GL_ARB_shader_image_load_store:require
#endif
#if defined(GL_ARB_fragment_shader_interlock)
#extension GL_ARB_fragment_shader_interlock:require
#define h2 beginInvocationInterlockARB()
#define j2 endInvocationInterlockARB()
#elif defined(GL_INTEL_fragment_shader_ordering)
#extension GL_INTEL_fragment_shader_ordering:require
#define h2 beginFragmentShaderOrderingINTEL()
#define j2
#else
#define h2
#define j2
#endif
#define w2
#ifdef YB
#define I0(d,a) layout(set=i5,binding=d,rgba8)uniform lowp coherent image2D a
#define Y0(d,a) layout(set=i5,binding=d,r32ui)uniform highp coherent uimage2D a
#else
#define I0(d,a) layout(binding=d,rgba8)uniform lowp coherent image2D a
#define Y0(d,a) layout(binding=d,r32ui)uniform highp coherent uimage2D a
#endif
#define x2
#define J0(h) imageLoad(h,I)
#define i1(h) imageLoad(h,I).x
#define T0(h,F) imageStore(h,I,F)
#define k1(h,F) imageStore(h,I,uvec4(F))
#define C2(h)
#define i2(h)
#ifndef DD
#define DD
#endif
#endif
#ifdef JE
#define w2
#define q3(d,a) layout(input_attachment_index=d,binding=d,set=i5)uniform lowp subpassInput q6##a;
#define I0(d,a) q3(d,a);layout(location=d)out lowp vec4 a
#define Y0(d,a) layout(input_attachment_index=d,binding=d,set=i5)uniform highp usubpassInput q6##a;layout(location=d)out highp uvec4 a
#define x2
#define J0(h) subpassLoad(q6##h)
#define i1(h) subpassLoad(q6##h).x
#define T0(h,F) h=(F)
#define k1(h,F) h.x=(F)
#define C2(h) T0(h,subpassLoad(q6##h))
#define i2(h) k1(h,subpassLoad(q6##h).x)
#define h2
#define j2
#endif
#ifdef KE
#define w2
#define I0(d,a) layout(location=d)out lowp vec4 a
#define Y0(d,a) layout(location=d)out highp uvec4 a
#define x2
#define J0(h) vec4(0)
#define i1(h) 0u
#define T0(h,F) h=(F)
#define k1(h,F) h.x=(F)
#define C2(h) h=vec4(0)
#define i2(h) h.x=0u
#define h2
#define j2
#endif
#ifndef q3
#define q3 I0
#endif
#ifdef YB
#define gl_VertexID gl_VertexIndex
#endif
#ifdef OD
#ifdef YB
#define O7 gl_InstanceIndex
#else
#ifdef ED
uniform highp int ED;
#define O7 (gl_InstanceID+ED)
#else
#define O7 (gl_InstanceID+gl_BaseInstance)
#endif
#endif
#else
#define O7 0
#endif
#define v5
#define Y1
#define p1(a,f0,B,n,K) void main(){int n=gl_VertexID;int K=O7;
#define H6 p1
#define P4(a,a2,c2,r2,v2,n) p1(a,a2,c2,n,K)
#define L(a,X)
#define Q(a)
#define O(a,X)
#define g1(f1) gl_Position=f1;}
#define e2(G4,a) layout(location=0)out G4 Ce;void main()
#define f2(F) Ce=F
#define B0 gl_FragCoord.xy
#define E5
#define X2
#ifdef DD
#ifdef YB
#define f4(d,a) layout(set=i5,binding=d,r32ui)uniform highp coherent uimage2D a
#else
#define f4(d,a) layout(binding=d,r32ui)uniform highp coherent uimage2D a
#endif
#define m4(h) imageLoad(h,I).x
#define n4(h,F) imageStore(h,I,uvec4(F))
#define I5(h,m) imageAtomicMax(h,I,m)
#define J5(h,m) imageAtomicAdd(h,I,m)
#define y3 ,g0 I
#define G1 ,I
#define y2(a) void main(){g0 I=ivec2(floor(B0));
#define L2 }
#else
#define y3
#define G1
#define y2(a) void main()
#define L2
#endif
#define S4(a) y2(a)
#define A3(a) layout(location=0)out i K1;y2(a)
#define H5(a) layout(location=0)out i K1;y2(a)
#define Q4 L2
#define C0(o,r) ((o)*(r))
precision highp float;precision highp int;
#if XB<310
e i unpackUnorm4x8(uint u){M A1=M(u&0xffu,(u>>8)&0xffu,(u>>16)&0xffu,u>>24);return f(A1)*(1./255.);}
#endif
#if XB>=310&&defined(AB)&&defined(CB)&&defined(BB)
out gl_PerVertex{float gl_ClipDistance[4];f gl_Position;};
#endif
#if defined(YB)&&defined(HB)&&defined(CB)&&!defined(JB)
i Ae(mediump mat4 r6){if(gl_SampleMaskIn[0]==0xf){return(r6[0]+r6[1]+r6[2]+r6[3])*.25;}else{i De=vec4(notEqual(gl_SampleMaskIn[0]&ivec4(1,2,4,8),ivec4(0)));i N=r6*De;int P7=(gl_SampleMaskIn[0]&5)+((gl_SampleMaskIn[0]>>1)&5);P7=(P7&3)+(P7>>2);N*=1./float(P7);return N;}}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive