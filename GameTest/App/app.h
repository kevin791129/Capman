//---------------------------------------------------------------------------------
// App.h
//---------------------------------------------------------------------------------
#ifndef _APP_H
#define _APP_H
//---------------------------------------------------------------------------------
#include <windows.h> 
//---------------------------------------------------------------------------------
#include "../glut/include/GL/freeglut.h"
//#include "../glut/glut.h"
#include "AppSettings.h"
#include "SimpleController.h"

//---------------------------------------------------------------------------------
// App namespace: These are the IO calls you can use for you game.
//---------------------------------------------------------------------------------
namespace App
{
	//*******************************************************************************************
	// Display Calls.
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// void DrawLine( float sx, float sy, float ex, float ey, float r = 1.0f, float g = 1.0f, float b = 1.0f );
	//-------------------------------------------------------------------------------------------
	// Draw a 2D Line from sx,sy to ex, ey using color r = red, g = green, b=blue.
	//-------------------------------------------------------------------------------------------
	void DrawLine( float sx, float sy, float ex, float ey, float r = 1.0f, float g = 1.0f, float b = 1.0f );
    void DrawQuad(float sx, float sy, float ex, float ey, float r, float g, float b);
	//-------------------------------------------------------------------------------------------
	// void DrawNgon(float cx, float cy, float radius, float startAngle = 0, float endAngle = 360, float r = 1.0f, float g = 1.0f, float b = 1.0f, int sliceCount = 72);
	//-------------------------------------------------------------------------------------------
	// Draw a sliceCount-sided polygon, center at (cx, cy) and points radius away from center.
	// Rotate with startAngle, option to leave sides no drawn with endAngle, and rgb for color.
	//-------------------------------------------------------------------------------------------
	void DrawNgon(float cx, float cy, float radius, float startAngle = 0, float endAngle = 360, float r = 1.0f, float g = 1.0f, float b = 1.0f, int sliceCount = 72);
	//-------------------------------------------------------------------------------------------
	// void Print(float x, float y, const char *text, float r = 1.0f, float g = 1.0f, float b = 1.0f, void *font = GLUT_BITMAP_HELVETICA_18);
	//-------------------------------------------------------------------------------------------
	// Print text to screen at x,y coordinates using color r = red, g = green, b=blue using the passed GLUT font. 
	// Color values are in the range 0.0f to 1.0f.
	// Available fonts...
	// GLUT_BITMAP_9_BY_15, GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_10, GLUT_BITMAP_TIMES_ROMAN_24
	// GLUT_BITMAP_HELVETICA_10, GLUT_BITMAP_HELVETICA_12, GLUT_BITMAP_HELVETICA_18	
	//-------------------------------------------------------------------------------------------
	void Print(float x, float y, const char *text, float r = 1.0f, float g = 1.0f, float b = 1.0f, void *font = GLUT_BITMAP_HELVETICA_18);

	//*******************************************************************************************
	// Sound handling.	
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// void PlaySound(const char *fileName, bool looping = false);
	//-------------------------------------------------------------------------------------------
	// Plays the passed .wav file. Set looping to true if you want the sound to loop.
	// If the sound is already playing it will restart.
	//-------------------------------------------------------------------------------------------
	void PlaySound(const char *fileName, bool looping = false);

	//-------------------------------------------------------------------------------------------
	// void StopSound(const char *fileName);
	//-------------------------------------------------------------------------------------------	
	// Stops the given .wav file from playing.
	//-------------------------------------------------------------------------------------------	
	void StopSound(const char *fileName);

	//-------------------------------------------------------------------------------------------
	// bool IsSoundPlaying(const char *filename);
	//-------------------------------------------------------------------------------------------	
	// Returns true if the given .wav file is currently playing.
	//-------------------------------------------------------------------------------------------	
	bool IsSoundPlaying(const char *filename);
	
	//*******************************************************************************************
	// Input handling.	
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// bool IsKeyPressed(int key);
	//-------------------------------------------------------------------------------------------
	// Returns true if the given key is currently being pressed. Uses windows keys, see WinUser.h 
	// e.g.
	// IsKeyPressed(VK_F1); // Is the F1 key pressed.
	// IsKeyPressed('A'); // Is the 'A' key pressed.
	//-------------------------------------------------------------------------------------------
	bool IsKeyPressed(int key);

	//-------------------------------------------------------------------------------------------
	// void GetMousePos(float &x, float &y);
	//-------------------------------------------------------------------------------------------
	// Sets the value of the passed in float references to the current position of the mouse pointer.	
	//-------------------------------------------------------------------------------------------
	void GetMousePos(float &x, float &y);

	//-------------------------------------------------------------------------------------------
	// const CController &GetController(int pad = 0);
	//-------------------------------------------------------------------------------------------
	// Returns a reference to a game controller. 
	// You can use this object to query gamepad buttons and analog stick positions etc.
	// e.g.
	// GetController(0).CheckButton(XINPUT_GAMEPAD_A, false); Returns true if the A button of pad 0 was pressed and repeat if held.
	// GetController(0).CheckButton(XINPUT_GAMEPAD_A, true); Returns true if the A button of pad 0 was pressed but DO NOT repeat if held.	
	// GetController(0).GetLeftThumbStickX(); Returns a float between -1.0f to 1.0f representing the position of the left thumb sticks X Axis.
	// See SimpleController.h for more info.
	//-------------------------------------------------------------------------------------------
	const CController &GetController( int pad = 0 );

    void CreateRandomTileMap(int dimensions = 20, int maxTunnels = 200, int maxLength = 4);
    void RenderTileMap();
    int GetTileMapValue(int x, int y);
};
#endif //_APP_H