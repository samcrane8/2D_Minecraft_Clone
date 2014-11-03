#include "Inventory.h"


LPDIRECT3DTEXTURE9 Inventory::inventory = NULL;

Inventory::Inventory(void)
{
	crafting[0].change(new BlockStone(20));
	crafting[1].change(new BlockGlowStone(20));
	crafting[2].change(new BlockStone(20));
	crafting[3].change(new BlockGlowStone(20));
	crafted.change(new BlockStone(20));
	for (int i = 0; i <= 26; i++)
	{
		slots[i].change(new BlockStone(20));
	}
	for (int i = 0; i <= 9; i++)
	{
		quickSlots[i].change(new BlockGlowStone(20));
	}

	slots[26].change(new BlockStone(20));
}


Inventory::~Inventory(void)
{
	for (int i = 0; i <= 27; i++)
	{
		slots[i].free();
	}
	for (int i = 0; i < 4; i++)
	{
		crafting[i].free();
	}
	crafted.free();
	for (int i = 0; i <= 9; i++)
	{
		//quickSlots[i].free();
	}
}

void Inventory::draw(ModelBiped player, LPDIRECT3DTEXTURE9 playerTexture)
{
	//176, 165 (dimensions of inventory)
	int placeX = (SCREENW/2) - (176);
	int placeY = (SCREENH/2) - 165;

	//main inventory picture and darkening of screen
	Sprite_Transform_Draw(inventory, -120, -120, 16, 16, 0, 1, 0, 100, D3DCOLOR_ARGB(30, 30, 30, 120) );
	Sprite_Transform_Draw(inventory, placeX, placeY, 176, 165, 0, 1, 0, 2);
	//draw small player in box area.
	player.draw(playerTexture, placeX + 78, placeY + 43, 3.3, D3DCOLOR_XRGB(255, 255, 255) );

	int craftingX = placeX + 176;
	int craftingY = placeY + 52;
	//crafting table working
	for (int i = 0; i < 4; i++)
	{
			crafting[i].draw(craftingX, craftingY, 2);
			switch(i)
			{
			case 0:
				{
					craftingX += 18 * 2;
					break;
				}
			case 1:
				{
					craftingX -= 18 * 2;
					craftingY += 18 * 2;
					break;
				}
			case 2:
				{
					craftingX += 18 * 2;
					break;
				}
			}
	
	}
	//end cafting table

	//for possible crafted object working

	crafted.draw(placeX + 288, placeY + 72, 2);

	//draw slots (not quickslots)

	//start 7, 83
	int inventX = placeX + (8 * 2);
	int inventY = placeY + (84 * 2);
	for (int i = 0; i <= 27; i++)
	{
		slots[i].draw(inventX, inventY, 2);
		int column = i % 9;
		int row = i / 9;

		inventX = placeX + (8 * 2) + (column * 36);
		inventY = placeY + (84 * 2) + (row * 36);

	}

	//quickslots
	//7, 141
	int quickX = placeX + (8 * 2);
	int quickY = placeY + (142 * 2);

	for (int i = 0; i <= 9; i++)
	{
		quickSlots[i].draw(quickX, quickY, 2);	

		int column = i % 9;
		int row = i / 9;

		quickX = placeX + (8 * 2) + (column * 36);
		quickY = placeY + (142 * 2) + (row * 36);
	}
	
}

void Inventory::update(MyMouseCursor mouse)
{
	mouseSlotX = mouse.mouseX;
	mouseSlotY = mouse.mouseY;
}

bool Inventory::create(string s)
{
	inventory = LoadTexture(s);

	if (!inventory)
	{
		return false;
	}
	return true;
}

void Inventory::release()
{
	if (inventory)
	{
		inventory->Release();
	}
}