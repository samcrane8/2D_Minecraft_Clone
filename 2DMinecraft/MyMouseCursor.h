#pragma once

#include "MyDirectX.h"
#include "InputHandler.h"

class MyMouseCursor
{
public:
	MyMouseCursor(void);
	~MyMouseCursor(void);

	static LPDIRECT3DTEXTURE9 cursorTexture;
	static bool createTexture(string s1);
	static void Release();

	void update(InputHandler inputhandler, HWND hwnd);
	void draw();

	int mouseX;
	int mouseY;

	bool mouse0;
	bool mouse1;
	bool mouse2;
	bool mouse3;
	bool mouse4;
};

