#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FULLSCREEN false
#define WINDOW_BORDERLESS false
#define WINDOW_RESIZABLE false
#define FULLSCREEN_DESKTOP false

#define VSYNC true
#define TITLE "Super Awesome Game"
#define SPRITE_FILE "sprites.png"

#endif // !_GLOBALS_H