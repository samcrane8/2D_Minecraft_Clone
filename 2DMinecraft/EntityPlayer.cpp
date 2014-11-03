#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(int x, int y)
	: x(x),
	y(y),
	restingOnBlock(true),
	frame(0),
	velX(0),
	velY(0)
{
	timeInventory = (int)GetTickCount();
	delay = 120;
}

LPDIRECT3DTEXTURE9 EntityPlayer::playerTexture = NULL;
ModelBiped EntityPlayer::playerModel = ModelBiped();


EntityPlayer::~EntityPlayer(void)
{
	
}

void EntityPlayer::updatePlayer( InputHandler inputhandler, float &SCALE_FACTOR)
{
	userInput(SCALE_FACTOR, inputhandler);

}

void EntityPlayer::updateCenter(int &centerX, int &centerY)
{
	centerX = x + 8;
	if (centerX < 0) centerX = 0;
	centerY = y + 16;
	if (centerY < 0) centerY = 0;
}

void EntityPlayer::draw(float &SCALE_FACTOR, int &centerX, int &centerY)
{
	float playerScale = SCALE_FACTOR * .9;
	int difX = centerX - x;
	difX *= playerScale;
	int difY = centerY - y;
	difY *= playerScale;

	int screenX = (SCREENW/2) - difX;
	int screenY = (SCREENH/2) - difY;

	
	playerModel.draw(playerTexture, screenX, screenY, SCALE_FACTOR, D3DCOLOR_RGBA(lightValue, lightValue, lightValue, 255));
}

void EntityPlayer::userInput(float &SCALE_FACTOR, InputHandler inputhandler)
{
	if (Key_Down(DIK_E))
	{
		if ((int)GetTickCount() > timeInventory + delay)
		{
			inventory.open = !inventory.open;
			timeInventory = (int)GetTickCount();
		}
		
	}

	if (restingOnBlock)
	{
		velX = 0;
	}

	velY += 1;

	if (inventory.open == true)
	{
		x += velX;
		y += velY;
		return;
	}


	int DELAY = 1;

	if (Key_Down(DIK_Q))
	{
		SCALE_FACTOR += 0.1f;
		if (SCALE_FACTOR > 4.0f) SCALE_FACTOR = 4.0f;
	}

	if (Key_Down(DIK_V))
	{
		SCALE_FACTOR -= 0.1f;
		if (SCALE_FACTOR < 2.0f) SCALE_FACTOR = 2.0f;
	}

	if (Key_Down(DIK_SPACE) && restingOnBlock)
		{
			velY -= 10;
		}
	if (Key_Down(DIK_A))
		{
			velX -= 5;
			playerModel.animateWalkRight(frame);
		}

	if (Key_Down(DIK_D))
		{
			velX += 5;
			playerModel.animateWalkRight(frame);
		}

	if ((velX == 0))
	{
		playerModel.animateStanding(frame);
	}

	if (velX > 5) velX = 5;
	if (velX < -5) velX = -5;

	x += velX;
	y += velY;
}

bool EntityPlayer::createTexture(string s)
{
	playerTexture = LoadTexture(s);
	if (!playerTexture)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void EntityPlayer::release()
{
	playerTexture->Release();
	
}