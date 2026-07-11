#pragma once

#include "bezier_utils.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char bezier_utils[] = R"===(#ifndef ja
#define ja f
#endif
#ifndef L5
#define L5 c
#endif
e float F8(c k,c b){float Uc=dot(k,b);float ka=dot(k,k)*dot(b,b);return(ka==.0)?1.:clamp(Uc*inversesqrt(ka),-1.,1.);}e void Vc(c o0,c p0,c x0,c y0,j1(c)o,j1(c)r,j1(c)L1){L1=p0-o0;c M5=x0-p0;c Z6=y0-o0;r=M5-L1;o=-3.*M5+Z6;}e V G8(c o0,c p0,c x0,c y0){V t;t[0]=(any(notEqual(o0,p0))?p0:any(notEqual(p0,x0))?x0:y0)-o0;t[1]=y0-(any(notEqual(y0,x0))?x0:any(notEqual(x0,p0))?p0:o0);return t;}e float Wc(c o0,c p0,c x0,c y0,float c1,float Xc){c o,r,L1;Vc(o0,p0,x0,y0,o,r,L1);c N5=3.*(((o*c1)+2.*r)*c1+L1);float la=length(N5);if(la==.0){return.0;}N5*=1./la;float a7=2.*dot(o,N5);float O5=3.*(a7*c1+4.*dot(r,N5))*c1+6.*dot(L1,N5);float H8=min(c1,1.-c1);float Yc=(a7*H8*H8+O5)*H8;float ma=min(Xc,Yc*.9999);float z2;if(a7==.0){z2=ma/O5;}else{float d0=1./a7;float b=O5*d0,A0=-ma*d0;float P5=(-1./3.)*b,Q5=.5*A0;float na=Q5*Q5-P5*P5*P5;if(na<.0){float c7=sqrt(P5);float O0=acos(Q5/(c7*c7*c7));z2=-2.*c7*cos(O0*(1./3.)+(-N2*2./3.));}else{float o=pow(abs(Q5)+sqrt(na),1./3.);if(Q5<.0)o=-o;z2=o!=.0?o+P5/o:.0;}}z2=abs(z2);f t0011=c1+ja(-z2,-z2,z2,z2);f oa=(o.xyxy*t0011+2.*r.xyxy)*t0011+L1.xyxy;V d2=G8(o0,p0,x0,y0);c Zc=t0011.x<1e-3?d2[0]:oa.xy;c ad=t0011.z>1.-1e-3?d2[1]:oa.zw;return acos(F8(Zc,ad));}e float d7(float k,float b){k=b<.0?-k:k;b=abs(b);return k>.0?(k<b?k/b:1.):.0;}float bd(c o0,c p0,c x0,c y0,j1(float)I8){c pa=y0-o0;float qa=length(y0-o0);if(qa==.0){I8=.5;return.0;}c A2=L5(-pa.y,pa.x)/qa;float ra=dot(A2,x0-o0);float C3=dot(A2,p0-o0);float D3=C3-ra;
#if 0
float k=3.*D3;float sa=D3+C3;float A0=C3;float V1=sqrt(max(D3*D3+ra*C3,.0));if(sa<.0)V1=-V1;V1+=sa;c R5=L5(d7(V1,k),d7(A0,V1));c Y4=3.*(R5*(R5*(R5*D3-(C3+D3))+C3));Y4=abs(Y4);I8=Y4.x>Y4.y?R5.x:R5.y;return max(Y4.x,Y4.y);
#else
float ta=3.*D3;float r=-C3-D3;float L1=C3;float t=.5;for(int C=0;C<3;++C){float ua=ta*t;t=d7(ua*t-L1,2.*(ua+r));}I8=t;return abs(t*(t*(t*ta+3.*r)+3.*L1));
#endif
}
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive