#include "BlockStone.h"

BlockHelper BlockStone::blockhelper = BlockHelper(1, 0.9f);

BlockStone::BlockStone(int worldIndex)
	: Block(worldIndex)
{
}


BlockStone::~BlockStone(void)
{
}

void BlockStone::draw(int x, int y, float SCALE_FACTOR)
{
	BlockStone::blockhelper.arender.scaling = SCALE_FACTOR;
	BlockStone::blockhelper.abreaking.scaling = SCALE_FACTOR;
	BlockStone::blockhelper.arender.draw(terrain, x, y, D3DCOLOR_RGBA(lightValue, lightValue, lightValue, 255));
}

bool BlockStone::checkSolid()
{
	return blockhelper.solid;
}

bool BlockStone::checkLightSource()
{
	return blockhelper.lightSource;
}