#pragma once
#include "MyMouseCursor.h"
#include "Entity.h"
#include "MyDirectX.h"
#include "InputHandler.h"
#include "ModelBiped.h"
#include "Inventory.h"
class EntityPlayer :
	public Entity
{
public:
	EntityPlayer(int x, int y);
	~EntityPlayer(void);

	Animation placeHolder;

	static LPDIRECT3DTEXTURE9 playerTexture;
	static ModelBiped playerModel;

	void updatePlayer( InputHandler inputhandler, float &SCALE_FACTOR);
	void updateCenter(int &centerX, int &centerY);
	void draw(float &SCALE_FACTOR, int &centerX, int &centerY);


	static bool createTexture(string s);
	static void release();

	bool restingOnBlock;

	int lightValue;

	int frame;

	int delay;
	int timeInventory;

	double velX;
	double velY;

	int x;
	int y;

	Inventory inventory;

private:
	void userInput(float &SCALE_FACTOR, InputHandler inputhandler);
};

