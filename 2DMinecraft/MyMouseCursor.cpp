#include "MyMouseCursor.h"

LPDIRECT3DTEXTURE9 MyMouseCursor::cursorTexture = NULL;

MyMouseCursor::MyMouseCursor()
{
}


MyMouseCursor::~MyMouseCursor(void)
{
}

void MyMouseCursor::update(InputHandler inputhandler, HWND hwnd)
{
	inputhandler.checkClick(hwnd);

	mouse0 = false;
	mouse1 = false;
	mouse2 = false;
	mouse3 = false;
	mouse4 = false;

	mouseX = inputhandler.mouseX;
	mouseY = inputhandler.mouseY;
	
	if (Mouse_Button(0))
	{
		mouse0 = true;
	}
	if (Mouse_Button(1))
	{
		mouse1 = true;
	}
	if (Mouse_Button(2))
	{
		mouse2 = true;
	}
	if (Mouse_Button(3))
	{
		mouse3 = true;
	}
	if (Mouse_Button(4))
	{
		mouse4 = true;
	}
}

void MyMouseCursor::draw()
{
	Sprite_Transform_Draw(cursorTexture, mouseX, mouseY, 20, 20, 0, 1, 0, 3);
}

bool MyMouseCursor::createTexture(string s1)
{
		cursorTexture = LoadTexture(s1);
	if (!cursorTexture)
	{
		return false;
	}
}

void MyMouseCursor::Release()
{
	cursorTexture->Release();
}