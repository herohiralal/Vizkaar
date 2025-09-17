#ifndef __cplusplus
    #error "Please use the C bindings.";
#endif

#ifndef DVRPL_CXX_MAIN_H
#define DVRPL_CXX_MAIN_H

#include "Intrinsics.hpp"
#include "Panshilar.hpp"

namespace Dvaarpaal
{
    using namespace Intrinsics;
    using namespace Panshilar;

    // #######################################################################################
    // Window
    // #######################################################################################

    /**
     * A cross-platform opaque handle to a window.
     * On Windows, this is an HWND.
     * On OSX, this is an NSWindow*.
     * On Android, this is an ANativeWindow*.
     */
    struct Window
    {
       u64 handle;
    };

    /**
     * A cross-platform opaque handle to saved information for a window.
     */
    struct alignas(8) SavedWindowData
    {
       u8 buffer[40];
    };

    /**
     * A cross-platform opaque handle for window data.
     * Includes some amount of saved data for the window.
     */
    struct WindowData
    {
       Window window;
       SavedWindowData savedData;
    };

    /**
     * Options for creating a window.
     */
    struct WindowCreationOptions
    {
       i16 posX;
       i16 posY;
       u16 sizeX;
       u16 sizeY;
       utf8str title;
       Window parent;
       u8 bgColR;
       u8 bgColG;
       u8 bgColB;
       u8 bgColA;
       b8 msaa;
    };

    /**
     * Creates a window with the specified options.
     * Returns a handle to the created window.
     * If creation failed, the returned handle will be zeroed.
     * Not thread-safe.
     */
    WindowData CreateWindow(
        WindowCreationOptions options
    );

    /**
     * Destroys the specified window.
     * Not thread-safe.
     */
    void DestroyWindow(
        WindowData* window
    );

    /**
     * Sets the window's fullscreen status.
     * Returns true on success, false on failure.
     * If entering fullscreen, the previous position and size are stored in the provided pointers.
     * If exiting fullscreen, the window is restored to the provided position and size.
     * If posX, posY, sizeX or sizeY are null, reasonable defaults are used instead.
     * Not thread-safe.
     */
    b8 SetFullScreen(
        WindowData* window,
        b8 status,
        i16* posX,
        i16* posY,
        u16* sizeX,
        u16* sizeY
    );

    /**
     * Gets the window's current position and size.
     * Returns true on success, false on failure.
     * If any of posX, posY, sizeX or sizeY are null, they are ignored, otherwise
     * the corresponding value is written to the provided pointer.
     * Not thread-safe.
     */
    b8 GetWindowDimensions(
        WindowData* window,
        i16* posX,
        i16* posY,
        u16* sizeX,
        u16* sizeY
    );

    /**
     * Get the current position of the pointer relative to the window's top-left corner.
     * Returns true on success, false on failure.
     * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
     * Not thread-safe.
     */
    b8 GetPtrPosFromWindow(
        Window window,
        i16* posX,
        i16* posY
    );

    /**
     * Get the current position of the pointer relative to the screen's top-left corner.
     * Returns true on success, false on failure.
     * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
     * Not thread-safe.
     */
    b8 GetPtrPos(
        i16* posX,
        i16* posY
    );

    // #######################################################################################
    // EntryPoint
    // #######################################################################################

    /**
     * This is the main entry point of the application.
     * It is not actually implemented inside the Dvaarpaal library,
     * but rather in the application that uses the library.
     * This is done to allow the application to have its own entry point.
     *
     * The code for the main entry point (platform-specific) will be included
     * in the built static libraries, but if compiling from source, add
     * `#define DVRPL_SKIP_ENTRY_PT` when compiling the source.
     */
    i32 Main(
        ArraySlice<utf8str> args
    );

} // namespace end

#endif//DVRPL_CXX_MAIN_H
#ifdef PNSLR_CXX_IMPL

#if (_MSC_VER)
    #define PNSLR_STRUCT_OFFSET(type, member) ((u64)&reinterpret_cast<char const volatile&>((((type*)0)->member)))
#elif (__clang__) || (__GNUC__)
    #define PNSLR_STRUCT_OFFSET(type, member) ((u64) offsetof(type, member))
#else
    #error "UNSUPPORTED COMPILER!";
#endif

struct DVRPL_Window
{
   u64 handle;
};
static_assert(sizeof(DVRPL_Window) == sizeof(Dvaarpaal::Window), "size mismatch");
static_assert(alignof(DVRPL_Window) == alignof(Dvaarpaal::Window), "align mismatch");
DVRPL_Window* PNSLR_Bindings_Convert(Dvaarpaal::Window* x) { return reinterpret_cast<DVRPL_Window*>(x); }
Dvaarpaal::Window* PNSLR_Bindings_Convert(DVRPL_Window* x) { return reinterpret_cast<Dvaarpaal::Window*>(x); }
DVRPL_Window& PNSLR_Bindings_Convert(Dvaarpaal::Window& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::Window& PNSLR_Bindings_Convert(DVRPL_Window& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Window, handle) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Window, handle), "handle offset mismatch");

struct alignas(8) DVRPL_SavedWindowData
{
   u8 buffer[40];
};
static_assert(sizeof(DVRPL_SavedWindowData) == sizeof(Dvaarpaal::SavedWindowData), "size mismatch");
static_assert(alignof(DVRPL_SavedWindowData) == alignof(Dvaarpaal::SavedWindowData), "align mismatch");
DVRPL_SavedWindowData* PNSLR_Bindings_Convert(Dvaarpaal::SavedWindowData* x) { return reinterpret_cast<DVRPL_SavedWindowData*>(x); }
Dvaarpaal::SavedWindowData* PNSLR_Bindings_Convert(DVRPL_SavedWindowData* x) { return reinterpret_cast<Dvaarpaal::SavedWindowData*>(x); }
DVRPL_SavedWindowData& PNSLR_Bindings_Convert(Dvaarpaal::SavedWindowData& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::SavedWindowData& PNSLR_Bindings_Convert(DVRPL_SavedWindowData& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_SavedWindowData, buffer) == PNSLR_STRUCT_OFFSET(Dvaarpaal::SavedWindowData, buffer), "buffer offset mismatch");

struct DVRPL_WindowData
{
   DVRPL_Window window;
   DVRPL_SavedWindowData savedData;
};
static_assert(sizeof(DVRPL_WindowData) == sizeof(Dvaarpaal::WindowData), "size mismatch");
static_assert(alignof(DVRPL_WindowData) == alignof(Dvaarpaal::WindowData), "align mismatch");
DVRPL_WindowData* PNSLR_Bindings_Convert(Dvaarpaal::WindowData* x) { return reinterpret_cast<DVRPL_WindowData*>(x); }
Dvaarpaal::WindowData* PNSLR_Bindings_Convert(DVRPL_WindowData* x) { return reinterpret_cast<Dvaarpaal::WindowData*>(x); }
DVRPL_WindowData& PNSLR_Bindings_Convert(Dvaarpaal::WindowData& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::WindowData& PNSLR_Bindings_Convert(DVRPL_WindowData& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowData, window) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowData, window), "window offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowData, savedData) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowData, savedData), "savedData offset mismatch");

struct DVRPL_WindowCreationOptions
{
   i16 posX;
   i16 posY;
   u16 sizeX;
   u16 sizeY;
   PNSLR_UTF8STR title;
   DVRPL_Window parent;
   u8 bgColR;
   u8 bgColG;
   u8 bgColB;
   u8 bgColA;
   b8 msaa;
};
static_assert(sizeof(DVRPL_WindowCreationOptions) == sizeof(Dvaarpaal::WindowCreationOptions), "size mismatch");
static_assert(alignof(DVRPL_WindowCreationOptions) == alignof(Dvaarpaal::WindowCreationOptions), "align mismatch");
DVRPL_WindowCreationOptions* PNSLR_Bindings_Convert(Dvaarpaal::WindowCreationOptions* x) { return reinterpret_cast<DVRPL_WindowCreationOptions*>(x); }
Dvaarpaal::WindowCreationOptions* PNSLR_Bindings_Convert(DVRPL_WindowCreationOptions* x) { return reinterpret_cast<Dvaarpaal::WindowCreationOptions*>(x); }
DVRPL_WindowCreationOptions& PNSLR_Bindings_Convert(Dvaarpaal::WindowCreationOptions& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::WindowCreationOptions& PNSLR_Bindings_Convert(DVRPL_WindowCreationOptions& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, posX) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, posX), "posX offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, posY) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, posY), "posY offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, sizeX) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, sizeX), "sizeX offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, sizeY) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, sizeY), "sizeY offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, title) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, title), "title offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, parent) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, parent), "parent offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, bgColR) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, bgColR), "bgColR offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, bgColG) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, bgColG), "bgColG offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, bgColB) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, bgColB), "bgColB offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, bgColA) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, bgColA), "bgColA offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowCreationOptions, msaa) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowCreationOptions, msaa), "msaa offset mismatch");

extern "C" DVRPL_WindowData DVRPL_CreateWindow(DVRPL_WindowCreationOptions options);
Dvaarpaal::WindowData Dvaarpaal::CreateWindow(Dvaarpaal::WindowCreationOptions options)
{
    DVRPL_WindowData zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_CreateWindow(PNSLR_Bindings_Convert(options)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" void DVRPL_DestroyWindow(DVRPL_WindowData* window);
void Dvaarpaal::DestroyWindow(Dvaarpaal::WindowData* window)
{
    DVRPL_DestroyWindow(PNSLR_Bindings_Convert(window));
}

extern "C" b8 DVRPL_SetFullScreen(DVRPL_WindowData* window, b8 status, i16* posX, i16* posY, u16* sizeX, u16* sizeY);
b8 Dvaarpaal::SetFullScreen(Dvaarpaal::WindowData* window, b8 status, i16* posX, i16* posY, u16* sizeX, u16* sizeY)
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_SetFullScreen(PNSLR_Bindings_Convert(window), PNSLR_Bindings_Convert(status), PNSLR_Bindings_Convert(posX), PNSLR_Bindings_Convert(posY), PNSLR_Bindings_Convert(sizeX), PNSLR_Bindings_Convert(sizeY)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" b8 DVRPL_GetWindowDimensions(DVRPL_WindowData* window, i16* posX, i16* posY, u16* sizeX, u16* sizeY);
b8 Dvaarpaal::GetWindowDimensions(Dvaarpaal::WindowData* window, i16* posX, i16* posY, u16* sizeX, u16* sizeY)
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_GetWindowDimensions(PNSLR_Bindings_Convert(window), PNSLR_Bindings_Convert(posX), PNSLR_Bindings_Convert(posY), PNSLR_Bindings_Convert(sizeX), PNSLR_Bindings_Convert(sizeY)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" b8 DVRPL_GetPtrPosFromWindow(DVRPL_Window window, i16* posX, i16* posY);
b8 Dvaarpaal::GetPtrPosFromWindow(Dvaarpaal::Window window, i16* posX, i16* posY)
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_GetPtrPosFromWindow(PNSLR_Bindings_Convert(window), PNSLR_Bindings_Convert(posX), PNSLR_Bindings_Convert(posY)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" b8 DVRPL_GetPtrPos(i16* posX, i16* posY);
b8 Dvaarpaal::GetPtrPos(i16* posX, i16* posY)
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_GetPtrPos(PNSLR_Bindings_Convert(posX), PNSLR_Bindings_Convert(posY)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" i32 DVRPL_Main(PNSLR_ArraySlice_PNSLR_UTF8STR args);
i32 Dvaarpaal::Main(ArraySlice<utf8str> args)
{
    i32 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_Main(PNSLR_Bindings_Convert(args)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

#undef PNSLR_STRUCT_OFFSET

#endif//PNSLR_CXX_IMPL

