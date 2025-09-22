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
        i16* posX = { },
        i16* posY = { },
        u16* sizeX = { },
        u16* sizeY = { }
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
    // Input
    // #######################################################################################

    /**
     * The type of input event that was logged.
     */
    enum class EvtTy : u8 /* use as value */
    {
        Unknown = 0,
        Keyboard = 1,
        MouseWheel = 2,
        Touch = 3,
        TextInput = 4,
        DropFile = 5,
        Quit = 6,
    };

    /**
     * The information regarding a window move event.
     */
    struct WindowMoveData
    {
       Window id;
       i16 posX;
       i16 posY;
    };

    /**
     * The information regarding a window resize event.
     */
    struct WindowResizeData
    {
       Window id;
       u16 sizeX;
       u16 sizeY;
    };

    /**
     * The status of a touch event.
     */
    enum class TouchStatus : u8 /* use as value */
    {
        Moved = 0,
        Pressed = 1,
        Released = 2,
    };

    /**
     * The status of a key event.
     */
    enum class KeyStatus : u8 /* use as value */
    {
        Pressed = 0,
        Released = 1,
    };

    /**
     * The possible states of a key event.
     */
    enum class KeyState : u8 /* use as flags */
    {
        None = 0,
        Pressed = 1,
        Held = 2,
        Released = 4,
    };

    /**
     * Any modifiers that are added to a key event.
     */
    enum class KeyModifier : u8 /* use as flags */
    {
        None = 0,
        Alt = 1,
        Control = 2,
        Shift = 4,
        CmdOrMeta = 8,
    };

    /**
     * The code of a key on the keyboard.
     * Compatible with ASCII for standard keys.
     */
    enum class KeyCode : u16 /* use as value */
    {
        Unknown = 0,
        Backspace = 8,
        Tab = 9,
        Enter = 13,
        Escape = 27,
        Space = 32,
        Delete = 127,
        ArrowUp = 128,
        ArrowDown = 129,
        ArrowLeft = 130,
        ArrowRight = 131,
        PgUp = 132,
        PgDown = 133,
        Home = 134,
        End = 135,
        Insert = 136,
        Pause = 137,
        ScrollLock = 138,
        Alt = 139,
        Control = 140,
        Shift = 141,
        Cmd = 142,
        Meta = 142,
        F1 = 143,
        F2 = 144,
        F3 = 145,
        F4 = 146,
        F5 = 147,
        F6 = 148,
        F7 = 149,
        F8 = 150,
        F9 = 151,
        F10 = 152,
        F11 = 153,
        F12 = 154,
        PrtScrn = 167,
        MouseBtnLeft = 168,
        MouseBtnMiddle = 169,
        MouseBtnRight = 170,
        MouseWhlUp = 171,
        MouseWhlDown = 172,
        GamePad0Bgn = 173,
        GamePad0End = 205,
        GamePad1Bgn = 206,
        GamePad1End = 238,
        GamePad2Bgn = 239,
        GamePad2End = 271,
        GamePad3Bgn = 272,
        GamePad3End = 304,
        Touch = 305,
        NUM = 306,
    };

    /**
     * An input event that was logged.
     */
    struct alignas(32) Event
    {
       EvtTy ty;
       KeyStatus keyStatus;
       KeyModifier keyModifiers;
       b8 repeat;
       KeyCode keyCode;
       u16 textCount;
       u32 utf32Char;
       i32 rawWheelData;
       i32 wheelData;
       TouchStatus touchStatus;
       u8 touchId;
       u16 droppedFileId;
       Window windowId;
    };

    /**
     * Gather all input events for this frame.
     * Must be called once per frame before accessing events.
     * Clears previous frame's events and processes new Windows messages.
     * Requires a temp allocator to store a bunch of temporary stuff.
     * Not thread-safe.
     */
    void GatherEvents(
        Allocator tempAllocator
    );

    /**
     * Get all events that were gathered this frame.
     * Returns a slice of events that is valid until the next call to DVRPL_GatherEvents.
     * Not thread-safe.
     */
    ArraySlice<Event> GetEvents();

    /**
     * Iterate across window resize events.
     * Automatically cleans up the internal resources when iteration is over.
     * Use in a `while` loop, ideally.
     * Not thread-safe.
     */
    b8 IterateResizeEvent(
        i32* iterator,
        WindowResizeData* val = { }
    );

    /**
     * Iterate across window move events.
     * Automatically cleans up the internal resources when iteration is over.
     * Use in a `while` loop, ideally.
     * Not thread-safe.
     */
    b8 IterateMoveEvent(
        i32* iterator,
        WindowMoveData* val = { }
    );

    /**
     * Get the current state of a key.
     * Returns a bitmask indicating if the key is pressed, held, or released this frame.
     * Not thread-safe.
     */
    KeyState GetKeyState(
        KeyCode key
    );

    /**
     * Get the mouse movement delta for this frame.
     * Sets the provided pointers to the delta values (can pass NULL to ignore).
     * deltaX, deltaY are relative mouse movement, deltaScroll is scroll wheel delta.
     * Not thread-safe.
     */
    void GetMouseDelta(
        i32* deltaX = { },
        i32* deltaY = { },
        i32* deltaScroll = { }
    );

    /**
     * Check if the application currently has focus.
     * Returns true if the application has focus, false otherwise.
     * Not thread-safe.
     */
    b8 DoesApplicationHaveFocus();

    /**
     * Get a dropped file path by its ID.
     * The fileId comes from a DropFile event's droppedFileId field.
     * Returns an empty string if the ID is invalid.
     * The returned string is valid until the next call to DVRPL_GatherEvents.
     * Not thread-safe.
     */
    utf8str GetDroppedFile(
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

enum class DVRPL_EvtTy : u8 { };
static_assert(sizeof(DVRPL_EvtTy) == sizeof(Dvaarpaal::EvtTy), "size mismatch");
static_assert(alignof(DVRPL_EvtTy) == alignof(Dvaarpaal::EvtTy), "align mismatch");
DVRPL_EvtTy* PNSLR_Bindings_Convert(Dvaarpaal::EvtTy* x) { return reinterpret_cast<DVRPL_EvtTy*>(x); }
Dvaarpaal::EvtTy* PNSLR_Bindings_Convert(DVRPL_EvtTy* x) { return reinterpret_cast<Dvaarpaal::EvtTy*>(x); }
DVRPL_EvtTy& PNSLR_Bindings_Convert(Dvaarpaal::EvtTy& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::EvtTy& PNSLR_Bindings_Convert(DVRPL_EvtTy& x) { return *PNSLR_Bindings_Convert(&x); }

struct DVRPL_WindowMoveData
{
   DVRPL_Window id;
   i16 posX;
   i16 posY;
};
static_assert(sizeof(DVRPL_WindowMoveData) == sizeof(Dvaarpaal::WindowMoveData), "size mismatch");
static_assert(alignof(DVRPL_WindowMoveData) == alignof(Dvaarpaal::WindowMoveData), "align mismatch");
DVRPL_WindowMoveData* PNSLR_Bindings_Convert(Dvaarpaal::WindowMoveData* x) { return reinterpret_cast<DVRPL_WindowMoveData*>(x); }
Dvaarpaal::WindowMoveData* PNSLR_Bindings_Convert(DVRPL_WindowMoveData* x) { return reinterpret_cast<Dvaarpaal::WindowMoveData*>(x); }
DVRPL_WindowMoveData& PNSLR_Bindings_Convert(Dvaarpaal::WindowMoveData& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::WindowMoveData& PNSLR_Bindings_Convert(DVRPL_WindowMoveData& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowMoveData, id) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowMoveData, id), "id offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowMoveData, posX) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowMoveData, posX), "posX offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowMoveData, posY) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowMoveData, posY), "posY offset mismatch");

typedef struct { DVRPL_WindowMoveData* data; i64 count; } PNSLR_ArraySlice_DVRPL_WindowMoveData;
static_assert(sizeof(PNSLR_ArraySlice_DVRPL_WindowMoveData) == sizeof(ArraySlice<Dvaarpaal::WindowMoveData>), "size mismatch");
static_assert(alignof(PNSLR_ArraySlice_DVRPL_WindowMoveData) == alignof(ArraySlice<Dvaarpaal::WindowMoveData>), "align mismatch");
PNSLR_ArraySlice_DVRPL_WindowMoveData* PNSLR_Bindings_Convert(ArraySlice<Dvaarpaal::WindowMoveData>* x) { return reinterpret_cast<PNSLR_ArraySlice_DVRPL_WindowMoveData*>(x); }
ArraySlice<Dvaarpaal::WindowMoveData>* PNSLR_Bindings_Convert(PNSLR_ArraySlice_DVRPL_WindowMoveData* x) { return reinterpret_cast<ArraySlice<Dvaarpaal::WindowMoveData>*>(x); }
PNSLR_ArraySlice_DVRPL_WindowMoveData& PNSLR_Bindings_Convert(ArraySlice<Dvaarpaal::WindowMoveData>& x) { return *PNSLR_Bindings_Convert(&x); }
ArraySlice<Dvaarpaal::WindowMoveData>& PNSLR_Bindings_Convert(PNSLR_ArraySlice_DVRPL_WindowMoveData& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(PNSLR_ArraySlice_DVRPL_WindowMoveData, count) == PNSLR_STRUCT_OFFSET(ArraySlice<Dvaarpaal::WindowMoveData>, count), "count offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(PNSLR_ArraySlice_DVRPL_WindowMoveData, data) == PNSLR_STRUCT_OFFSET(ArraySlice<Dvaarpaal::WindowMoveData>, data), "data offset mismatch");

struct DVRPL_WindowResizeData
{
   DVRPL_Window id;
   u16 sizeX;
   u16 sizeY;
};
static_assert(sizeof(DVRPL_WindowResizeData) == sizeof(Dvaarpaal::WindowResizeData), "size mismatch");
static_assert(alignof(DVRPL_WindowResizeData) == alignof(Dvaarpaal::WindowResizeData), "align mismatch");
DVRPL_WindowResizeData* PNSLR_Bindings_Convert(Dvaarpaal::WindowResizeData* x) { return reinterpret_cast<DVRPL_WindowResizeData*>(x); }
Dvaarpaal::WindowResizeData* PNSLR_Bindings_Convert(DVRPL_WindowResizeData* x) { return reinterpret_cast<Dvaarpaal::WindowResizeData*>(x); }
DVRPL_WindowResizeData& PNSLR_Bindings_Convert(Dvaarpaal::WindowResizeData& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::WindowResizeData& PNSLR_Bindings_Convert(DVRPL_WindowResizeData& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowResizeData, id) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowResizeData, id), "id offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowResizeData, sizeX) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowResizeData, sizeX), "sizeX offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_WindowResizeData, sizeY) == PNSLR_STRUCT_OFFSET(Dvaarpaal::WindowResizeData, sizeY), "sizeY offset mismatch");

typedef struct { DVRPL_WindowResizeData* data; i64 count; } PNSLR_ArraySlice_DVRPL_WindowResizeData;
static_assert(sizeof(PNSLR_ArraySlice_DVRPL_WindowResizeData) == sizeof(ArraySlice<Dvaarpaal::WindowResizeData>), "size mismatch");
static_assert(alignof(PNSLR_ArraySlice_DVRPL_WindowResizeData) == alignof(ArraySlice<Dvaarpaal::WindowResizeData>), "align mismatch");
PNSLR_ArraySlice_DVRPL_WindowResizeData* PNSLR_Bindings_Convert(ArraySlice<Dvaarpaal::WindowResizeData>* x) { return reinterpret_cast<PNSLR_ArraySlice_DVRPL_WindowResizeData*>(x); }
ArraySlice<Dvaarpaal::WindowResizeData>* PNSLR_Bindings_Convert(PNSLR_ArraySlice_DVRPL_WindowResizeData* x) { return reinterpret_cast<ArraySlice<Dvaarpaal::WindowResizeData>*>(x); }
PNSLR_ArraySlice_DVRPL_WindowResizeData& PNSLR_Bindings_Convert(ArraySlice<Dvaarpaal::WindowResizeData>& x) { return *PNSLR_Bindings_Convert(&x); }
ArraySlice<Dvaarpaal::WindowResizeData>& PNSLR_Bindings_Convert(PNSLR_ArraySlice_DVRPL_WindowResizeData& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(PNSLR_ArraySlice_DVRPL_WindowResizeData, count) == PNSLR_STRUCT_OFFSET(ArraySlice<Dvaarpaal::WindowResizeData>, count), "count offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(PNSLR_ArraySlice_DVRPL_WindowResizeData, data) == PNSLR_STRUCT_OFFSET(ArraySlice<Dvaarpaal::WindowResizeData>, data), "data offset mismatch");

enum class DVRPL_TouchStatus : u8 { };
static_assert(sizeof(DVRPL_TouchStatus) == sizeof(Dvaarpaal::TouchStatus), "size mismatch");
static_assert(alignof(DVRPL_TouchStatus) == alignof(Dvaarpaal::TouchStatus), "align mismatch");
DVRPL_TouchStatus* PNSLR_Bindings_Convert(Dvaarpaal::TouchStatus* x) { return reinterpret_cast<DVRPL_TouchStatus*>(x); }
Dvaarpaal::TouchStatus* PNSLR_Bindings_Convert(DVRPL_TouchStatus* x) { return reinterpret_cast<Dvaarpaal::TouchStatus*>(x); }
DVRPL_TouchStatus& PNSLR_Bindings_Convert(Dvaarpaal::TouchStatus& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::TouchStatus& PNSLR_Bindings_Convert(DVRPL_TouchStatus& x) { return *PNSLR_Bindings_Convert(&x); }

enum class DVRPL_KeyStatus : u8 { };
static_assert(sizeof(DVRPL_KeyStatus) == sizeof(Dvaarpaal::KeyStatus), "size mismatch");
static_assert(alignof(DVRPL_KeyStatus) == alignof(Dvaarpaal::KeyStatus), "align mismatch");
DVRPL_KeyStatus* PNSLR_Bindings_Convert(Dvaarpaal::KeyStatus* x) { return reinterpret_cast<DVRPL_KeyStatus*>(x); }
Dvaarpaal::KeyStatus* PNSLR_Bindings_Convert(DVRPL_KeyStatus* x) { return reinterpret_cast<Dvaarpaal::KeyStatus*>(x); }
DVRPL_KeyStatus& PNSLR_Bindings_Convert(Dvaarpaal::KeyStatus& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::KeyStatus& PNSLR_Bindings_Convert(DVRPL_KeyStatus& x) { return *PNSLR_Bindings_Convert(&x); }

enum class DVRPL_KeyState : u8 { };
static_assert(sizeof(DVRPL_KeyState) == sizeof(Dvaarpaal::KeyState), "size mismatch");
static_assert(alignof(DVRPL_KeyState) == alignof(Dvaarpaal::KeyState), "align mismatch");
DVRPL_KeyState* PNSLR_Bindings_Convert(Dvaarpaal::KeyState* x) { return reinterpret_cast<DVRPL_KeyState*>(x); }
Dvaarpaal::KeyState* PNSLR_Bindings_Convert(DVRPL_KeyState* x) { return reinterpret_cast<Dvaarpaal::KeyState*>(x); }
DVRPL_KeyState& PNSLR_Bindings_Convert(Dvaarpaal::KeyState& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::KeyState& PNSLR_Bindings_Convert(DVRPL_KeyState& x) { return *PNSLR_Bindings_Convert(&x); }

enum class DVRPL_KeyModifier : u8 { };
static_assert(sizeof(DVRPL_KeyModifier) == sizeof(Dvaarpaal::KeyModifier), "size mismatch");
static_assert(alignof(DVRPL_KeyModifier) == alignof(Dvaarpaal::KeyModifier), "align mismatch");
DVRPL_KeyModifier* PNSLR_Bindings_Convert(Dvaarpaal::KeyModifier* x) { return reinterpret_cast<DVRPL_KeyModifier*>(x); }
Dvaarpaal::KeyModifier* PNSLR_Bindings_Convert(DVRPL_KeyModifier* x) { return reinterpret_cast<Dvaarpaal::KeyModifier*>(x); }
DVRPL_KeyModifier& PNSLR_Bindings_Convert(Dvaarpaal::KeyModifier& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::KeyModifier& PNSLR_Bindings_Convert(DVRPL_KeyModifier& x) { return *PNSLR_Bindings_Convert(&x); }

enum class DVRPL_KeyCode : u16 { };
static_assert(sizeof(DVRPL_KeyCode) == sizeof(Dvaarpaal::KeyCode), "size mismatch");
static_assert(alignof(DVRPL_KeyCode) == alignof(Dvaarpaal::KeyCode), "align mismatch");
DVRPL_KeyCode* PNSLR_Bindings_Convert(Dvaarpaal::KeyCode* x) { return reinterpret_cast<DVRPL_KeyCode*>(x); }
Dvaarpaal::KeyCode* PNSLR_Bindings_Convert(DVRPL_KeyCode* x) { return reinterpret_cast<Dvaarpaal::KeyCode*>(x); }
DVRPL_KeyCode& PNSLR_Bindings_Convert(Dvaarpaal::KeyCode& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::KeyCode& PNSLR_Bindings_Convert(DVRPL_KeyCode& x) { return *PNSLR_Bindings_Convert(&x); }

struct alignas(32) DVRPL_Event
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
};
static_assert(sizeof(DVRPL_Event) == sizeof(Dvaarpaal::Event), "size mismatch");
static_assert(alignof(DVRPL_Event) == alignof(Dvaarpaal::Event), "align mismatch");
DVRPL_Event* PNSLR_Bindings_Convert(Dvaarpaal::Event* x) { return reinterpret_cast<DVRPL_Event*>(x); }
Dvaarpaal::Event* PNSLR_Bindings_Convert(DVRPL_Event* x) { return reinterpret_cast<Dvaarpaal::Event*>(x); }
DVRPL_Event& PNSLR_Bindings_Convert(Dvaarpaal::Event& x) { return *PNSLR_Bindings_Convert(&x); }
Dvaarpaal::Event& PNSLR_Bindings_Convert(DVRPL_Event& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, ty) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, ty), "ty offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, keyStatus) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, keyStatus), "keyStatus offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, keyModifiers) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, keyModifiers), "keyModifiers offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, repeat) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, repeat), "repeat offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, keyCode) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, keyCode), "keyCode offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, textCount) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, textCount), "textCount offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, utf32Char) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, utf32Char), "utf32Char offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, rawWheelData) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, rawWheelData), "rawWheelData offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, wheelData) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, wheelData), "wheelData offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, touchStatus) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, touchStatus), "touchStatus offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, touchId) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, touchId), "touchId offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, droppedFileId) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, droppedFileId), "droppedFileId offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(DVRPL_Event, windowId) == PNSLR_STRUCT_OFFSET(Dvaarpaal::Event, windowId), "windowId offset mismatch");

typedef struct { DVRPL_Event* data; i64 count; } PNSLR_ArraySlice_DVRPL_Event;
static_assert(sizeof(PNSLR_ArraySlice_DVRPL_Event) == sizeof(ArraySlice<Dvaarpaal::Event>), "size mismatch");
static_assert(alignof(PNSLR_ArraySlice_DVRPL_Event) == alignof(ArraySlice<Dvaarpaal::Event>), "align mismatch");
PNSLR_ArraySlice_DVRPL_Event* PNSLR_Bindings_Convert(ArraySlice<Dvaarpaal::Event>* x) { return reinterpret_cast<PNSLR_ArraySlice_DVRPL_Event*>(x); }
ArraySlice<Dvaarpaal::Event>* PNSLR_Bindings_Convert(PNSLR_ArraySlice_DVRPL_Event* x) { return reinterpret_cast<ArraySlice<Dvaarpaal::Event>*>(x); }
PNSLR_ArraySlice_DVRPL_Event& PNSLR_Bindings_Convert(ArraySlice<Dvaarpaal::Event>& x) { return *PNSLR_Bindings_Convert(&x); }
ArraySlice<Dvaarpaal::Event>& PNSLR_Bindings_Convert(PNSLR_ArraySlice_DVRPL_Event& x) { return *PNSLR_Bindings_Convert(&x); }
static_assert(PNSLR_STRUCT_OFFSET(PNSLR_ArraySlice_DVRPL_Event, count) == PNSLR_STRUCT_OFFSET(ArraySlice<Dvaarpaal::Event>, count), "count offset mismatch");
static_assert(PNSLR_STRUCT_OFFSET(PNSLR_ArraySlice_DVRPL_Event, data) == PNSLR_STRUCT_OFFSET(ArraySlice<Dvaarpaal::Event>, data), "data offset mismatch");

extern "C" void DVRPL_GatherEvents(PNSLR_Allocator tempAllocator);
void Dvaarpaal::GatherEvents(Panshilar::Allocator tempAllocator)
{
    DVRPL_GatherEvents(PNSLR_Bindings_Convert(tempAllocator));
}

extern "C" PNSLR_ArraySlice_DVRPL_Event DVRPL_GetEvents();
ArraySlice<Dvaarpaal::Event> Dvaarpaal::GetEvents()
{
    PNSLR_ArraySlice_DVRPL_Event zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_GetEvents(); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" b8 DVRPL_IterateResizeEvent(i32* iterator, DVRPL_WindowResizeData* val);
b8 Dvaarpaal::IterateResizeEvent(i32* iterator, Dvaarpaal::WindowResizeData* val)
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_IterateResizeEvent(PNSLR_Bindings_Convert(iterator), PNSLR_Bindings_Convert(val)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" b8 DVRPL_IterateMoveEvent(i32* iterator, DVRPL_WindowMoveData* val);
b8 Dvaarpaal::IterateMoveEvent(i32* iterator, Dvaarpaal::WindowMoveData* val)
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_IterateMoveEvent(PNSLR_Bindings_Convert(iterator), PNSLR_Bindings_Convert(val)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" DVRPL_KeyState DVRPL_GetKeyState(DVRPL_KeyCode key);
Dvaarpaal::KeyState Dvaarpaal::GetKeyState(Dvaarpaal::KeyCode key)
{
    DVRPL_KeyState zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_GetKeyState(PNSLR_Bindings_Convert(key)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" void DVRPL_GetMouseDelta(i32* deltaX, i32* deltaY, i32* deltaScroll);
void Dvaarpaal::GetMouseDelta(i32* deltaX, i32* deltaY, i32* deltaScroll)
{
    DVRPL_GetMouseDelta(PNSLR_Bindings_Convert(deltaX), PNSLR_Bindings_Convert(deltaY), PNSLR_Bindings_Convert(deltaScroll));
}

extern "C" b8 DVRPL_DoesApplicationHaveFocus();
b8 Dvaarpaal::DoesApplicationHaveFocus()
{
    b8 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_DoesApplicationHaveFocus(); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" PNSLR_UTF8STR DVRPL_GetDroppedFile(u16 fileId);
utf8str Dvaarpaal::GetDroppedFile(u16 fileId)
{
    PNSLR_UTF8STR zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_GetDroppedFile(PNSLR_Bindings_Convert(fileId)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

extern "C" i32 DVRPL_Main(PNSLR_ArraySlice_PNSLR_UTF8STR args);
i32 Dvaarpaal::Main(ArraySlice<utf8str> args)
{
    i32 zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW = DVRPL_Main(PNSLR_Bindings_Convert(args)); return PNSLR_Bindings_Convert(zzzz_RetValXYZABCDEFGHIJKLMNOPQRSTUVW);
}

#undef PNSLR_STRUCT_OFFSET

#endif//PNSLR_CXX_IMPL

