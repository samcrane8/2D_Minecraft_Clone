#pragma once

#include "Entity.h"
#include "MyMouseCursor.h"
#include "MyDirectX.h"
#include "ModelBiped.h"
#include "Block.h"
#include "BlockGlowStone.h"
#include "BlockStone.h"
#include <string>

struct SLOT
{
	int quantity;
	Block* block;

	SLOT()
	{
		quantity = 0;
		block = NULL;
	}

	void draw(int x, int y, float SCALE_FACTOR)
	{
		if (block != NULL)
		{
			block->draw(x, y, SCALE_FACTOR);
		}
		
	}

	void free()
	{
		delete block;
	}

	void change(Block* newBlock)
	{
		free();
		block = newBlock;
		block->lightValue = 255;
	}


};


class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	SLOT slots[27];
	SLOT quickSlots[9];
	SLOT crafting[4];

	SLOT crafted;
	
	SLOT mouseSlot;

	int mouseSlotX;
	int mouseSlotY;

	void update(MyMouseCursor mouse);
	void draw(ModelBiped player, LPDIRECT3DTEXTURE9 playerTexture);

	static LPDIRECT3DTEXTURE9 inventory;
	static bool create(string s);
	static void release();

	bool open;
};

//details what the player has and all that good stuff.


