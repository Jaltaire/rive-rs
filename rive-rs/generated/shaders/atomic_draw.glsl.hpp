#pragma once

#include "atomic_draw.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char atomic_draw[] = R"===(#ifdef LC
#ifdef AB
U0(f0)i0(0,f,MB);i0(1,f,NB);V0
#endif
n1
#ifdef EB
n0 H(0,f,D);
#else
n0 H(0,G,D);
#endif
K2 H(1,c0,j0);o1
#ifdef AB
p1(QB,f0,B,n,K){l0(n,B,MB,f);l0(n,B,NB,f);
#ifdef EB
L(D,f);
#else
L(D,G);
#endif
L(j0,c0);f T;uint U;c J;f P;if(F6(MB,NB,K,U,J,P Y1)){
#ifdef EB
D=P;
#else
D.xy=G6(P.xy);
#endif
j0=Q1(U);T=E2(J);}else{T=f(q.C1,q.C1,q.C1,q.C1);}Q(D);Q(j0);g1(T);}
#endif
#endif
#ifdef GB
#ifdef AB
U0(f0)i0(0,a4,IB);V0
#endif
n1
#ifdef DB
n0 H(0,c,Q0);
#else
PB H(0,g,h1);
#endif
K2 H(1,c0,j0);o1
#ifdef AB
p1(QB,f0,B,n,K){l0(n,B,IB,a0);
#ifdef DB
L(Q0,c);
#else
L(h1,g);
#endif
L(j0,c0);uint U;c J;
#ifdef DB
J=f8(IB,U,Q0 Y1);
#else
J=g8(IB,U,h1 Y1);
#endif
j0=Q1(U);f T=E2(J);
#ifdef DB
Q(Q0);
#else
Q(h1);
#endif
Q(j0);g1(T);}
#endif
#endif
#ifdef WC
#ifdef AB
U0(f0)i0(0,f,ZB);V0
#endif
n1 n0 H(0,c,q0);n0 H(1,g,c4);
#ifdef BB
n0 H(2,f,R0);
#endif
o1
#ifdef AB
H6(QB,f0,B,n,K){l0(n,B,ZB,f);L(q0,c);L(c4,g);
#ifdef BB
L(R0,f);
#endif
bool h8=ZB.z==.0||ZB.w==.0;c4=h8?.0:1.;c J=ZB.xy;V D0=D1(m0.I6);V C5=transpose(inverse(D0));if(!h8){float i8=p3*j8(C5[1])/dot(D0[1],C5[1]);if(i8>=.5){J.x=.5;c4*=d4(.5/i8);}else{J.x+=i8*ZB.z;}float k8=p3*j8(C5[0])/dot(D0[0],C5[0]);if(k8>=.5){J.y=.5;c4*=d4(.5/k8);}else{J.y+=k8*ZB.w;}}q0=J;J=C0(D0,J)+m0.S0;if(h8){c e4=C0(C5,ZB.zw);e4*=j8(e4)/dot(e4,e4);J+=p3*e4;}
#ifdef BB
if(BB){R0=J6(D1(m0.R1),m0.Z1,J);}
#endif
f T=E2(J);Q(q0);Q(c4);
#ifdef BB
Q(R0);
#endif
g1(T);}
#endif
#elif defined(UD)
#ifdef AB
U0(a2)i0(0,c,TB);V0 U0(r2)i0(1,c,UB);V0
#endif
n1 n0 H(0,c,q0);
#ifdef BB
n0 H(1,f,R0);
#endif
o1
#ifdef AB
P4(QB,a2,c2,r2,v2,n){l0(n,c2,TB,c);l0(n,v2,UB,c);L(q0,c);
#ifdef BB
L(R0,f);
#endif
V D0=D1(m0.I6);c J=C0(D0,TB)+m0.S0;q0=UB;
#ifdef BB
if(BB){R0=J6(D1(m0.R1),m0.Z1,J);}
#endif
f T=E2(J);Q(q0);
#ifdef BB
Q(R0);
#endif
g1(T);}
#endif
#endif
#ifdef VD
#ifdef AB
U0(f0)V0
#endif
n1 o1
#ifdef AB
p1(QB,f0,B,n,K){g0 S1;S1.x=(n&1)==0?q.K6.x:q.K6.z;S1.y=(n&2)==0?q.K6.y:q.K6.w;f T=E2(c(S1));g1(T);}
#endif
#endif
#ifdef XC
#endif
#ifdef HB
w2
#ifndef JB
#ifdef LD
#define l8 LD
#else
#define l8 L6
#endif
#ifdef MC
q3(l8,H0);
#else
I0(l8,H0);
#endif
#endif
#ifdef AC
#define r3 i
#define m8 J0
#define M6 E1(.0)
#define Z9(m) ((m).w!=.0)
#ifdef R
#ifndef IC
I0(D5,q1);
#else
q3(D5,q1);
#endif
#endif
#else
#define r3 uint
#define M6 0u
#define m8 i1
#define Z9(m) ((m)!=0u)
#ifdef R
Y0(D5,q1);
#endif
#endif
f4(n8,v3);x2 w3 g4(o8,aa,DC);h4(p8,ba,LB);x3 e uint Nc(float x){return uint(round(x*q8+r8));}e g N6(uint x){return d4(float(x)*ca+(-r8*ca));}
#ifdef R
e void da(uint Z0,r3 I1,i4(g)E){
#ifdef AC
if(all(lessThan(abs(I1.xy-unpackUnorm4x8(Z0).xy),Z3(.25/255.))))E=min(E,I1.z);else E=.0;
#else
if(Z0==I1>>16)E=min(E,unpackHalf2x16(I1).x);else E=.0;
#endif
}
#endif
e void O6(uint U,g F1,j1(i)W
#if defined(R)&&!defined(IC)
,i4(r3)a1
#endif
E5 y3){N0 F0=k4(DC,U);g E=F1;if((F0.x&(Oc|v8))!=0u){E=abs(E);
#ifdef EC
if(EC&&(F0.x&v8)!=0u){E=1.-abs(fract(E*.5)*2.+-1.);}
#endif
}E=clamp(E,r1(.0),r1(1.));
#ifdef R
if(R){uint Z0=F0.x>>16u;if(Z0!=0u){da(Z0,m8(q1),E);}}
#endif
#ifdef BB
if(BB&&(F0.x&Pc)!=0u){V D0=D1(w0(LB,U*4u+2u));f S0=w0(LB,U*4u+3u);c Qc=C0(D0,B0)+S0.xy;G ea=G6(abs(Qc)*S0.zw-S0.zw);g l4=clamp(min(ea.x,ea.y)+.5,.0,1.);E=min(E,l4);}
#endif
uint J1=F0.x&0xfu;if(J1<=w8){W=unpackUnorm4x8(F0.y);
#ifdef R
if(R&&J1==P6){
#ifndef IC
#ifdef AC
a1.xy=W.zw;a1.z=E;a1.w=1.;
#else
a1=F0.y|packHalf2x16(Z3(E,.0));
#endif
#endif
W=E1(.0);}
#endif
}else{V D0=D1(w0(LB,U*4u));f S0=w0(LB,U*4u+1u);c F2=C0(D0,B0)+S0.xy;float t=J1==Q6?F2.x:length(F2);t=clamp(t,.0,1.);float x=t*S0.z+S0.w;float y=uintBitsToFloat(F0.y);W=T1(NC,x8,c(x,y),.0);}W.w*=E;
#if!defined(JB)&&defined(FB)
c0 z3;if(FB&&W.w!=.0&&(z3=Q1((F0.x>>4)&0xfu))!=0u){i v1=J0(H0);W.xyz=O4(W.xyz,v1,z3);}
#endif
#ifndef AC
W.xyz*=W.w;
#endif
}
#if!defined(JB)&&!defined(MC)
e void R6(i W y3){
#ifndef AC
if(W.w==.0)return;float F5=1.-W.w;if(F5!=.0)W+=J0(H0)*F5;
#endif
T0(H0,W);}
#endif
#if defined(R)&&!defined(IC)
e void y8(r3 a1 y3){
#ifdef AC
T0(q1,a1);
#else
if(a1!=0u)k1(q1,a1);
#endif
}
#endif
#ifdef JB
#define G5 A3
#define ga H5
#define R4 Q4
#else
#define G5 y2
#define ga S4
#define R4 L2
#endif
#ifdef LC
G5(OB){
#ifdef EB
O(D,f);
#else
O(D,G);
#endif
O(j0,c0);g S6;
#ifdef EB
if(EB&&z8(D)){S6=T6(D w1);}else if(EB&&U6(D)){S6=T4(D w1);}else
#endif
{S6=min(min(r1(D.x),abs(r1(D.y))),r1(1.));}i W=E1(.0);
#ifdef R
r3 a1=M6;
#endif
uint V6=Nc(S6);uint ha=(ia(j0)<<U4)|V6;uint U1=I5(v3,ha);c0 M2=Q1(U1>>U4);if(M2==j0){if(!W6(D)){V6+=U1-max(ha,U1);V6-=A8;J5(v3,V6);}}else{g F1=N6(U1&X6);O6(M2,F1,W
#ifdef R
,a1
#endif
X2 G1);}
#ifdef JB
K1=W;
#else
R6(W G1);
#endif
#ifdef R
y8(a1 G1);
#endif
R4}
#endif
#ifdef GB
G5(OB){
#ifdef DB
O(Q0,c);
#else
O(h1,g);
#endif
O(j0,c0);uint U1=m4(v3);c0 M2=Q1(U1>>U4);uint B8;
#ifndef DB
if(M2==j0){B8=U1;}else
#endif
{B8=(ia(j0)<<U4)+A8;}g E;
#ifdef DB
E=Y6(Q0,q.V4 w1);
#else
E=h1;
#endif
int Rc=int(round(E*q8));n4(v3,B8+uint(Rc));i W=E1(.0);
#ifdef R
r3 a1=M6;
#endif
#ifndef DB
if(M2!=j0)
#endif
{g C8=N6(U1&X6);O6(M2,C8,W
#ifdef R
,a1
#endif
X2 G1);}
#ifdef JB
K1=W;
#else
R6(W G1);
#endif
#ifdef R
y8(a1 G1);
#endif
R4}
#endif
#ifdef XC
ga(OB){O(q0,c);
#ifdef WC
O(c4,g);
#endif
#ifdef BB
O(R0,f);
#endif
i W4=o4(VB,B3,q0);g X4=1.;
#ifdef WC
X4=min(c4,X4);
#endif
#ifdef BB
if(BB){g l4=D8(K5(R0));X4=clamp(l4,r1(.0),X4);}
#endif
uint U1=m4(v3);c0 M2=Q1(U1>>U4);g C8=N6(U1&X6);i W;
#ifdef R
r3 a1=M6;
#endif
O6(M2,C8,W
#ifdef R
,a1
#endif
X2 G1);
#ifdef AC
W.xyz*=W.w;
#endif
#ifdef R
if(R&&m0.Z0!=0u){r3 I1=Z9(a1)?a1:m8(q1);da(m0.Z0,I1,X4);}
#endif
#if!defined(JB)&&defined(FB)
if(FB&&m0.z3!=E8){i v1=J0(H0)*(1.-W.w)+W;W4.xyz=O4(Y3(W4),v1,Q1(m0.z3))*W4.w;}
#endif
W4*=X4*d4(m0.G2);W=W*(1.-W4.w)+W4;
#ifdef JB
K1=W;
#else
R6(W G1);
#endif
#ifdef R
y8(a1 G1);
#endif
n4(v3,A8);R4}
#endif
#ifdef WD
G5(OB){
#ifdef XD
T0(H0,unpackUnorm4x8(q.Sc));
#endif
#ifdef YD
i j=J0(H0);T0(H0,j.zyxw);
#endif
n4(v3,q.Tc);
#ifdef R
if(R){k1(q1,0u);}
#endif
#ifdef JB
discard;
#endif
R4}
#endif
#ifdef IC
#ifdef MC
A3(OB)
#else
G5(OB)
#endif
{uint U1=m4(v3);g F1=N6(U1&X6);c0 M2=Q1(U1>>U4);i W;O6(M2,F1,W X2 G1);
#ifdef MC
#ifdef AC
W.xyz*=W.w;
#endif
float F5=1.-W.w;if(F5!=.0)W+=J0(H0)*F5;K1=W;Q4
#else
#ifdef JB
K1=W;
#else
R6(W G1);
#endif
R4
#endif
}
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive