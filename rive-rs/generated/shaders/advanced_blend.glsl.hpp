#pragma once

#include "advanced_blend.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char advanced_blend[] = R"===(#ifdef HB
#ifdef KD
layout(
#ifdef SB
blend_support_all_equations
#else
blend_support_multiply,blend_support_screen,blend_support_overlay,blend_support_darken,blend_support_lighten,blend_support_colordodge,blend_support_colorburn,blend_support_hardlight,blend_support_softlight,blend_support_difference,blend_support_exclusion
#endif
)out;
#endif
#ifdef FB
#ifdef SB
g Z7(A A0){return min(min(A0.x,A0.y),A0.z);}g R9(A A0){return max(max(A0.x,A0.y),A0.z);}g a8(A A0){return dot(A0,L0(.30,.59,.11));}g S9(A A0){return R9(A0)-Z7(A0);}A oc(A j){g o3=a8(j);g T9=Z7(j);g U9=R9(j);if(T9<.0)j=o3+((j-o3)*o3)/(o3-T9);if(U9>1.)j=o3+((j-o3)*(1.-o3))/(U9-o3);return j;}A c8(A N4,A d8){g pc=a8(N4);g qc=a8(d8);g rc=qc-pc;A j=N4+L0(rc);return oc(j);}A V9(A N4,A sc,A d8){g tc=Z7(N4);g W9=S9(N4);g uc=S9(sc);A j;if(W9>.0){j=(N4-tc)*uc/W9;}else{j=L0(.0);}return c8(j,d8);}
#endif
A vc(A e0,i X0,c0 e8){A h0=Y3(X0);A M0;switch(e8){case wc:M0=e0.xyz*h0.xyz;break;case xc:M0=e0.xyz+h0.xyz-e0.xyz*h0.xyz;break;case yc:{for(int C=0;C<3;++C){if(h0[C]<=.5)M0[C]=2.*e0[C]*h0[C];else M0[C]=1.-2.*(1.-e0[C])*(1.-h0[C]);}break;}case zc:M0=min(e0.xyz,h0.xyz);break;case Ac:M0=max(e0.xyz,h0.xyz);break;case Bc:{X0.xyz=clamp(X0.xyz,L0(.0),X0.www);A X9=clamp(1.-e0,L0(.0),L0(1.))*X0.w;M0=mix(min(L0(1.),X0.xyz/X9),sign(X0.xyz),equal(X9,L0(.0)));break;}case Dc:{e0=clamp(e0,L0(.0),L0(1.));X0.xyz=clamp(X0.xyz,L0(.0),X0.www);if(X0.w==.0)X0.w=1.;A Y9=X0.w-X0.xyz;M0=1.-mix(min(L0(1.),Y9/(e0*X0.w)),sign(Y9),equal(e0,L0(.0)));break;}case Ec:{for(int C=0;C<3;++C){if(e0[C]<=.5)M0[C]=2.*e0[C]*h0[C];else M0[C]=1.-2.*(1.-e0[C])*(1.-h0[C]);}break;}case Fc:{for(int C=0;C<3;++C){if(e0[C]<=0.5)M0[C]=h0[C]-(1.-2.*e0[C])*h0[C]*(1.-h0[C]);else if(h0[C]<=.25)M0[C]=h0[C]+(2.*e0[C]-1.)*h0[C]*((16.*h0[C]-12.)*h0[C]+3.);else M0[C]=h0[C]+(2.*e0[C]-1.)*(sqrt(h0[C])-h0[C]);}break;}case Gc:M0=abs(h0.xyz-e0.xyz);break;case Hc:M0=e0.xyz+h0.xyz-2.*e0.xyz*h0.xyz;break;
#ifdef SB
case Ic:if(SB){e0.xyz=clamp(e0.xyz,L0(.0),L0(1.));M0=V9(e0.xyz,h0.xyz,h0.xyz);}break;case Jc:if(SB){e0.xyz=clamp(e0.xyz,L0(.0),L0(1.));M0=V9(h0.xyz,e0.xyz,h0.xyz);}break;case Kc:if(SB){e0.xyz=clamp(e0.xyz,L0(.0),L0(1.));M0=c8(e0.xyz,h0.xyz);}break;case Lc:if(SB){e0.xyz=clamp(e0.xyz,L0(.0),L0(1.));M0=c8(h0.xyz,e0.xyz);}break;
#endif
}return M0;}e A O4(A e0,i X0,c0 e8){A M0=vc(e0,X0,e8);G B5=Z3(X0.w,1.-X0.w);return C0(Mc(M0,e0),B5);}
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive