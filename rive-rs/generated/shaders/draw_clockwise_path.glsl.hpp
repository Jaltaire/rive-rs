#pragma once

#include "draw_clockwise_path.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char draw_clockwise_path[] = R"===(#ifdef LC
#ifdef AB
U0(f0)i0(0,f,MB);i0(1,f,NB);V0
#endif
n1 K2 H(0,c0,j0);n0 H(1,f,D);n0 H(2,c,Q0);K2 H(3,N0,U2);H(4,c,a3);o1
#ifdef AB
p1(QB,f0,B,n,K){l0(n,B,MB,f);l0(n,B,NB,f);L(j0,c0);L(D,f);L(U2,N0);L(a3,c);f T;uint U;c J;if(F6(MB,NB,K,U,J,D Y1)){M L3=w0(KB,U*4u+3u);j0=U;U2=L3.xy;a3=J+uintBitsToFloat(L3.zw);T=E2(J);}else{T=f(q.C1,q.C1,q.C1,q.C1);}Q(j0);Q(D);Q(U2);Q(a3);g1(T);}
#endif
#endif
#ifdef GB
#ifdef AB
U0(f0)i0(0,a4,IB);V0
#endif
n1 K2 H(0,c0,j0);
#ifdef DB
n0 H(1,c,Q0);
#else
PB H(1,g,h1);K2 H(2,N0,U2);H(3,c,a3);
#endif
o1
#ifdef AB
p1(QB,f0,B,n,K){l0(n,B,IB,a0);
#ifdef DB
L(Q0,c);
#else
#endif
L(j0,c0);
#ifdef DB
L(Q0,c);
#else
L(h1,g);L(U2,N0);L(a3,c);
#endif
uint U;c J;
#ifdef DB
J=f8(IB,U,Q0 Y1);
#else
J=g8(IB,U,h1 Y1);M L3=w0(KB,U*4u+3u);U2=L3.xy;a3=J+uintBitsToFloat(L3.zw);
#endif
j0=Q1(U);f T=E2(J);Q(j0);
#ifdef DB
Q(Q0);
#else
Q(h1);Q(U2);Q(a3);
#endif
g1(T);}
#endif
#endif
#ifdef HB
w3 g4(o8,aa,DC);h4(p8,ba,LB);Md(zd,Of,j5);x3
#ifdef KC
e void Nd(g q7,uint N1){uint gb=uint(abs(q7)*d9+.5);uint hb=q.Y2|(c6-gb);uint V2=f9(j5,N1,hb);if(V2>=q.Y2){uint Od=V2-max(V2,hb);ib(j5,N1,Od-gb);}}
#endif
e void Pd(i4(float)c3,g r0,uint N1){if(min(c3,r0)>=1.){return;}g m;uint Qd=uint(abs(r0)*d9+.5);uint V2=f9(j5,N1,q.Y2|Qd);if(V2<q.Y2){m=r0;}else{g g2=h7(V2&c9)*e9;g d3=max(g2,r0);m=(d3-g2)/(1.-g2*c3);}c3*=m;}e void Rd(i4(float)c3,g M3,uint N1){uint g9=Sd(j5,N1);if(min(c3,M3)>=1.&&(g9<q.Y2||g9>=(q.Y2|c6))){return;}g m=.0;uint h9=uint(abs(M3)*d9+.5);if(g9<q.Y2){uint jb=q.Y2|(c6+h9);uint V2=f9(j5,N1,jb);if(V2<=q.Y2){m=M3;
#ifdef GB
m=min(m,1.);
#endif
M3=.0;}else if(V2<jb){uint kb=(V2&c9)-c6;g g2=h7(kb)*e9;g d3=M3;
#ifdef GB
d3=min(d3,1.);
#endif
m=(d3-g2)/(1.-g2*c3);h9=kb;M3=g2;}}if(M3>.0){uint Td=ib(j5,N1,h9);g g2=Q8(int((Td&c9)-c6))*e9;g d3=g2+M3;g2=clamp(g2,.0,1.);d3=clamp(d3,.0,1.);g lb=1.-g2*c3;if(lb<=.0)discard;m+=(1.-m*c3)*(d3-g2)/lb;}c3*=m;}e2(i,OB){O(j0,c0);
#ifdef Pf
O(D,f);
#elif defined(DB)
O(Q0,c);
#else
O(h1,g);
#endif
#ifndef DB
O(U2,N0);O(a3,c);
#endif
i H2;uint U=j0;N0 F0=k4(DC,U);uint J1=F0.x&0xfu;if(J1<=w8){H2=unpackUnorm4x8(F0.y);}else{V D0=D1(w0(LB,U*4u));f S0=w0(LB,U*4u+1u);c F2=C0(D0,B0)+S0.xy;if(J1!=yd){float t=J1==Q6?F2.x:length(F2);t=clamp(t,.0,1.);float x=t*S0.z+S0.w;float y=uintBitsToFloat(F0.y);H2=T1(NC,x8,c(x,y),.0);}else{float G2=uintBitsToFloat(F0.y);float d6=S0.z;H2=T1(VB,B3,F2,d6);H2=E1(Y3(H2),H2.w*G2);}}if(H2.w==.0){discard;}
#ifdef DB
H2.w*=Y6(Q0,q.V4 w1);
#else
uint N1=U2.x;uint Ud=U2.y;N0 k5=N0(floor(a3));N1+=(k5.y>>5)*(Ud<<5)+(k5.x>>5)*(32<<5);N1+=((k5.x&0x1f)>>2)*(32<<2)+((k5.y&0x1f)>>2)*(4<<2);N1+=(k5.y&0x3)*4+(k5.x&0x3);
#ifdef KC
if(KC){
#ifdef GB
g q7=-h1;
#else
g r0;
#ifdef EB
if(EB&&U6(D)){r0=T4(D w1);}else
#endif
{r0=D.x;}g q7=max(-r0,.0);
#endif
Nd(q7,N1);discard;}
#endif
#ifndef GB
if(W6(D)){g r0;
#ifdef EB
if(EB&&z8(D)){r0=T6(D w1);}else
#endif
{r0=min(D.x,D.y);}r0=clamp(r0,.0,1.);Pd(H2.w,r0,N1);}else
#endif
{
#ifdef GB
g r0=h1;
#else
g r0;
#ifdef EB
if(EB&&U6(D)){r0=T4(D w1);}else
#endif
{r0=D.x;}r0=clamp(r0,.0,1.);
#endif
Rd(H2.w,r0,N1);}
#endif
f2(H2);}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive