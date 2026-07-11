#pragma once

#include "color_ramp.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char color_ramp[] = R"===(#ifdef AB
U0(f0)
#ifdef K8
i0(0,uint,ZC);i0(1,uint,AD);i0(2,uint,BD);i0(3,uint,CD);
#else
i0(0,M,BC);
#endif
V0
#endif
n1 n0 H(0,i,S5);o1
#ifdef AB
O2 P2 E3 F3 i dd(uint j){return va((M(j,j,j,j)>>M(16,8,0,24))&0xffu)/255.;}p1(AE,f0,B,n,K){
#ifdef K8
l0(K,B,ZC,uint);l0(K,B,AD,uint);l0(K,B,BD,uint);l0(K,B,CD,uint);M BC=M(ZC,AD,BD,CD);
#else
l0(K,B,BC,M);
#endif
L(S5,i);int e7=n>>1;float x=float(e7<=1?BC.x&0xffffu:BC.x>>16)/65536.;float L8=(n&1)==0?.0:1.;if(q.wa<.0){L8=1.-L8;}uint T5=BC.y;float y=float(T5&~ed)+L8;if((T5&xa)!=0u&&e7==0){if((T5&M8)!=0u)x=.0;else x-=ya;}if((T5&za)!=0u&&e7==3){if((T5&M8)!=0u)x=1.;else x+=ya;}S5=dd(e7<=1?BC.z:BC.w);f T=f7(c(x,y),2.,q.wa);Q(S5);g1(T);}
#endif
#ifdef HB
Q2 R2 e2(i,BE){O(S5,i);f2(S5);}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive