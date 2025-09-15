#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Compiler.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Warnings.h"
PNSLR_SUPPRESS_WARN
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #undef WIN32_LEAN_AND_MEAN
    #include "Dependencies/Panshilar/Bindings/C/Panshilar.h"
    #include "Dependencies/Dvaarpaal/Source/Dvaarpaal.h"
PNSLR_UNSUPPRESS_WARN
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Primitives.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Macros.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    DVRPL_WindowData wnd = DVRPL_CreateWindow((DVRPL_WindowCreationOptions){
        .posX = 10, .posY = 10,
        .title = "Test Window",
        .sizeX = 800, .sizeY = 600,
        .parent = {0},
        .msaa = false,
        .bgColR = 38, .bgColG = 38, .bgColB = 51, .bgColA = 255,
    });

    Sleep(3000); // 3 seconds

    DVRPL_DestroyWindow(&wnd);

    return 0;
}
