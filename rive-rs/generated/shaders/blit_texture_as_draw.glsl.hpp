#pragma once

#include "blit_texture_as_draw.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char blit_texture_as_draw[] = R"===(n1
#ifndef OC
n0 H(0,c,q0);
#endif
o1
#ifdef AB
O2 P2 E3 F3 p1(ZD,f0,B,n,K){c S1;S1.x=(n&1)==0?-1.:1.;S1.y=(n&2)==0?-1.:1.;
#ifndef OC
L(q0,c);q0.x=S1.x*.5+.5;q0.y=S1.y*-.5+.5;Q(q0);
#endif
f T=f(S1,0,1);g1(T);}
#endif
#ifdef HB
Q2 B2(0,0,YC);R2
#ifndef OC
p4 G3(0,1,cd)q4
#endif
e2(i,MD){i J8;
#ifndef OC
O(q0,c);J8=T1(YC,cd,q0,.0);
#else
J8=x1(YC,g0(floor(B0.xy)));
#endif
f2(J8);}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive