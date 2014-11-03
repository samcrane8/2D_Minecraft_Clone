#include "Block.h"

LPDIRECT3DTEXTURE9 Block::terrain = NULL;
int Block::COLUMN_LENGTH = 10;

Block::Block(int blockIndex)
	: iworldIndex(blockIndex),
	worldX(getXValue(blockIndex, COLUMN_LENGTH)),  //initializes worldX
	worldY(getYValue(blockIndex, COLUMN_LENGTH)),  //initializes worldY
	lightValue(0)
{
	
}


Block::~Block(void)
{
}




bool Block::createTerrain(string s)
{
	terrain = LoadTexture(s);
	if (!terrain)
	{
		return false;
	}

	return true;
}

bool Block::releaseTerrain()
{
	if (terrain)
	{
		terrain->Release();
		return true;
	}

	return false;
}

int Block::getXValue(int blockIndex, int COLUMN_LENGTH)
{
	return (blockIndex / COLUMN_LENGTH) * 16;
}

int Block::getYValue(int blockIndex, int COLUMN_LENGTH)
{
	return (blockIndex % COLUMN_LENGTH) * 16;
}

void Block::setBlocks(int iCOLUMN_LENGTH)
{
	COLUMN_LENGTH = iCOLUMN_LENGTH;
}

void Block::setLightValue(int newLightValue)
{
	lightValue = newLightValue;
	if (lightValue > 255)
	{
		lightValue = 255;
	}
	if (lightValue < 0)
	{
		lightValue = 0;
	}
}

void Block::incrementLightValue(int increment)
{
	lightValue += increment;
	if (lightValue > 255)
	{
		lightValue = 255;
	}
	if (lightValue < 0)
	{
		lightValue = 0;
	}
}