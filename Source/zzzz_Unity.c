#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION
#define VZKR_IMPLEMENTATION
#include "__Prelude.h"

i32 DVRPL_Main(PNSLR_ArraySlice(utf8str) args)
{
    // i64 prevTime = PNSLR_NanosecondsSinceUnixEpoch();

    PNSLR_AllocatorError err = PNSLR_AllocatorError_None;
    PNSLR_Allocator tempAllocator = PNSLR_NewAllocator_Arena(PNSLR_GetAllocator_DefaultHeap(), 16 * 1024 * 1024 /* 16 MiB */, PNSLR_GET_LOC(), &err);
    if (err != PNSLR_AllocatorError_None)
    {
        // failed to create temp allocator
        return -1;
    }

    DVRPL_WindowData wnd = DVRPL_CreateWindow((DVRPL_WindowCreationOptions){
        .posX = 10, .posY = 10,
        .title = PNSLR_StringLiteral("Test Window"),
        .sizeX = 800, .sizeY = 600,
        .parent = {0},
        .msaa = false,
        .bgColR = 38, .bgColG = 38, .bgColB = 51, .bgColA = 255,
    });

    PNSLR_FreeAll(tempAllocator, PNSLR_GET_LOC(), nil);

    b8 running = true, fullscreen = false;
    while (running)
    {
        // i64 newTime = PNSLR_NanosecondsSinceUnixEpoch();
        // f32 dt = (f32) ((f64) (newTime - prevTime) / 1000000000.0);
        // prevTime = newTime;

        DVRPL_GatherEvents(tempAllocator);
        PNSLR_ArraySlice(DVRPL_Event) evts = DVRPL_GetEvents();
        for (i64 i = 0; i < evts.count; i++)
        {
            DVRPL_Event evt = evts.data[i];

            // alt+f4 or quit event
            if (evt.ty == DVRPL_EvtTy_Quit ||
                (evt.ty == DVRPL_EvtTy_Keyboard &&
                    evt.keyCode == DVRPL_KeyCode_F4 &&
                    !!(evt.keyModifiers & DVRPL_KeyModifier_Alt)))
                running = false;


            // alt+enter
            if (evt.ty == DVRPL_EvtTy_Keyboard &&
                evt.keyCode == DVRPL_KeyCode_Enter &&
                !!(evt.keyModifiers & DVRPL_KeyModifier_Alt))
            {
                fullscreen = !fullscreen;
                DVRPL_SetFullScreen(&wnd, fullscreen, nil, nil, nil, nil);
            }
        }

        PNSLR_FreeAll(tempAllocator, PNSLR_GET_LOC(), nil);
    }

    DVRPL_DestroyWindow(&wnd);

    return 0;
}

// unity build
#include "Dependencies/Dvaarpaal/Source/zzzz_Unity.c"
#include "Dependencies/Panshilar/Source/zzzz_Unity.c"
