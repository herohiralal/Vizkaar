#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION
#define VZKR_IMPLEMENTATION
#include "__Prelude.h"

i32 DVRPL_Main(PNSLR_ArraySlice(utf8str) args)
{
    DVRPL_WindowData wnd = DVRPL_CreateWindow((DVRPL_WindowCreationOptions){
        .posX = 10, .posY = 10,
        .title = PNSLR_StringLiteral("Test Window"),
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
