#ifndef MZNT_MAIN_H
#define MZNT_MAIN_H

#include "Intrinsics.h"
#include "Panshilar.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__cplusplus)
    #define PNSLR_ALIGNAS(x) alignas(x)
#elif defined(_MSC_VER)
    #define PNSLR_ALIGNAS(x) __declspec(align(x))
#elif defined(__clang__) || defined(__GNUC__)
    #define PNSLR_ALIGNAS(x) __attribute__((aligned(x)))
#else
    #error "UNSUPPORTED COMPILER!";
#endif

#undef PNSLR_ALIGNAS

#ifdef __cplusplus
} // extern c
#endif

#endif//MZNT_MAIN_H
