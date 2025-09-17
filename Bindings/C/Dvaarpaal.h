#ifndef DVRPL_MAIN_H
#define DVRPL_MAIN_H

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

// #######################################################################################
// Window
// #######################################################################################

/**
 * A cross-platform opaque handle to a window.
 * On Windows, this is an HWND.
 * On OSX, this is an NSWindow*.
 * On Android, this is an ANativeWindow*.
 */
typedef struct DVRPL_Window
{
    u64 handle;
} DVRPL_Window;

/**
 * A cross-platform opaque handle to saved information for a window.
 */
typedef struct PNSLR_ALIGNAS(8) DVRPL_SavedWindowData
{
    u8 buffer[40];
} DVRPL_SavedWindowData;

/**
 * A cross-platform opaque handle for window data.
 * Includes some amount of saved data for the window.
 */
typedef struct DVRPL_WindowData
{
    DVRPL_Window window;
    DVRPL_SavedWindowData savedData;
} DVRPL_WindowData;

/**
 * Options for creating a window.
 */
typedef struct DVRPL_WindowCreationOptions
{
    i16 posX;
    i16 posY;
    u16 sizeX;
    u16 sizeY;
    utf8str title;
    DVRPL_Window parent;
    u8 bgColR;
    u8 bgColG;
    u8 bgColB;
    u8 bgColA;
    b8 msaa;
} DVRPL_WindowCreationOptions;

/**
 * Creates a window with the specified options.
 * Returns a handle to the created window.
 * If creation failed, the returned handle will be zeroed.
 * Not thread-safe.
 */
DVRPL_WindowData DVRPL_CreateWindow(
    DVRPL_WindowCreationOptions options
);

/**
 * Destroys the specified window.
 * Not thread-safe.
 */
void DVRPL_DestroyWindow(
    DVRPL_WindowData* window
);

/**
 * Sets the window's fullscreen status.
 * Returns true on success, false on failure.
 * If entering fullscreen, the previous position and size are stored in the provided pointers.
 * If exiting fullscreen, the window is restored to the provided position and size.
 * If posX, posY, sizeX or sizeY are null, reasonable defaults are used instead.
 * Not thread-safe.
 */
b8 DVRPL_SetFullScreen(
    DVRPL_WindowData* window,
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
b8 DVRPL_GetWindowDimensions(
    DVRPL_WindowData* window,
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
b8 DVRPL_GetPtrPosFromWindow(
    DVRPL_Window window,
    i16* posX,
    i16* posY
);

/**
 * Get the current position of the pointer relative to the screen's top-left corner.
 * Returns true on success, false on failure.
 * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
 * Not thread-safe.
 */
b8 DVRPL_GetPtrPos(
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
i32 DVRPL_Main(
    PNSLR_ArraySlice(utf8str) args
);

#undef PNSLR_ALIGNAS

#ifdef __cplusplus
} // extern c
#endif

#endif//DVRPL_MAIN_H
