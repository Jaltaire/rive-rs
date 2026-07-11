#pragma once

#include "draw_image_mesh.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char draw_image_mesh[] = R"===(#ifdef AB
U0(a2)i0(0,c,TB);V0 U0(r2)i0(1,c,UB);V0
#endif
n1 n0 H(0,c,q0);
#ifdef R
PB H(1,g,l5);
#endif
#ifdef BB
n0 H(2,f,R0);
#endif
o1
#ifdef AB
O2 P2 P4(QB,a2,c2,r2,v2,n){l0(n,c2,TB,c);l0(n,v2,UB,c);L(q0,c);
#ifdef R
L(l5,g);
#endif
#ifdef BB
L(R0,f);
#endif
c J=C0(D1(m0.I6),TB)+m0.S0;q0=UB;
#ifdef R
if(R){l5=i7(m0.Z0,q.e5);}
#endif
#ifdef BB
if(BB){
#ifndef CB
R0=J6(D1(m0.R1),m0.Z1,J);
#else
Oa(D1(m0.R1),m0.Z1,J);
#endif
}
#endif
f T=E2(J);
#ifdef CB
T.z=V8(m0.Z5);
#endif
Q(q0);
#ifdef R
Q(l5);
#endif
#ifdef BB
Q(R0);
#endif
g1(T);}
#endif
#ifdef HB
Q2 B2(x4,Z8,VB);
#if defined(CB)&&defined(FB)
r7(PC);
#endif
R2 p4 G3(x4,a9,B3)q4 w3 x3
#ifndef CB
w2 I0(L6,H0);Y0(D5,q1);I0(fb,N3);Y0(n8,y4);x2 S4(OB){O(q0,c);
#ifdef R
O(l5,g);
#endif
#ifdef BB
O(R0,f);
#endif
i j=o4(VB,B3,q0);g E=1.;
#ifdef BB
if(BB){g l4=D8(K5(R0));E=clamp(l4,r1(.0),E);}
#endif
h2;
#ifdef R
if(R&&l5!=.0){G I1=unpackHalf2x16(i1(q1));g m5=I1.y;g Vd=m5==l5?I1.x:r1(.0);E=min(E,Vd);}
#endif
i v1=J0(H0);
#ifdef FB
if(FB&&m0.z3!=E8){j.xyz=O4(Y3(j),v1,Q1(m0.z3))*j.w;}
#endif
j*=m0.G2*E;j+=v1*(1.-j.w);T0(H0,j);i2(q1);i2(y4);j2;L2;}
#else
e2(i,OB){O(q0,c);i j=o4(VB,B3,q0)*m0.G2;
#if defined(FB)&&!defined(JB)
if(FB){i v1=i9(PC);j.xyz=O4(Y3(j),v1,m0.z3);j.xyz*=j.w;}
#endif
f2(j);}
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive