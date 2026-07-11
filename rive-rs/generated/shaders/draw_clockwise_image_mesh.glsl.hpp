#pragma once

#include "draw_clockwise_image_mesh.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char draw_clockwise_image_mesh[] = R"===(#ifdef AB
U0(a2)i0(0,c,TB);V0 U0(r2)i0(1,c,UB);V0
#endif
n1 n0 H(0,c,q0);o1
#ifdef AB
O2 P2 P4(QB,a2,c2,r2,v2,n){l0(n,c2,TB,c);l0(n,v2,UB,c);L(q0,c);c J=C0(D1(m0.I6),TB)+m0.S0;q0=UB;f T=E2(J);Q(q0);g1(T);}
#endif
#ifdef HB
Q2 B2(x4,Z8,VB);R2 p4 G3(x4,a9,B3)q4 w3 x3 e2(i,OB){O(q0,c);i p7=o4(VB,B3,q0);p7=E1(Y3(p7),p7.w*m0.G2);f2(p7);}
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive