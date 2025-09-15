#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION

#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Compiler.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Platforms.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Warnings.h"
PNSLR_SUPPRESS_WARN
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #undef WIN32_LEAN_AND_MEAN
PNSLR_UNSUPPRESS_WARN
#include "Dependencies/Panshilar/Source/Panshilar.h"
#include "Dependencies/Dvaarpaal/Source/Dvaarpaal.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    DVRPL_WindowData wnd = DVRPL_CreateWindow((DVRPL_WindowCreationOptions){
        .posX = 10, .posY = 10,
        .title = PNSLR_STRING_LITERAL("Test Window"),
        .sizeX = 800, .sizeY = 600,
        .parent = {0},
        .msaa = false,
        .bgColR = 38, .bgColG = 38, .bgColB = 51, .bgColA = 255,
    });

    Sleep(1000);

    DVRPL_SetFullScreen(&wnd, true, nil, nil, nil, nil);

    Sleep(1000);

    DVRPL_SetFullScreen(&wnd, false, nil, nil, nil, nil);

    Sleep(1000);

    DVRPL_DestroyWindow(&wnd);

    return 0;
}

// unity build
#include "Dependencies/Dvaarpaal/Source/zzzz_Unity.c"
#include "Dependencies/Panshilar/Source/zzzz_Unity.c"
