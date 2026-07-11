#pragma once

#include "tessellate.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char tessellate[] = R"===(#define Ze 10
#ifdef AB
U0(f0)i0(0,f,UC);i0(1,f,VC);i0(2,f,HC);
#ifdef K8
i0(3,uint,GD);i0(4,uint,HD);i0(5,uint,ID);i0(6,uint,JD);
#else
i0(3,M,RB);
#endif
V0
#endif
n1 n0 H(0,f,z5);n0 H(1,f,A5);n0 H(2,f,W3);n0 H(3,a0,L4);K2 H(4,uint,B6);o1
#ifdef AB
O2 n5(T2,a6,JC);P2 Q3(a6,P8)E3 P3(Za,ae,KB);P3(ab,be,TC);F3 p1(WE,f0,B,n,K){l0(K,B,UC,f);l0(K,B,VC,f);l0(K,B,HC,f);
#ifdef K8
l0(K,B,GD,uint);l0(K,B,HD,uint);l0(K,B,ID,uint);l0(K,B,JD,uint);M RB=M(GD,HD,ID,JD);
#else
l0(K,B,RB,M);
#endif
L(z5,f);L(A5,f);L(W3,f);L(L4,a0);L(B6,uint);c o0=UC.xy;c p0=UC.zw;c x0=VC.xy;c y0=VC.zw;bool Yb=n<4;float y=Yb?HC.z:HC.w;int I9=int(Yb?RB.x:RB.y);
#ifdef Da
int Zb=I9<<16;if(RB.z==0xffffffffu){--Zb;}float S7=float(Zb>>16);
#else
float S7=float(I9<<16>>16);
#endif
float T7=float(I9>>16);c S1=c((n&1)==0?S7:T7,(n&2)==0?y+1.:y);if((T7-S7)*q.Ja<.0){S1.y=2.*y+1.-S1.y;}uint q2=RB.z&0x3ffu;uint ac=(RB.z>>10)&0x3ffu;uint O1=RB.z>>20;uint Z=RB.w;uint U=Z!=wd?w0(TC,Ea(Z)).z:0u;M S3=U!=0u?w0(KB,U*4u+1u):M(0u,0u,0u,0u);float k2=uintBitsToFloat(S3.z);float l2=uintBitsToFloat(S3.w);if(l2!=.0&&k2==.0){float bc;float af=bd(o0,p0,x0,y0,bc);float J9=l2*(1./X8);float bf=Wc(o0,p0,x0,y0,bc,J9);float C6=1.-bf*(1./N2);float cf=dot(y0-o0,y0-o0)/(J9*J9);float df=(cf-1.)*.5;C6=min(C6,df);C6=min(C6,.99);float ef=.5*C6;float x=a5(ef)*-2.+1.;float cc=d7(x*l2,af);f dc=mix(o0.xyxy,y0.xyxy,f(1./3.,1./3.,2./3.,2./3.));p0=mix(p0,dc.xy,cc);x0=mix(x0,dc.zw,cc);}if((Z&sd)!=0u){V ec=D1(uintBitsToFloat(w0(KB,U*4u)));c fc=C0(ec,-2.*p0+x0+o0);c gc=C0(ec,-2.*x0+y0+p0);float W0=max(dot(fc,fc),dot(gc,gc));float e4=max(ceil(sqrt(.75*4.*sqrt(W0))),1.);q2=min(uint(e4),q2);}uint U7=q2+ac+O1-1u;V d2=G8(o0,p0,x0,y0);float O0=acos(F8(d2[0],d2[1]));float m3=O0/float(ac);float K9=determinant(V(x0-o0,y0-p0));if(K9==.0)K9=determinant(d2);if(K9<.0)m3=-m3;z5=f(o0,p0);A5=f(x0,y0);W3=f(float(U7)-abs(T7-S1.x),float(U7),(O1<<10)|q2,m3);if(O1>1u){V L9=V(d2[1],HC.xy);float ff=acos(F8(L9[0],L9[1]));float hc=float(O1);if((Z&(Z2|m7))==(k7|m7)){hc-=2.;}float M9=ff/hc;if(determinant(L9)<.0)M9=-M9;L4.xy=HC.xy;L4.z=M9;}if(T7<S7){Z|=S2;}B6=Z;f T=f7(S1,2./qd,q.Ja);Q(z5);Q(A5);Q(W3);Q(L4);Q(B6);g1(T);}
#endif
#ifdef HB
Q2 R2 e2(H3,XE){O(z5,f);O(A5,f);O(W3,f);O(L4,a0);O(B6,uint);c o0=z5.xy;c p0=z5.zw;c x0=A5.xy;c y0=A5.zw;V d2=G8(o0,p0,x0,y0);float gf=max(floor(W3.x),.0);float U7=W3.y;uint ic=uint(W3.z);float q2=float(ic&0x3ffu);float O1=float(ic>>10);float m3=W3.w;uint Z=B6;float X3=U7-O1;float X1=gf;if(X1<=X3){Z&=~Z2;}else{o0=p0=x0=y0;d2=V(d2[1],L4.xy);q2=1.;X1-=X3;X3=O1;m3=L4.z;if((Z&Z2)>k7){if(X1<2.5)Z|=Y8;if(X1>1.5&&X1<3.5)Z|=Ua;}else if((Z&m7)!=0u||(Z&Z2)==l7){X3-=2.;--X1;}Z|=m3<.0?n7:Va;}c V7;float O0=.0;if(X1==.0||X1==X3||(Z&Z2)>k7){bool F7=X1<X3*.5;V7=F7?o0:y0;O0=Ga(F7?d2[0]:d2[1]);}else if((Z&Ta)!=0u){V7=p0;}else{float c1,M4;if(q2==X3){c1=X1/q2;M4=.0;}else{c o,r,L1=p0-o0;c M5=y0-o0;c Z6=x0-p0;r=Z6-L1;o=-3.*Z6+M5;c hf=r*(q2*2.);c O5=L1*(q2*q2);float W7=.0;float jf=min(q2-1.,X1);c N9=normalize(d2[0]);float kf=-abs(m3);float lf=(1.+X1)*abs(m3);for(int B5=Ze-1;B5>=0;--B5){float D6=W7+exp2(float(B5));if(D6<=jf){c O9=D6*o+hf;O9=D6*O9+O5;float mf=dot(normalize(O9),N9);float P9=D6*kf+lf;P9=min(P9,N2);if(mf>=cos(P9))W7=D6;}}float nf=W7/q2;float jc=X1-W7;float X7=acos(clamp(N9.x,-1.,1.));X7=N9.y>=.0?X7:-X7;O0=jc*m3+X7;c A2=c(sin(O0),-cos(O0));float k=dot(A2,o),Y7=dot(A2,r),A0=dot(A2,L1);float of=max(Y7*Y7-k*A0,.0);float V1=sqrt(of);if(Y7>.0)V1=-V1;V1-=Y7;float kc=-.5*V1*k;c Q9=(abs(V1*V1+kc)<abs(k*A0+kc))?c(V1,k):c(A0,V1);M4=(Q9.y!=.0)?Q9.x/Q9.y:.0;M4=clamp(M4,.0,1.);if(jc==.0)M4=.0;c1=max(nf,M4);}c pf=d5(o0,p0,c1);c lc=d5(p0,x0,c1);c qf=d5(x0,y0,c1);c mc=d5(pf,lc,c1);c nc=d5(lc,qf,c1);V7=d5(mc,nc,c1);if(c1!=M4)O0=Ga(nc-mc);}H3 E6;E6.xy=N8(V7);if((Z&Z2)==l7){E6.z=O8((uint(X3)<<16)|uint(X1));}else{E6.z=N8(mod(O0,g7));}E6.w=O8(Z);f2(E6);}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive