#pragma once

#include "common.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char common[] = R"===(#define N2 3.14159265359
#define g7 6.28318530718
#define U5 1.57079632679
#ifndef CB
#define p3 float(.5)
#else
#define p3 float(.0)
#endif
#define E2(l) f7(l,q.fd,q.gd)
#ifdef CE
#define Aa(S,d,a) r4(S,d,a)
#define H3 f
#define N8(m) m
#define Z4(m) m
#define O8(m) uintBitsToFloat(m)
#define v4(m) floatBitsToUint(m)
#else
#define Aa(S,d,a) I3(S,d,a)
#define H3 M
#define N8(m) floatBitsToUint(m)
#define Z4(m) uintBitsToFloat(m)
#define O8(m) m
#define v4(m) m
#endif
#define J3(m) V5(JC,P8,m,Ba,float(Ba),.0).x
#define a5(m) V5(JC,P8,m,Ca,float(Ca),.0).x
#ifdef Da
e g d4(float x){return x;}e g h7(uint x){return float(x);}e g hd(c0 x){return float(x);}e g Q8(int x){return float(x);}e i K5(f xyzw){return xyzw;}e G G6(c xy){return xy;}e i va(M xyzw){return vec4(xyzw);}e c0 R8(g x){return uint(x);}e c0 Q1(uint x){return x;}
#else
e g d4(float x){return(g)x;}e g h7(uint x){return(g)x;}e g hd(c0 x){return(g)x;}e g Q8(int x){return(g)x;}e i K5(f xyzw){return(i)xyzw;}e G G6(c xy){return(G)xy;}e i va(M xyzw){return(i)xyzw;}e c0 R8(g x){return(c0)x;}e c0 Q1(uint x){return(c0)x;}
#endif
e g r1(g x){return x;}e G Z3(G xy){return xy;}e G Z3(g x,g y){G N;N.x=x,N.y=y;return N;}e G Z3(g x){G N;N.x=x,N.y=x;return N;}e c L5(float x){return c(x,x);}e A L0(g x,g y,g z){A N;N.x=x,N.y=y,N.z=z;return N;}e A L0(g x){A N;N.x=x,N.y=x,N.z=x;return N;}e i E1(g x,g y,g z,g w){i N;N.x=x,N.y=y,N.z=z,N.w=w;return N;}e i E1(A xyz,g w){i N;N.xyz=xyz;N.w=w;return N;}e i E1(g x){i N;N.x=x,N.y=x,N.z=x,N.w=x;return N;}e c5 id(bool b){return c5(b,b);}e W5 uf(A k,A b,A A0){W5 N;N[0]=k;N[1]=b;N[2]=A0;return N;}e X5 Mc(A k,A b){X5 N;N[0]=k;N[1]=b;return N;}e V D1(f x){return V(x.xy,x.zw);}e uint ia(c0 x){return x;}e uint Ea(uint Z){return(Z&jd)-1u;}e c d5(c k,c b,float t){return(b-k)*t+k;}e g i7(uint Fa,uint e5){return Fa==0u?.0:unpackHalf2x16((Fa+kd)*e5).x;}e float Ga(c M1){M1=normalize(M1);float O0=acos(clamp(M1.x,-1.,1.));return M1.y>=.0?O0:-O0;}e i vf(i j){return E1(j.xyz*j.w,j.w);}e A Y3(i S8){return S8.xyz*(S8.w!=.0?1./S8.w:.0);}e g D8(i Ha){G Ia=min(Ha.xy,Ha.zw);g ld=min(Ia.x,Ia.y);return ld;}e float j8(c x){return abs(x.x)+abs(x.y);}
#ifndef UNIFORM_DEFINITIONS_AUTO_GENERATED
f5(K3,WB)float wa;float Ja;float fd;float gd;uint Ka;uint md;uint Sc;uint Tc;j7 K6;c V4;c La;uint Y2;uint e5;float C1;uint nd;Y5(q)
#endif
#ifdef AB
e f f7(c Ma,float od,float Na){return f(Ma.x*od-1.,Ma.y*Na-sign(Na),0.,1.);}
#ifndef CB
e f J6(V R1,c Z1,c T8){c U8=abs(R1[0])+abs(R1[1]);if(U8.x!=.0&&U8.y!=.0){c d0=1./U8;c w4=C0(R1,T8)+Z1;const float pd=.5;return f(w4,-w4)*d0.xyxy+d0.xyxy+pd;}else{return Z1.xyxy;}}
#else
e float V8(uint Z5){return 1.-float(Z5)*(2./32768.);}
#ifdef BB
e void Oa(V R1,c Z1,c T8){if(R1!=V(0)){c w4=C0(R1,T8)+Z1.xy;gl_ClipDistance[0]=w4.x+1.;gl_ClipDistance[1]=w4.y+1.;gl_ClipDistance[2]=1.-w4.x;gl_ClipDistance[3]=1.-w4.y;}else{gl_ClipDistance[0]=gl_ClipDistance[1]=gl_ClipDistance[2]=gl_ClipDistance[3]=Z1.x-.5;}}
#endif
#endif
#endif
#ifdef XC
#ifndef UNIFORM_DEFINITIONS_AUTO_GENERATED
f5(g5,FC)f I6;c S0;float G2;float wf;f R1;c Z1;uint Z0;uint z3;uint Z5;Y5(m0)
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive