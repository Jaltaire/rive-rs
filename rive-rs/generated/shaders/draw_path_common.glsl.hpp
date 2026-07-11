#pragma once

#include "draw_path_common.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char draw_path_common[] = R"===(#define g6 -2.
#define qb -1.5
#define rb .25
#define A7 1e3
#define sb (A7*A7)
#ifdef AB
O2 Aa(T2,Ad,CC);
#ifdef EB
n5(T2,a6,JC);
#endif
P2 E3 P3(Za,ae,KB);g4(o8,aa,DC);h4(p8,ba,LB);P3(ab,be,TC);F3
#endif
#if defined(EB)||defined(DB)
Q3(a6,P8)
#endif
#ifdef HB
Q2 B2(T2,bb,NC);
#if defined(EB)||defined(DB)
n5(T2,a6,JC);
#endif
#ifdef DB
z4(x4,cb,ND);
#endif
B2(x4,Z8,VB);
#if defined(CB)&&defined(FB)&&!defined(JB)
r7(PC);
#endif
R2 Q3(bb,x8)
#ifdef DB
Q3(cb,ce)
#endif
p4 G3(x4,a9,B3)q4
#endif
#ifdef HB
e bool W6(f P){return P.y>=.0;}e bool W6(G P){return P.y>=.0;}
#endif
#if defined(HB)&&defined(EB)
e bool z8(f P){return P.x<qb;}e bool U6(f P){return P.y<qb;}
#endif
#ifdef AB
f tb(float j9,c B7,float l1){c o5=(1.-B7*abs(l1))*.5;float f3,A4;if(abs(j9-U5)<1./A7){f3=.0;A4=.0;}else{float k9=tan(j9);f3=sign(U5-j9)/max(abs(k9),1./sb);A4=f3>=.0?o5.y-(1.-o5.x)*k9:o5.y+o5.x*k9;}f P;P.x=max(o5.x,.0)+rb;P.y=-o5.y+g6;P.z=f3;P.w=A4;return P;}
#endif
#ifdef EB
e g T4(f P p5){g f3=P.z;g A4=max(P.w,.0);g q5=f3>=.0?J3(A4):.0;if(abs(f3)<A7){g x=abs(P.x)-rb;g y=-P.y+g6;g z2=(y-A4)*0.5984134206;i t=A4+z2*E1(0.20888568955,0.62665706865,1.04442844776,1.46219982687);i u=t*-f3+(y*f3+x);i de=E1(J3(u[0]),J3(u[1]),J3(u[2]),J3(u[3]));i ub=t*5.09593080173+-2.54796540086;i ee=exp2(-ub*ub);q5+=dot(de,ee)*z2;}return q5*sign(P.x);}e g T6(f P p5){float q5=1.;float fe=(1.-g6)+P.x;q5-=J3(fe);float ge=1.-P.y;q5-=J3(ge);return q5;}
#endif
#if defined(HB)&&defined(DB)
e g Y6(c l9,c V4 p5){c m9=round(l9);i P=r5(ND,ce,m9,V4);P=E1(a5(P.x),a5(P.y),a5(P.z),a5(P.w));P.xw=mix(P.xw,P.yz,r1(l9.x+.5-m9.x));P.x=mix(P.w,P.x,r1(l9.y+.5-m9.y));return J3(P.x);}
#endif
#if defined(AB)&&defined(LC)
e g0 B4(int vb){return g0(vb&((1<<Pa)-1),vb>>Pa);}e float wb(V D0,c he){c M1=C0(D0,he);return(abs(M1.x)+abs(M1.y))*(1./dot(M1,M1));}e bool F6(f h6,f n9,int K,j1(uint)D2,j1(c)ie
#ifndef CB
,j1(f)m1
#else
,j1(c0)i6
#endif
v5){int C7=int(h6.x);float l1=h6.y;float o9=h6.z;int xb=floatBitsToInt(h6.w)>>2;int j6=floatBitsToInt(h6.w)&3;int p9=min(C7,xb-1);int R3=K*xb+p9;H3 C4=x1(CC,B4(R3));uint Z=v4(C4.w);M q9=w0(TC,Ea(Z));c yb=uintBitsToFloat(q9.xy);D2=q9.z&0xffffu;uint zb=q9.w;V D0=D1(uintBitsToFloat(w0(KB,D2*4u)));M S3=w0(KB,D2*4u+1u);c S0=uintBitsToFloat(S3.xy);float k2=uintBitsToFloat(S3.z);float l2=uintBitsToFloat(S3.w);uint Ab=Z&S2;if(Ab!=0u){C7=int(n9.x);l1=n9.y;o9=n9.z;}if(C7!=p9){int Bb=R3+C7-p9;H3 Cb=x1(CC,B4(Bb));if((v4(Cb.w)&(S2|0xffffu))!=(Z&(S2|0xffffu))){bool je=k2==.0||yb.x!=.0;if(je){R3=int(zb);C4=x1(CC,B4(R3));}}else{R3=Bb;C4=Cb;}Z=(v4(C4.w)&~S2)|Ab;}float O0;
#ifdef EB
float k6;float d1;if((Z&Z2)==l7&&j6==o7){uint Db=v4(C4.z);float g3=float(Db&0xffffu);float O1=float(Db>>16);g0 D7=g0(-g3-1.,O1-g3+1.);if((Z&S2)!=0u)D7=-D7;H3 Eb=x1(CC,B4(R3+D7.x));H3 r9=x1(CC,B4(R3+D7.y));if((v4(r9.w)&(S2|0xffffu))!=(v4(Eb.w)&(S2|0xffffu))){r9=x1(CC,B4(int(zb)));}k6=Z4(Eb.z);float Fb=Z4(r9.z);d1=Fb-k6;if(abs(d1)>N2)d1-=g7*sign(d1);float v9=O1+1.-float(Qa);float Gb=clamp(round(abs(d1)/N2*v9),1.,v9-1.);float l6=v9-Gb;if(g3<=l6){d1=-(N2*sign(d1)-d1);O1=l6;if(g3==l6)l1=-l1;}else if(g3==l6+1.){g3=.0;O1=.0;l1=.0;}else{g3-=l6+2.;O1=Gb;}if(g3==O1){O0=Fb;}else{O0=k6+d1*(g3/O1);}}else
#endif
{O0=Z4(C4.z);}c A2=c(sin(O0),-cos(O0));c Hb=Z4(C4.xy);c E7=c(0,0);if(l2!=.0){l2=max(l2,(X8/3.)/length(C0(D0,A2)));}if(k2!=.0){l1*=sign(determinant(D0));if((Z&n7)!=0u)l1=min(l1,.0);if((Z&Va)!=0u)l1=max(l1,.0);float T3=l2!=.0?l2:wb(D0,A2)*p3;g Ib=1.;if(T3>k2&&l2==.0){Ib=d4(k2)/d4(T3);k2=T3;}c D4=A2*(k2+T3);
#ifndef CB
float x=l1*(k2+T3);m1.xy=(1./(T3*2.))*(c(x,-x)+k2)+.5;m1.zw=L5(.0);
#endif
uint w9=Z&Z2;if(w9>k7){int m6=2;if((Z&Y8)==0u)m6=-m6;if((Z&S2)!=0u)m6=-m6;g0 ke=B4(R3+m6);H3 le=x1(CC,ke);float me=Z4(le.z);float n6=abs(me-O0);if(n6>N2)n6=g7-n6;bool F7=(Z&Y8)!=0u;bool ne=(Z&n7)!=0u;float Jb=n6*(F7==ne?-.5:.5)+O0;c G7=c(sin(Jb),-cos(Jb));float x9=wb(D0,G7);float o6=cos(n6*.5);float y9;if((w9==td)||(w9==ud&&o6>=.25)){float oe=(Z&m7)!=0u?1.:.25;y9=k2*(1./max(o6,oe));}else{y9=k2*o6+x9*.5;}float z9=y9+x9*p3;if((Z&Ua)!=0u){float Kb=k2+T3;float pe=T3*.125;if(Kb<=z9*o6+pe){float qe=Kb*(1./o6);D4=G7*qe;}else{c A9=G7*z9;c re=c(dot(D4,D4),dot(A9,A9));D4=C0(re,inverse(V(D4,A9)));}}c se=abs(l1)*D4;float Lb=(z9-dot(se,G7))/(x9*(p3*2.));
#ifndef CB
if((Z&n7)!=0u)m1.y=Lb;else m1.x=Lb;
#endif
}
#ifndef CB
m1.xy*=Ib;m1.y=max(m1.y,1e-4);if(l2!=.0){m1.x=g6-m1.x;}
#endif
E7=C0(D0,l1*D4);if(j6!=o7)return false;}else{
#ifndef CB
m1=f(o9,-1.,.0,.0);
#ifdef EB
if(l2!=.0){m1.y=g6;m1.z=sb;m1.w=o9;if((Z&Z2)==l7&&j6==o7){if(d1<.0){k6+=d1;d1=-d1;}float h3=O0-k6;h3=mod(h3+U5,g7)-U5;h3=clamp(h3,.0,d1);if(h3>d1*.5){h3=d1-h3;}c B7=c(sin(h3),cos(h3));
#if 0
float y1=1.+.33*log2(U5/(N2-min(d1,N2-N2/16.)));f te=tb(d1,B7,.5*(y1/3.));float ue=T4(te w1);float ve=a5(ue);float we=(.5-ve)*(X8*2.);float xe=y1/max(we,y1);l1*=xe;
#endif
m1=tb(d1,B7,l1);}E7=C0(D0,(l1*l2)*A2);}else
#endif
{E7=sign(C0(l1*A2,inverse(D0)))*p3;}if(bool(Z&S2)!=bool(Z&vd)){m1.x=-m1.x;}
#endif
if(j6==Xa)Hb=yb;if((Z&Ta)!=0u&&j6!=Wa){return false;}}ie=C0(D0,Hb)+E7+S0;
#ifdef CB
M U3=w0(KB,D2*4u+2u);i6=Q1(U3.x);
#else
m1.xy=mix(m1.xy,c(1.,-1.),id(q.nd!=0u));
#endif
return true;}
#endif
#if defined(AB)&&defined(GB)
e c g8(a0 w5,j1(uint)D2
#ifdef CB
,j1(c0)i6
#else
,j1(g)ye
#endif
v5){D2=floatBitsToUint(w5.z)&0xffffu;
#ifdef CB
M U3=w0(KB,D2*4u+2u);i6=Q1(U3.x);
#else
ye=Q8(floatBitsToInt(w5.z)>>16);
#endif
c x5=w5.xy;V D0=D1(uintBitsToFloat(w0(KB,D2*4u)));M S3=w0(KB,D2*4u+1u);c S0=uintBitsToFloat(S3.xy);x5=C0(D0,x5)+S0;return x5;}
#endif
#if defined(AB)&&defined(DB)
e c f8(a0 w5,j1(uint)D2,
#ifdef CB
j1(c0)i6,
#endif
j1(c)ze v5){D2=floatBitsToUint(w5.z)&0xffffu;M U3=w0(KB,D2*4u+2u);
#ifdef CB
i6=Q1(U3.x);
#endif
c x5=w5.xy;a0 p6=uintBitsToFloat(U3.yzw);ze=x5*p6.x+p6.yz;return x5;}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive