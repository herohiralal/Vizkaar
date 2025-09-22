package Dvaarpaal

import "../Intrinsics"
import "../Panshilar"

// #######################################################################################
// Window
// #######################################################################################

/*
A cross-platform opaque handle to a window.
On Windows, this is an HWND.
On OSX, this is an NSWindow*.
On Android, this is an ANativeWindow*.
*/
Window :: struct  {
	handle: u64,
}

/*
A cross-platform opaque handle to saved information for a window.
*/
SavedWindowData :: struct #align(8)  {
	buffer: [40]u8,
}

/*
A cross-platform opaque handle for window data.
Includes some amount of saved data for the window.
*/
WindowData :: struct  {
	window: Window,
	savedData: SavedWindowData,
}

/*
Options for creating a window.
*/
WindowCreationOptions :: struct  {
	posX: i16,
	posY: i16,
	sizeX: u16,
	sizeY: u16,
	title: string,
	parent: Window,
	bgColR: u8,
	bgColG: u8,
	bgColB: u8,
	bgColA: u8,
	msaa: b8,
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Creates a window with the specified options.
	Returns a handle to the created window.
	If creation failed, the returned handle will be zeroed.
	Not thread-safe.
	*/
	CreateWindow :: proc "c" (
		options: WindowCreationOptions,
	) -> WindowData ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Destroys the specified window.
	Not thread-safe.
	*/
	DestroyWindow :: proc "c" (
		window: ^WindowData,
	) ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Sets the window's fullscreen status.
	Returns true on success, false on failure.
	If entering fullscreen, the previous position and size are stored in the provided pointers.
	If exiting fullscreen, the window is restored to the provided position and size.
	If posX, posY, sizeX or sizeY are null, reasonable defaults are used instead.
	Not thread-safe.
	*/
	SetFullScreen :: proc "c" (
		window: ^WindowData,
		status: b8,
		posX: ^i16 = { },
		posY: ^i16 = { },
		sizeX: ^u16 = { },
		sizeY: ^u16 = { },
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Gets the window's current position and size.
	Returns true on success, false on failure.
	If any of posX, posY, sizeX or sizeY are null, they are ignored, otherwise
	the corresponding value is written to the provided pointer.
	Not thread-safe.
	*/
	GetWindowDimensions :: proc "c" (
		window: ^WindowData,
		posX: ^i16,
		posY: ^i16,
		sizeX: ^u16,
		sizeY: ^u16,
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Get the current position of the pointer relative to the window's top-left corner.
	Returns true on success, false on failure.
	If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
	Not thread-safe.
	*/
	GetPtrPosFromWindow :: proc "c" (
		window: Window,
		posX: ^i16,
		posY: ^i16,
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Get the current position of the pointer relative to the screen's top-left corner.
	Returns true on success, false on failure.
	If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
	Not thread-safe.
	*/
	GetPtrPos :: proc "c" (
		posX: ^i16,
		posY: ^i16,
	) -> b8 ---
}

// #######################################################################################
// Input
// #######################################################################################

/*
The type of input event that was logged.
*/
EvtTy :: enum u8 {
	Unknown = 0,
	Keyboard = 1,
	MouseWheel = 2,
	Touch = 3,
	TextInput = 4,
	DropFile = 5,
	Quit = 6,
}

/*
The information regarding a window move event.
*/
WindowMoveData :: struct  {
	id: Window,
	posX: i16,
	posY: i16,
}

// declare []WindowMoveData

/*
The information regarding a window resize event.
*/
WindowResizeData :: struct  {
	id: Window,
	sizeX: u16,
	sizeY: u16,
}

// declare []WindowResizeData

/*
The status of a touch event.
*/
TouchStatus :: enum u8 {
	Moved = 0,
	Pressed = 1,
	Released = 2,
}

/*
The status of a key event.
*/
KeyStatus :: enum u8 {
	Pressed = 0,
	Released = 1,
}

/*
The possible states of a key event.
*/
KeyState :: distinct bit_set[KeyStateValues; u8]

KeyStateValues :: enum u8 {
	Pressed = 0,
	Held = 1,
	Released = 2,
}

/*
Any modifiers that are added to a key event.
*/
KeyModifier :: distinct bit_set[KeyModifierValues; u8]

KeyModifierValues :: enum u8 {
	Alt = 0,
	Control = 1,
	Shift = 2,
	CmdOrMeta = 3,
}

/*
The code of a key on the keyboard.
Compatible with ASCII for standard keys.
*/
KeyCode :: enum u16 {
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
}

/*
An input event that was logged.
*/
Event :: struct #align(32)  {
	ty: EvtTy,
	keyStatus: KeyStatus,
	keyModifiers: KeyModifier,
	repeat: b8,
	keyCode: KeyCode,
	textCount: u16,
	utf32Char: u32,
	rawWheelData: i32,
	wheelData: i32,
	touchStatus: TouchStatus,
	touchId: u8,
	droppedFileId: u16,
	windowId: Window,
}

// declare []Event

@(link_prefix="PNSLR_")
foreign {
	/*
	Gather all input events for this frame.
	Must be called once per frame before accessing events.
	Clears previous frame's events and processes new Windows messages.
	Requires a temp allocator to store a bunch of temporary stuff.
	Not thread-safe.
	*/
	GatherEvents :: proc "c" (
		tempAllocator: Panshilar.Allocator,
	) ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Get all events that were gathered this frame.
	Returns a slice of events that is valid until the next call to DVRPL_GatherEvents.
	Not thread-safe.
	*/
	GetEvents :: proc "c" () -> []Event ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Iterate across window resize events.
	Automatically cleans up the internal resources when iteration is over.
	Use in a `while` loop, ideally.
	Not thread-safe.
	*/
	IterateResizeEvent :: proc "c" (
		iterator: ^i32,
		val: ^WindowResizeData = { },
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Iterate across window move events.
	Automatically cleans up the internal resources when iteration is over.
	Use in a `while` loop, ideally.
	Not thread-safe.
	*/
	IterateMoveEvent :: proc "c" (
		iterator: ^i32,
		val: ^WindowMoveData = { },
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Get the current state of a key.
	Returns a bitmask indicating if the key is pressed, held, or released this frame.
	Not thread-safe.
	*/
	GetKeyState :: proc "c" (
		key: KeyCode,
	) -> KeyState ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Get the mouse movement delta for this frame.
	Sets the provided pointers to the delta values (can pass NULL to ignore).
	deltaX, deltaY are relative mouse movement, deltaScroll is scroll wheel delta.
	Not thread-safe.
	*/
	GetMouseDelta :: proc "c" (
		deltaX: ^i32 = { },
		deltaY: ^i32 = { },
		deltaScroll: ^i32 = { },
	) ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Check if the application currently has focus.
	Returns true if the application has focus, false otherwise.
	Not thread-safe.
	*/
	DoesApplicationHaveFocus :: proc "c" () -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
	/*
	Get a dropped file path by its ID.
	The fileId comes from a DropFile event's droppedFileId field.
	Returns an empty string if the ID is invalid.
	The returned string is valid until the next call to DVRPL_GatherEvents.
	Not thread-safe.
	*/
	GetDroppedFile :: proc "c" (
		fileId: u16,
	) -> string ---
}

// #######################################################################################
// EntryPoint
// #######################################################################################

@(link_prefix="PNSLR_")
foreign {
	/*
	This is the main entry point of the application.
	It is not actually implemented inside the Dvaarpaal library,
	but rather in the application that uses the library.
	This is done to allow the application to have its own entry point.
	 *
	The code for the main entry point (platform-specific) will be included
	in the built static libraries, but if compiling from source, add
	`#define DVRPL_SKIP_ENTRY_PT` when compiling the source.
	*/
	Main :: proc "c" (
		args: []string,
	) -> i32 ---
}

