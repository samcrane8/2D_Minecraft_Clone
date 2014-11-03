// Beginning Game Programming, Third Edition
// MyGame.cpp

#include <iostream>
#include <fstream>
#include <sstream>

#include "MyDirectX.h"
#include "InputHandler.h"
#include "MyMouseCursor.h"
#include "Inventory.h"
#include "Level.h"
#include "Block.h"
#include "BlockAir.h"
#include "BlockStone.h"

#include "entity.h"
#include "EntityPlayer.h"
using namespace std;

const string APPTITLE = "Minecraft 2D";
extern const int SCREENW = 1920;
extern const int SCREENH = 1440;

int frame = 0;
int starttime = 0;

Level level;

InputHandler inputhandler(400, 400);
MyMouseCursor mousecursor;



extern LPD3DXFONT font = NULL;

extern D3DCOLOR day = D3DCOLOR_XRGB(127, 204, 255);

void debug();

bool Game_Init(HWND window)
{
    //initialize Direct3D
    if (!Direct3D_Init(window, SCREENW, SCREENH, false))
    {
        MessageBox(0, "Error initializing Direct3D","ERROR",0);
        return false;
    }

    //initialize DirectInput
    if (!DirectInput_Init(window))
    {
        MessageBox(0, "Error initializing DirectInput","ERROR",0);
        return false;
    }

	//initialize LightThread


	if (!Block::createTerrain("terrain.png")) return false;
	if (!EntityPlayer::createTexture("terrain.png")) return false;

	if (!MyMouseCursor::createTexture("cursor.png")) return false;

	if (!Inventory::create("inventory.png")) return false;

	font = MakeFont("Arial", 20);

    return true;
}

void Game_Run(HWND window)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //update input devices
    DirectInput_Update();

	//sets mouse coordinates
	inputhandler.userInput();
	mousecursor.update(inputhandler, window);
    level.updateScreen(mousecursor, inputhandler);
	//clear the scene
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, day, 1.0f, 0);

    //start rendering
    if (d3ddev->BeginScene())
    {
        //start drawing
        spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		
		
		level.renderScreen();

		mousecursor.draw();
	
		debug();


		//stop drawing
        spriteobj->End();

        //stop rendering
        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    //Escape key ends program
	//exit when escape key is pressed
	if (KEY_DOWN(VK_ESCAPE)) gameover = true;

    //controller Back button also ends
    if (controllers[0].wButtons & XINPUT_GAMEPAD_BACK)
        gameover = true;

	
}

void Game_End()
{
	font->Release();


	Block::releaseTerrain();
	EntityPlayer::release();
	Inventory::release();

    //free memory and shut down
    DirectInput_Shutdown();
    Direct3D_Shutdown();
}


void debug()
{
	Sprite_Transform_Draw(Block::terrain, 0, 0, 20, 20, 0, 1, 0, 1);
	
		FontPrint(font, 0, 0, "Screen");

		string s;
		stringstream out;
		out << mousecursor.mouseX;
		s = out.str();

		FontPrint(font, 70, 0, s);
		out = stringstream("");
		out << mousecursor.mouseY;
		s = out.str();

		FontPrint(font, 110, 0, s);
		out = stringstream("");
		out << level.entityplayer.velX << " " << level.entityplayer.velY;
		s = out.str();
		FontPrint(font, 150, 40, s);
		out = stringstream("");
		out << level.entityplayer.x << " " << level.entityplayer.y;
		s = out.str();
		FontPrint(font, 190, 0, s);
}

