#define DVRPL_EXECUTABLE_IMPL_ANY VzkrMain
#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION
#define MZNT_IMPLEMENTATION
#define VZKR_IMPLEMENTATION
#include "Vizkaar.h"

i32 VzkrMain(DVRPL_App app, PNSLR_ArraySlice(utf8str) args)
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

    MZNT_RendererSurface* wndSrf = MZNT_CreateRendererSurfaceFromWindow(renderer, (MZNT_WindowHandle) {.handle = wnd.window.handle}, tempAllocator);

    PNSLR_FreeAll(tempAllocator, PNSLR_GET_LOC(), nil);

    b8 running = true, fullscreen = false;
    while (running)
    {
        // i64 newTime = PNSLR_NanosecondsSinceUnixEpoch();
        // f32 dt = (f32) ((f64) (newTime - prevTime) / 1000000000.0);
        // prevTime = newTime;

        DVRPL_GatherEvents(tempAllocator);
        i64 iterator = 0; DVRPL_Event evt;
        while (DVRPL_IterateEvents(&iterator, &evt))
        {
            b8 altBttn = (evt.ty == DVRPL_EvtTy_Keyboard && evt.keyStatus == DVRPL_KeyStatus_Pressed && !!(evt.keyModifiers & DVRPL_KeyModifier_Alt));
            b8 altF4   = (altBttn && evt.keyCode == DVRPL_KeyCode_F4);
            b8 altRet  = (altBttn && evt.keyCode == DVRPL_KeyCode_Enter);

            // alt+f4 or quit event
            if (evt.ty == DVRPL_EvtTy_Quit || altF4)
                running = false;

            // alt+enter
            if (altRet)
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

        if (running)
        {
            i32 resizeIterator = 0; DVRPL_WindowResizeData resizeData;
            while (DVRPL_IterateResizeEvent(&resizeIterator, &resizeData))
            {
                if (resizeData.id.handle != wnd.window.handle)
                {
                    PNSLR_LogEf(PNSLR_StringLiteral("Resize event for unknown window: $"), PNSLR_FmtArgs(PNSLR_FmtU64(resizeData.id.handle, PNSLR_IntegerBase_HexaDecimal)), PNSLR_GET_LOC());
                    continue;
                }

                MZNT_ResizeRendererSurface(wndSrf, resizeData.sizeX, resizeData.sizeY, tempAllocator);
            }

            /*MZNT_RendererCommandBuffer* cmdBuf = */ MZNT_BeginFrame(wndSrf, 0.15f, 0.15f, 0.3f, 1.0f, tempAllocator);
            MZNT_EndFrame(wndSrf, tempAllocator);
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
