#pragma once

#include "draw_path.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char draw_path[] = R"===(#ifdef FB
#define e6 !FB
#else
#define e6 true
#endif
#ifdef AB
U0(f0)
#ifdef GB
i0(0,a4,IB);
#else
i0(0,f,MB);i0(1,f,NB);
#endif
V0
#endif
n1 n0 H(0,f,H1);
#ifdef DB
n0 H(1,c,Q0);
#elif!defined(CB)
#ifdef GB
PB H(1,g,h1);
#elif defined(EB)
n0 H(2,f,D);
#else
n0 H(2,G,D);
#endif
PB H(3,g,j0);
#endif
#ifdef R
PB H(4,G,e3);
#endif
#ifdef BB
n0 H(5,f,R0);
#endif
#ifdef FB
PB H(6,g,O3);
#endif
o1
#ifdef AB
p1(QB,f0,B,n,K){
#ifdef GB
l0(n,B,IB,a0);
#else
l0(n,B,MB,f);l0(n,B,NB,f);
#endif
L(H1,f);
#ifdef DB
L(Q0,c);
#elif!defined(CB)
#ifdef GB
L(h1,g);
#elif defined(EB)
L(D,f);
#else
L(D,G);
#endif
L(j0,g);
#endif
#ifdef R
L(e3,G);
#endif
#ifdef BB
L(R0,f);
#endif
#ifdef FB
L(O3,g);
#endif
bool mb=false;uint U;c J;
#ifdef CB
c0 v7;
#endif
#ifdef DB
J=f8(IB,U,
#ifdef CB
v7,
#endif
Q0 Y1);
#elif defined(GB)
J=g8(IB,U
#ifdef CB
,v7
#else
,h1
#endif
Y1);
#else
f P;mb=!F6(MB,NB,K,U,J
#ifndef CB
,P
#else
,v7
#endif
Y1);
#ifndef CB
#ifdef EB
D=P;
#else
D.xy=G6(P.xy);
#endif
#endif
#endif
N0 F0=k4(DC,U);
#if!defined(DB)&&!defined(CB)
j0=i7(U,q.e5);if((F0.x&v8)!=0u)j0=-j0;
#endif
uint J1=F0.x&0xfu;
#ifdef R
if(R){uint Wd=(J1==P6?F0.y:F0.x)>>16;g Z0=i7(Wd,q.e5);if(J1==P6)Z0=-Z0;e3.x=Z0;}
#endif
#ifdef FB
if(FB){O3=float((F0.x>>4)&0xfu);}
#endif
c f6=J;
#ifdef DE
f6.y=float(q.md)-f6.y;
#endif
#ifdef BB
if(BB){V R1=D1(w0(LB,U*4u+2u));f Z1=w0(LB,U*4u+3u);
#ifndef CB
R0=J6(R1,Z1.xy,f6);
#else
Oa(R1,Z1.xy,f6);
#endif
}
#endif
if(J1==w8){i j=unpackUnorm4x8(F0.y);if(e6)j.xyz*=j.w;H1=f(j);}
#ifdef R
else if(R&&J1==P6){g w7=i7(F0.x>>16,q.e5);e3.y=w7;}
#endif
else{V Xd=D1(w0(LB,U*4u));f x7=w0(LB,U*4u+1u);c F2=C0(Xd,f6)+x7.xy;if(J1==Q6||J1==xd){H1.w=-uintBitsToFloat(F0.y);float Yd=x7.z;if(Yd>.9){H1.z=2.;}else{H1.z=x7.w;}if(J1==Q6){H1.y=.0;H1.x=F2.x;}else{H1.z=-H1.z;H1.xy=F2.xy;}}else{float G2=uintBitsToFloat(F0.y);float d6=x7.z;H1=f(F2.x,F2.y,G2,-2.-d6);}}f T;if(!mb){T=E2(J);
#ifdef EE
T.y=-T.y;
#endif
#ifdef CB
T.z=V8(v7);
#endif
}else{T=f(q.C1,q.C1,q.C1,q.C1);}Q(H1);
#ifdef DB
Q(Q0);
#elif!defined(CB)
#ifdef GB
Q(h1);
#elif defined(EB)
Q(D);
#else
Q(D);
#endif
Q(j0);
#endif
#ifdef R
Q(e3);
#endif
#ifdef BB
Q(R0);
#endif
#ifdef FB
Q(O3);
#endif
g1(T);}
#endif
#ifdef HB
w3 x3 e i nb(f I2,float E E5){i j;if(I2.w>=.0){j=K5(I2);if(e6)j*=E;else j.w*=E;}else if(I2.w>-1.){float t=I2.z>.0?I2.x:length(I2.xy);t=clamp(t,.0,1.);float ob=abs(I2.z);float x=ob>1.?(1.-1./W8)*t+(.5/W8):(1./W8)*t+ob;float Zd=-I2.w;j=T1(NC,x8,c(x,Zd),.0);j.w*=E;if(e6)j.xyz*=j.w;}else{g d6=-I2.w-2.;j=y7(VB,B3,I2.xy,d6);g G2=I2.z*E;if(e6)j*=G2;else j=E1(Y3(j),j.w*G2);}return j;}
#ifndef CB
w2 I0(L6,H0);Y0(D5,q1);I0(fb,N3);Y0(n8,y4);x2 y2(OB){O(H1,f);
#ifdef DB
O(Q0,c);
#elif!defined(CB)
#ifdef GB
O(h1,g);
#elif defined(EB)
O(D,f);
#else
O(D,G);
#endif
O(j0,g);
#endif
#ifdef R
O(e3,G);
#endif
#ifdef BB
O(R0,f);
#endif
#ifdef FB
O(O3,g);
#endif
#if!defined(GB)||defined(DB)
h2;
#endif
g E;
#ifdef DB
E=Y6(Q0,q.V4 w1);
#else
G L3=unpackHalf2x16(i1(y4));g pb=L3.y;g F1=pb==j0?L3.x:r1(.0);
#ifdef GB
F1+=h1;i2(y4);
#else
if(W6(D)){g r0;
#ifdef EB
if(EB&&z8(D)){r0=T6(D w1);}else
#endif
{r0=min(D.x,D.y);}F1=max(r0,F1);}else{g r0;
#if defined(EB)
if(EB&&U6(D)){r0=T4(D w1);}else
#endif
{r0=D.x;}F1+=r0;}k1(y4,packHalf2x16(Z3(F1,j0)));
#endif
#ifdef QC
if(QC){
#ifdef RC
if(RC==Bd){if(F1<.0)E=.0;else if(F1<=1.)E=F1;else E=1.;}else
#endif
{E=clamp(F1,r1(.0),r1(1.));}}else
#endif
{E=abs(F1);
#ifdef EC
if(EC&&j0<.0){E=1.-r1(abs(fract(E*.5)*2.+-1.));}
#endif
E=min(E,r1(1.));}
#endif
#ifdef R
if(R&&e3.x<.0){g Z0=-e3.x;
#ifdef SC
if(SC){g w7=e3.y;if(w7!=.0){G I1=unpackHalf2x16(i1(q1));g m5=I1.y;g z7;if(m5!=Z0){z7=m5==w7?I1.x:.0;
#ifndef GB
T0(N3,E1(z7,.0,.0,.0));
#endif
}else{z7=J0(N3).x;
#ifndef GB
C2(N3);
#endif
}E=min(E,z7);}}
#endif
k1(q1,packHalf2x16(Z3(E,Z0)));C2(H0);}else
#endif
{
#ifdef R
if(R){g Z0=e3.x;if(Z0!=.0){G I1=unpackHalf2x16(i1(q1));g m5=I1.y;E=(m5==Z0)?min(I1.x,E):r1(.0);}}
#endif
#ifdef BB
if(BB){g l4=D8(K5(R0));E=clamp(l4,r1(.0),E);}
#endif
i j=nb(H1,E X2);i v1;
#ifdef DB
v1=J0(H0);
#else
if(pb!=j0){v1=J0(H0);
#ifndef GB
T0(N3,v1);
#endif
}else{v1=J0(N3);
#ifndef GB
C2(N3);
#endif
}
#endif
#ifdef FB
if(FB){if(O3!=h7(E8)){j.xyz=O4(j.xyz,v1,R8(O3));}j.xyz*=j.w;}
#endif
j+=v1*(1.-j.w);T0(H0,j);i2(q1);}
#if!defined(GB)||defined(DB)
j2;
#endif
L2;}
#else
e2(i,OB){O(H1,f);
#ifdef DB
O(Q0,c);
#endif
#ifdef FB
O(O3,g);
#endif
g E=
#ifdef DB
Y6(Q0,q.V4 w1);
#else
1.;
#endif
i j=nb(H1,E X2);
#if defined(FB)&&!defined(JB)
if(FB){i v1=i9(PC);j.xyz=O4(j.xyz,v1,R8(O3));j.xyz*=j.w;}
#endif
f2(j);}
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive