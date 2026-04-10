#define DVRPL_EXECUTABLE_IMPL_ANY VzkrMain
#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION
#define MZNT_IMPLEMENTATION
#define VZKR_IMPLEMENTATION
#include "Vizkaar.h"

#if MZNT_DX12
    __declspec(dllexport) extern const UINT D3D12SDKVersion = D3D12_SDK_VERSION;

    #if PNSLR_X64
        __declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\x64\\";
    #elif PNSLR_ARM64
        __declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\arm64\\";
    #else
        #error "Unsupported architecture."
    #endif
#endif

i32 VzkrMain(DVRPL_App app, PNSLR_ArraySlice(utf8str) args)
{
    PNSLR_SetDefaultLogger(
        PNSLR_GetDefaultLoggerWithOptions(
            PNSLR_LoggerLevel_Info,
            PNSLR_LogOption_None
                | PNSLR_LogOption_IncludeLevel
                | PNSLR_LogOption_IncludeColours
            #if PNSLR_MOBILE
                | PNSLR_LogOption_IncludeFile
            #else
                | PNSLR_LogOption_IncludeFn
            #endif
        )
    );

    // i64 prevTime = PNSLR_NanosecondsSinceUnixEpoch();

    PNSLR_AllocatorError err = PNSLR_AllocatorError_None;
    PNSLR_Allocator tempAllocator = PNSLR_NewAllocator_Arena(PNSLR_GetAllocator_DefaultHeap(), 16 * 1024 * 1024 /* 16 MiB */, PNSLR_GET_LOC(), &err);
    if (err != PNSLR_AllocatorError_None)
    {
        // failed to create temp allocator
        return -1;
    }

    MZNT_Renderer* rendererDx12 = MZNT_CreateRenderer((MZNT_RendererConfiguration)
    {
        .type = MZNT_RendererType_DirectX12,
        .allocator = PNSLR_GetAllocator_DefaultHeap(),
        .appName = PNSLR_StringLiteral("Vizkaar"),
        .appHandle = {.handle = app.handle},
    }, tempAllocator);

    MZNT_Renderer* rendererVk = MZNT_CreateRenderer((MZNT_RendererConfiguration)
    {
        .type = MZNT_RendererType_Vulkan,
        .allocator = PNSLR_GetAllocator_DefaultHeap(),
        .appName = PNSLR_StringLiteral("Vizkaar"),
        .appHandle = {.handle = app.handle},
    }, tempAllocator);

    DVRPL_WindowData wndDx12 = DVRPL_CreateWindow((DVRPL_WindowCreationOptions)
    {
        .app = app,
        .posX = 200, .posY = 150,
        .title = PNSLR_StringLiteral("Test Window Dx12"),
        .sizeX = 800, .sizeY = 600,
        .parent = {0},
        .msaa = false,
        .acceptDropFiles = true,
        .bgColR = 38, .bgColG = 38, .bgColB = 51, .bgColA = 255,
    });

    DVRPL_WindowData wndVk = DVRPL_CreateWindow((DVRPL_WindowCreationOptions)
    {
        .app = app,
        .posX = 200 + 800 + 10, .posY = 150,
        .title = PNSLR_StringLiteral("Test Window Vk"),
        .sizeX = 800, .sizeY = 600,
        .parent = {0},
        .msaa = false,
        .acceptDropFiles = true,
        .bgColR = 38, .bgColG = 38, .bgColB = 51, .bgColA = 255,
    });

    MZNT_RendererSurface* wndSrfDx12 = MZNT_CreateRendererSurfaceFromWindow(rendererDx12, (MZNT_WindowHandle) {.handle = wndDx12.window.handle}, tempAllocator);
    MZNT_RendererSurface* wndSrfVk   = MZNT_CreateRendererSurfaceFromWindow(rendererVk,   (MZNT_WindowHandle) {.handle =   wndVk.window.handle}, tempAllocator);

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
                DVRPL_WindowData* wnd = (evt.windowId.handle == wndVk.window.handle) ? (&wndVk) : (evt.windowId.handle == wndDx12.window.handle) ? (&wndDx12) : nil;
                if (wnd)
                    DVRPL_SetFullScreen(wnd, fullscreen, nil, nil, nil, nil);
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
                MZNT_RendererSurface* wndSrf = (resizeData.id.handle == wndVk.window.handle) ? wndSrfVk : (resizeData.id.handle == wndDx12.window.handle) ? wndSrfDx12 : nil;
                MZNT_ResizeRendererSurface(wndSrf, resizeData.sizeX, resizeData.sizeY, tempAllocator);
            }

            /*MZNT_RendererCommandBuffer* cmdBuf = */ MZNT_BeginFrame(wndSrfVk, 0.15f, 0.15f, 0.3f, 1.0f, tempAllocator);
            MZNT_EndFrame(wndSrfVk, tempAllocator);

            /*MZNT_RendererCommandBuffer* cmdBuf = */ MZNT_BeginFrame(wndSrfDx12, 0.15f, 0.15f, 0.3f, 1.0f, tempAllocator);
            MZNT_EndFrame(wndSrfDx12, tempAllocator);
        }

        PNSLR_FreeAll(tempAllocator, PNSLR_GET_LOC(), nil);
    }

    MZNT_DestroyRendererSurface(wndSrfVk, tempAllocator);
    MZNT_DestroyRendererSurface(wndSrfDx12, tempAllocator);

    DVRPL_DestroyWindow(&wndVk);
    DVRPL_DestroyWindow(&wndDx12);

    MZNT_DestroyRenderer(rendererVk, tempAllocator);
    MZNT_DestroyRenderer(rendererDx12, tempAllocator);

    return 0;
}

// unity build
#include "Dependencies/Panshilar/Source/zzzz_Unity.c"
#include "Dependencies/Dvaarpaal/Source/zzzz_Unity.c"
#include "Dependencies/Muzent/Source/zzzz_Unity.c"
