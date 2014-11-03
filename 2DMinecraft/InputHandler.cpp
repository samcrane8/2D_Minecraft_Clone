#include "InputHandler.h"


InputHandler::InputHandler(int x, int y)
	: mouseX(x),
	mouseY(y)
{
	Q = false;
	A = false;
	S = false;
	W = false;
	D = false;
	SPACE = false;
	mouse0 = false;
	mouse1 = false;
}


InputHandler::~InputHandler(void)
{
}

void InputHandler::userInput()
{
	Q = false;
	A = false;
	S = false;
	W = false;
	D = false;
	SPACE = false;
	mouse0 = false;
	mouse1 = false;

	if (Key_Down(DIK_Q))
	{
		Q = true;
	}

	if (Key_Down(DIK_SPACE))
	{
		SPACE = true;
	}

	if (Key_Down(DIK_W))
		{
			W = true;
		}

	if (Key_Down(DIK_S))
		{
			S = true;
		}
	if (Key_Down(DIK_A))
		{
			A = true;
		}

	if (Key_Down(DIK_D))
		{
			D = true;
		}
	
}

void InputHandler::checkClick(HWND hWnd)
{
	getMouse(mouseX, mouseY, hWnd);
}