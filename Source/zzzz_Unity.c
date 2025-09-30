#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION
#define VZKR_IMPLEMENTATION
#include "Vizkaar.h"

i32 DVRPL_Main(DVRPL_App app, PNSLR_ArraySlice(utf8str) args)
{
    // i64 prevTime = PNSLR_NanosecondsSinceUnixEpoch();

    PNSLR_AllocatorError err = PNSLR_AllocatorError_None;
    PNSLR_Allocator tempAllocator = PNSLR_NewAllocator_Arena(PNSLR_GetAllocator_DefaultHeap(), 16 * 1024 * 1024 /* 16 MiB */, PNSLR_GET_LOC(), &err);
    if (err != PNSLR_AllocatorError_None)
    {
        // failed to create temp allocator
        return -1;
    }

    MZNT_Renderer* renderer = MZNT_CreateRenderer(
    (MZNT_RendererConfiguration)
    {
        .type = MZNT_RendererType_Vulkan,
        .allocator = PNSLR_GetAllocator_DefaultHeap(),
        .appName = PNSLR_StringLiteral("Vizkaar"),
    }, tempAllocator);

    DVRPL_WindowData wnd = DVRPL_CreateWindow((DVRPL_WindowCreationOptions){
        .app = app,
        .posX = 10, .posY = 10,
        .title = PNSLR_StringLiteral("Test Window"),
        .sizeX = 800, .sizeY = 600,
        .parent = {0},
        .msaa = false,
        .acceptDropFiles = true,
        .bgColR = 38, .bgColG = 38, .bgColB = 51, .bgColA = 255,
    });

    MZNT_RendererSurface* wndSrf = MZNT_CreateRendererSurface(renderer, (MZNT_WindowHandle) {.handle = wnd.window.handle}, tempAllocator);

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

            if (evt.ty == DVRPL_EvtTy_DropFile)
            {
                utf8str file = DVRPL_GetDroppedFile(evt.droppedFileId);
                PNSLR_LogIf(PNSLR_StringLiteral("Dropped file: $"), PNSLR_FmtArgs(PNSLR_FmtString(file)), PNSLR_GET_LOC());
            }

            switch (evt.ty)
            {
                case DVRPL_EvtTy_Unknown:    PNSLR_LogI(PNSLR_StringLiteral("EVT: Unknown"),    PNSLR_GET_LOC()); break;
                case DVRPL_EvtTy_Keyboard:   PNSLR_LogI(PNSLR_StringLiteral("EVT: Keyboard"),   PNSLR_GET_LOC()); break;
                case DVRPL_EvtTy_MouseWheel: PNSLR_LogI(PNSLR_StringLiteral("EVT: MouseWheel"), PNSLR_GET_LOC()); break;
                case DVRPL_EvtTy_Touch:      PNSLR_LogI(PNSLR_StringLiteral("EVT: Touch"),      PNSLR_GET_LOC()); break;
                case DVRPL_EvtTy_TextInput:  PNSLR_LogI(PNSLR_StringLiteral("EVT: TextInput"),  PNSLR_GET_LOC()); break;
                case DVRPL_EvtTy_DropFile:   PNSLR_LogI(PNSLR_StringLiteral("EVT: DropFile"),   PNSLR_GET_LOC()); break;
                case DVRPL_EvtTy_Quit:       PNSLR_LogI(PNSLR_StringLiteral("EVT: Quit"),       PNSLR_GET_LOC()); break;
                default:                     PNSLR_LogI(PNSLR_StringLiteral("EVT: ???"),        PNSLR_GET_LOC()); break;
            }
        }

        PNSLR_FreeAll(tempAllocator, PNSLR_GET_LOC(), nil);
    }

    MZNT_DestroyRendererSurface(wndSrf, tempAllocator);

    DVRPL_DestroyWindow(&wnd);

    MZNT_DestroyRenderer(renderer, tempAllocator);

    return 0;
}

// unity build
#include "Dependencies/Panshilar/Source/zzzz_Unity.c"
#include "Dependencies/Dvaarpaal/Source/zzzz_Unity.c"
#include "Dependencies/Muzent/Source/zzzz_Unity.c"
