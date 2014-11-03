#include "BlockHelper.h"


BlockHelper::BlockHelper(int terrainIndex, float ihardness,
	bool bsolid, bool blightsource, int animationLength)
	: solid(bsolid),
	hardness(ihardness),
	lightSource(blightsource)
{
	abreaking.columns = 10;
	abreaking.height = abreaking.width = 16;
	abreaking.startX = 0;
	abreaking.startY = 240;
	abreaking.direction = 1;
	abreaking.startframe = 0;
	abreaking.endframe = 9;
	abreaking.frame = 0;
	abreaking.delay =  hardness * 100;
	abreaking.scaling = 1;

	arender.startX = (terrainIndex % 15) * 16;
	arender.startY = (terrainIndex / 15) * 16;

	arender.columns = 1;
	arender.height = arender.width = 16;
	arender.startframe = 0;
	arender.endframe = animationLength;
	arender.frame = 0;
	arender.delay = 1000;
	arender.scaling = 1;
}


BlockHelper::~BlockHelper(void)
{
}


bool BlockHelper::breakBlock(LPDIRECT3DTEXTURE9 lpTerrain, int screenX, int screenY) //true means the block has been broken.
{																		 //false means the block has not been broken.
	abreaking.animate();
	abreaking.draw(lpTerrain, screenX, screenY, abreaking.color);
	if (abreaking.frame == abreaking.endframe - 1)
		{
			abreaking.frame = 0;
			return true;
		}
	return false;
}

//x and y value should be screenX and screenY values


void BlockHelper::renderBlock(LPDIRECT3DTEXTURE9 lpTerrain, int x, int y)
{
	arender.draw(lpTerrain, x, y, arender.color);
}