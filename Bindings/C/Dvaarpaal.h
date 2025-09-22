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
// Input
// #######################################################################################

/**
 * The type of input event that was logged.
 */
typedef u8 DVRPL_EvtTy /* use as value */;
#define DVRPL_EvtTy_Unknown ((DVRPL_EvtTy) 0)
#define DVRPL_EvtTy_Keyboard ((DVRPL_EvtTy) 1)
#define DVRPL_EvtTy_MouseWheel ((DVRPL_EvtTy) 2)
#define DVRPL_EvtTy_Touch ((DVRPL_EvtTy) 3)
#define DVRPL_EvtTy_TextInput ((DVRPL_EvtTy) 4)
#define DVRPL_EvtTy_DropFile ((DVRPL_EvtTy) 5)
#define DVRPL_EvtTy_Quit ((DVRPL_EvtTy) 6)

/**
 * The information regarding a window move event.
 */
typedef struct DVRPL_WindowMoveData
{
    DVRPL_Window id;
    i16 posX;
    i16 posY;
} DVRPL_WindowMoveData;

PNSLR_DECLARE_ARRAY_SLICE(DVRPL_WindowMoveData);

/**
 * The information regarding a window resize event.
 */
typedef struct DVRPL_WindowResizeData
{
    DVRPL_Window id;
    u16 sizeX;
    u16 sizeY;
} DVRPL_WindowResizeData;

PNSLR_DECLARE_ARRAY_SLICE(DVRPL_WindowResizeData);

/**
 * The status of a touch event.
 */
typedef u8 DVRPL_TouchStatus /* use as value */;
#define DVRPL_TouchStatus_Moved ((DVRPL_TouchStatus) 0)
#define DVRPL_TouchStatus_Pressed ((DVRPL_TouchStatus) 1)
#define DVRPL_TouchStatus_Released ((DVRPL_TouchStatus) 2)

/**
 * The status of a key event.
 */
typedef u8 DVRPL_KeyStatus /* use as value */;
#define DVRPL_KeyStatus_Pressed ((DVRPL_KeyStatus) 0)
#define DVRPL_KeyStatus_Released ((DVRPL_KeyStatus) 1)

/**
 * The possible states of a key event.
 */
typedef u8 DVRPL_KeyState /* use as flags */;
#define DVRPL_KeyState_None ((DVRPL_KeyState) 0)
#define DVRPL_KeyState_Pressed ((DVRPL_KeyState) 1)
#define DVRPL_KeyState_Held ((DVRPL_KeyState) 2)
#define DVRPL_KeyState_Released ((DVRPL_KeyState) 4)

/**
 * Any modifiers that are added to a key event.
 */
typedef u8 DVRPL_KeyModifier /* use as flags */;
#define DVRPL_KeyModifier_None ((DVRPL_KeyModifier) 0)
#define DVRPL_KeyModifier_Alt ((DVRPL_KeyModifier) 1)
#define DVRPL_KeyModifier_Control ((DVRPL_KeyModifier) 2)
#define DVRPL_KeyModifier_Shift ((DVRPL_KeyModifier) 4)
#define DVRPL_KeyModifier_CmdOrMeta ((DVRPL_KeyModifier) 8)

/**
 * The code of a key on the keyboard.
 * Compatible with ASCII for standard keys.
 */
typedef u16 DVRPL_KeyCode /* use as value */;
#define DVRPL_KeyCode_Unknown ((DVRPL_KeyCode) 0)
#define DVRPL_KeyCode_Backspace ((DVRPL_KeyCode) 8)
#define DVRPL_KeyCode_Tab ((DVRPL_KeyCode) 9)
#define DVRPL_KeyCode_Enter ((DVRPL_KeyCode) 13)
#define DVRPL_KeyCode_Escape ((DVRPL_KeyCode) 27)
#define DVRPL_KeyCode_Space ((DVRPL_KeyCode) 32)
#define DVRPL_KeyCode_Delete ((DVRPL_KeyCode) 127)
#define DVRPL_KeyCode_ArrowUp ((DVRPL_KeyCode) 128)
#define DVRPL_KeyCode_ArrowDown ((DVRPL_KeyCode) 129)
#define DVRPL_KeyCode_ArrowLeft ((DVRPL_KeyCode) 130)
#define DVRPL_KeyCode_ArrowRight ((DVRPL_KeyCode) 131)
#define DVRPL_KeyCode_PgUp ((DVRPL_KeyCode) 132)
#define DVRPL_KeyCode_PgDown ((DVRPL_KeyCode) 133)
#define DVRPL_KeyCode_Home ((DVRPL_KeyCode) 134)
#define DVRPL_KeyCode_End ((DVRPL_KeyCode) 135)
#define DVRPL_KeyCode_Insert ((DVRPL_KeyCode) 136)
#define DVRPL_KeyCode_Pause ((DVRPL_KeyCode) 137)
#define DVRPL_KeyCode_ScrollLock ((DVRPL_KeyCode) 138)
#define DVRPL_KeyCode_Alt ((DVRPL_KeyCode) 139)
#define DVRPL_KeyCode_Control ((DVRPL_KeyCode) 140)
#define DVRPL_KeyCode_Shift ((DVRPL_KeyCode) 141)
#define DVRPL_KeyCode_Cmd ((DVRPL_KeyCode) 142)
#define DVRPL_KeyCode_Meta ((DVRPL_KeyCode) 142)
#define DVRPL_KeyCode_F1 ((DVRPL_KeyCode) 143)
#define DVRPL_KeyCode_F2 ((DVRPL_KeyCode) 144)
#define DVRPL_KeyCode_F3 ((DVRPL_KeyCode) 145)
#define DVRPL_KeyCode_F4 ((DVRPL_KeyCode) 146)
#define DVRPL_KeyCode_F5 ((DVRPL_KeyCode) 147)
#define DVRPL_KeyCode_F6 ((DVRPL_KeyCode) 148)
#define DVRPL_KeyCode_F7 ((DVRPL_KeyCode) 149)
#define DVRPL_KeyCode_F8 ((DVRPL_KeyCode) 150)
#define DVRPL_KeyCode_F9 ((DVRPL_KeyCode) 151)
#define DVRPL_KeyCode_F10 ((DVRPL_KeyCode) 152)
#define DVRPL_KeyCode_F11 ((DVRPL_KeyCode) 153)
#define DVRPL_KeyCode_F12 ((DVRPL_KeyCode) 154)
#define DVRPL_KeyCode_PrtScrn ((DVRPL_KeyCode) 167)
#define DVRPL_KeyCode_MouseBtnLeft ((DVRPL_KeyCode) 168)
#define DVRPL_KeyCode_MouseBtnMiddle ((DVRPL_KeyCode) 169)
#define DVRPL_KeyCode_MouseBtnRight ((DVRPL_KeyCode) 170)
#define DVRPL_KeyCode_MouseWhlUp ((DVRPL_KeyCode) 171)
#define DVRPL_KeyCode_MouseWhlDown ((DVRPL_KeyCode) 172)
#define DVRPL_KeyCode_GamePad0Bgn ((DVRPL_KeyCode) 173)
#define DVRPL_KeyCode_GamePad0End ((DVRPL_KeyCode) 205)
#define DVRPL_KeyCode_GamePad1Bgn ((DVRPL_KeyCode) 206)
#define DVRPL_KeyCode_GamePad1End ((DVRPL_KeyCode) 238)
#define DVRPL_KeyCode_GamePad2Bgn ((DVRPL_KeyCode) 239)
#define DVRPL_KeyCode_GamePad2End ((DVRPL_KeyCode) 271)
#define DVRPL_KeyCode_GamePad3Bgn ((DVRPL_KeyCode) 272)
#define DVRPL_KeyCode_GamePad3End ((DVRPL_KeyCode) 304)
#define DVRPL_KeyCode_Touch ((DVRPL_KeyCode) 305)
#define DVRPL_KeyCode_NUM ((DVRPL_KeyCode) 306)

/**
 * An input event that was logged.
 */
typedef struct PNSLR_ALIGNAS(32) DVRPL_Event
{
    DVRPL_EvtTy ty;
    DVRPL_KeyStatus keyStatus;
    DVRPL_KeyModifier keyModifiers;
    b8 repeat;
    DVRPL_KeyCode keyCode;
    u16 textCount;
    u32 utf32Char;
    i32 rawWheelData;
    i32 wheelData;
    DVRPL_TouchStatus touchStatus;
    u8 touchId;
    u16 droppedFileId;
    DVRPL_Window windowId;
} DVRPL_Event;

PNSLR_DECLARE_ARRAY_SLICE(DVRPL_Event);

/**
 * Gather all input events for this frame.
 * Must be called once per frame before accessing events.
 * Clears previous frame's events and processes new Windows messages.
 * Requires a temp allocator to store a bunch of temporary stuff.
 * Not thread-safe.
 */
void DVRPL_GatherEvents(
    PNSLR_Allocator tempAllocator
);

/**
 * Get all events that were gathered this frame.
 * Returns a slice of events that is valid until the next call to DVRPL_GatherEvents.
 * Not thread-safe.
 */
PNSLR_ArraySlice(DVRPL_Event) DVRPL_GetEvents(void);

/**
 * Iterate across window resize events.
 * Automatically cleans up the internal resources when iteration is over.
 * Use in a `while` loop, ideally.
 * Not thread-safe.
 */
b8 DVRPL_IterateResizeEvent(
    i32* iterator,
    DVRPL_WindowResizeData* val
);

/**
 * Iterate across window move events.
 * Automatically cleans up the internal resources when iteration is over.
 * Use in a `while` loop, ideally.
 * Not thread-safe.
 */
b8 DVRPL_IterateMoveEvent(
    i32* iterator,
    DVRPL_WindowMoveData* val
);

/**
 * Get the current state of a key.
 * Returns a bitmask indicating if the key is pressed, held, or released this frame.
 * Not thread-safe.
 */
DVRPL_KeyState DVRPL_GetKeyState(
    DVRPL_KeyCode key
);

/**
 * Get the mouse movement delta for this frame.
 * Sets the provided pointers to the delta values (can pass NULL to ignore).
 * deltaX, deltaY are relative mouse movement, deltaScroll is scroll wheel delta.
 * Not thread-safe.
 */
void DVRPL_GetMouseDelta(
    i32* deltaX,
    i32* deltaY,
    i32* deltaScroll
);

/**
 * Check if the application currently has focus.
 * Returns true if the application has focus, false otherwise.
 * Not thread-safe.
 */
b8 DVRPL_DoesApplicationHaveFocus(void);

/**
 * Get a dropped file path by its ID.
 * The fileId comes from a DropFile event's droppedFileId field.
 * Returns an empty string if the ID is invalid.
 * The returned string is valid until the next call to DVRPL_GatherEvents.
 * Not thread-safe.
 */
utf8str DVRPL_GetDroppedFile(
    u16 fileId
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
