#pragma once
#include "MyDirectX.h"

class InputHandler
{
public:
	InputHandler(int x, int y);
	~InputHandler(void);

	void userInput();

	void checkClick(HWND hWnd);

	bool Q;
	bool A;
	bool S;
	bool W;
	bool D;
	bool SPACE;
	bool mouse0;
	bool mouse1;

	int mouseX;
	int mouseY;
};

