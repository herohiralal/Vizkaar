#ifndef __cplusplus
    #error "Please use the C bindings.";
#endif

#ifndef VZKR_CXX_MAIN_H
#define VZKR_CXX_MAIN_H

#include "Intrinsics.hpp"
#include "Panshilar.hpp"
#include "Dvaarpaal.hpp"
#include "Intrinsics.hpp"
#include "Panshilar.hpp"
#include "Muzent.hpp"
#include "Intrinsics.hpp"
#include "Panshilar.hpp"

namespace Vizkaar
{
    using namespace Intrinsics;
    using namespace Panshilar;
    using namespace Dvaarpaal;
    using namespace Intrinsics;
    using namespace Panshilar;
    using namespace Muzent;
    using namespace Intrinsics;
    using namespace Panshilar;

} // namespace end

#endif//VZKR_CXX_MAIN_H
#ifdef PNSLR_CXX_IMPL

#if (_MSC_VER)
    #define PNSLR_STRUCT_OFFSET(type, member) ((u64)&reinterpret_cast<char const volatile&>((((type*)0)->member)))
#elif (__clang__) || (__GNUC__)
    #define PNSLR_STRUCT_OFFSET(type, member) ((u64) offsetof(type, member))
#else
    #error "UNSUPPORTED COMPILER!";
#endif

#undef PNSLR_STRUCT_OFFSET

#endif//PNSLR_CXX_IMPL

