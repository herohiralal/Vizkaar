package Dvaarpaal

import "../Intrinsics"
import "../Panshilar"

// #######################################################################################
// Window
// #######################################################################################

/**
 * A cross-platform opaque handle to a window.
 * On Windows, this is an HWND.
 * On OSX, this is an NSWindow*.
 * On Android, this is an ANativeWindow*.
 */
Window :: struct  {
	handle: u64,
}

/**
 * A cross-platform opaque handle to saved information for a window.
 */
SavedWindowData :: struct #align(8)  {
	buffer: [40]u8,
}

/**
 * A cross-platform opaque handle for window data.
 * Includes some amount of saved data for the window.
 */
WindowData :: struct  {
	window: Window,
	savedData: SavedWindowData,
}

/**
 * Options for creating a window.
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
    /**
     * Creates a window with the specified options.
     * Returns a handle to the created window.
     * If creation failed, the returned handle will be zeroed.
     * Not thread-safe.
     */
	CreateWindow :: proc "c" (
		options: WindowCreationOptions,
	) -> WindowData ---
}

@(link_prefix="PNSLR_")
foreign {
    /**
     * Destroys the specified window.
     * Not thread-safe.
     */
	DestroyWindow :: proc "c" (
		window: ^WindowData,
	) ---
}

@(link_prefix="PNSLR_")
foreign {
    /**
     * Sets the window's fullscreen status.
     * Returns true on success, false on failure.
     * If entering fullscreen, the previous position and size are stored in the provided pointers.
     * If exiting fullscreen, the window is restored to the provided position and size.
     * If posX, posY, sizeX or sizeY are null, reasonable defaults are used instead.
     * Not thread-safe.
     */
	SetFullScreen :: proc "c" (
		window: ^WindowData,
		status: b8,
		posX: ^i16,
		posY: ^i16,
		sizeX: ^u16,
		sizeY: ^u16,
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
    /**
     * Gets the window's current position and size.
     * Returns true on success, false on failure.
     * If any of posX, posY, sizeX or sizeY are null, they are ignored, otherwise
     * the corresponding value is written to the provided pointer.
     * Not thread-safe.
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
    /**
     * Get the current position of the pointer relative to the window's top-left corner.
     * Returns true on success, false on failure.
     * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
     * Not thread-safe.
     */
	GetPtrPosFromWindow :: proc "c" (
		window: Window,
		posX: ^i16,
		posY: ^i16,
	) -> b8 ---
}

@(link_prefix="PNSLR_")
foreign {
    /**
     * Get the current position of the pointer relative to the screen's top-left corner.
     * Returns true on success, false on failure.
     * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
     * Not thread-safe.
     */
	GetPtrPos :: proc "c" (
		posX: ^i16,
		posY: ^i16,
	) -> b8 ---
}

// #######################################################################################
// EntryPoint
// #######################################################################################

@(link_prefix="PNSLR_")
foreign {
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
	Main :: proc "c" (
		args: []string,
	) -> i32 ---
}

