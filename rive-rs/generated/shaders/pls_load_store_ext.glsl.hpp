#pragma once

#include "pls_load_store_ext.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char pls_load_store_ext[] = R"===(#ifdef AB
void main(){gl_Position=vec4(mix(vec2(-1,1),vec2(1,-1),equal(gl_VertexID&ivec2(1,2),ivec2(0))),0,1);}
#endif
#ifdef HB
#extension GL_EXT_shader_pixel_local_storage:require
#ifdef GL_ARM_shader_framebuffer_fetch
#extension GL_ARM_shader_framebuffer_fetch:require
#else
#extension GL_EXT_shader_framebuffer_fetch:require
#endif
#ifdef RD
#if __VERSION__>=310
layout(binding=0,std140)uniform Vf{uniform highp vec4 Je;}Ke;
#else
uniform mediump vec4 SD;
#endif
#endif
#ifdef GL_EXT_shader_pixel_local_storage
#ifdef FD
__pixel_local_inEXT z1
#else
__pixel_local_outEXT z1
#endif
{layout(rgba8)mediump vec4 H0;layout(r32ui)highp uint q1;layout(rgba8)mediump vec4 N3;layout(r32ui)highp uint y4;};
#ifndef GL_ARM_shader_framebuffer_fetch
#ifdef TD
layout(location=0)inout mediump vec4 H9;
#endif
#endif
#ifdef FD
layout(location=0)out mediump vec4 H9;
#endif
void main(){
#ifdef RD
#if __VERSION__>=310
H0=Ke.Je;
#else
H0=SD;
#endif
#endif
#ifdef TD
#ifdef GL_ARM_shader_framebuffer_fetch
H0=gl_LastFragColorARM;
#else
H0=H9;
#endif
#endif
#ifdef NE
y4=0u;
#endif
#ifdef OE
q1=0u;
#endif
#ifdef FD
H9=H0;
#endif
}
#else
layout(location=0)out mediump vec4 Le;void main(){Le=vec4(0,1,0,1);}
#endif
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive