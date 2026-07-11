#pragma once

#include "stencil_draw.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char stencil_draw[] = R"===(#ifdef AB
U0(f0)i0(0,a4,IB);V0 O2 P2 E3 F3 p1(VE,f0,B,n,K){f T=E2(IB.xy);uint Z5=floatBitsToUint(IB.z)&0xffffu;T.z=V8(Z5);g1(T);}
#endif
#ifdef HB
Q2 R2 e2(i,MD){f2(E1(.0));}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive