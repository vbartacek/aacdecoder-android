/* ------------------------------------------------------------------
 * Copyright (C) 1998-2010 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/*

 Filename: fxp_mul32.h

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

------------------------------------------------------------------------------
*/
#ifndef FXP_MUL32
#define FXP_MUL32

#include "oscl_base_macros.h"// has integer values of PV_COMPILER

#if   ((PV_COMPILER == EPV_ARM_GNUC) && (PV_CPU_ARCH_VERSION >=5))
#include "fxp_mul32_arm_gcc.h"

#else/*#else for PV__PROCESSOR__PENTIUM*/

#ifndef C_EQUIVALENT
#define C_EQUIVALENT
#endif/*#endif for C_EQUIVALENT*/

#include "fxp_mul32_c_equivalent.h"

#endif/*#endif for PV__PROCESSOR__PENTIUM*/

#endif   /*  FXP_MUL32  */
