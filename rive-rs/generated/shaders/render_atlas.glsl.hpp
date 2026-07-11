#pragma once

#include "render_atlas.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char render_atlas[] = R"===(#ifdef AB
U0(f0)i0(0,f,MB);i0(1,f,NB);V0
#endif
n1 n0 H(0,f,D);o1
#ifdef AB
p1(PE,f0,B,n,K){l0(n,B,MB,f);l0(n,B,NB,f);L(D,f);f T;uint U;c J;if(F6(MB,NB,K,U,J,D Y1)){M U3=w0(KB,U*4u+2u);a0 p6=uintBitsToFloat(U3.yzw);J=J*p6.x+p6.yz;T=f7(J,q.La.x,q.La.y);}else{T=f(q.C1,q.C1,q.C1,q.C1);}Q(D);g1(T);}
#endif
#ifdef HB
#ifdef QE
e2(float,RE){O(D,f);f2(T4(D w1));}
#endif
#ifdef SE
e2(float,TE){O(D,f);f2(T6(D w1));}
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive