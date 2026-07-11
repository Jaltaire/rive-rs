#pragma once

#include "specialization.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char specialization[] = R"===(#ifndef UE
layout(constant_id=Cd)const bool Pe=true;layout(constant_id=Dd)const bool Qe=true;layout(constant_id=Ed)const bool Re=true;layout(constant_id=Fd)const bool Se=true;layout(constant_id=Gd)const bool Te=true;layout(constant_id=Hd)const bool Ue=true;layout(constant_id=Id)const bool Ve=true;layout(constant_id=Jd)const bool We=true;layout(constant_id=Kd)const bool Xe=true;layout(constant_id=Ld)const uint Ye=0;
#define R Pe
#define BB Qe
#define FB Re
#define EB Se
#define EC Te
#define SC Ue
#define SB Ve
#define QC We
#define KC Xe
#define RC Ye
#else
#define R true
#define BB true
#define FB true
#define EB true
#define EC true
#define SC true
#define SB true
#define QC true
#define KC true
#define RC 0
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive