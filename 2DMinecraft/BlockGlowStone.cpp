#include "BlockGlowStone.h"

BlockHelper BlockGlowStone::blockhelper = BlockHelper(99, 0.5f, true, true);

BlockGlowStone::BlockGlowStone(int worldIndex)
	: Block(worldIndex)
{
	lightValue = 255;
}


BlockGlowStone::~BlockGlowStone(void)
{
}

void BlockGlowStone::draw(int x, int y, float SCALE_FACTOR)
{
	BlockGlowStone::blockhelper.arender.scaling = SCALE_FACTOR;
	BlockGlowStone::blockhelper.abreaking.scaling = SCALE_FACTOR;
	BlockGlowStone::blockhelper.arender.draw(terrain, x, y, D3DCOLOR_RGBA(lightValue, lightValue, lightValue, 255));
}

bool BlockGlowStone::checkSolid()
{
	return blockhelper.solid;
}

bool BlockGlowStone::checkLightSource()
{
	return blockhelper.lightSource;
}