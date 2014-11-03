#include "BlockAir.h"

BlockHelper BlockAir::blockhelper = BlockHelper(160, 1.0f, false);

BlockAir::BlockAir(int worldIndex)
	: Block(worldIndex)
{
}


BlockAir::~BlockAir(void)
{
}

void BlockAir::draw(int x, int y, float SCALE_FACTOR)
{
	/*
	BlockAir::blockhelper.arender.scaling = SCALE_FACTOR;
	BlockAir::blockhelper.abreaking.scaling = SCALE_FACTOR;
	BlockAir::blockhelper.arender.draw(terrain, x, y, blockhelper.arender.color);
	*/
}

bool BlockAir::checkSolid()
{
	return blockhelper.solid;
}

bool BlockAir::checkLightSource()
{
	return blockhelper.lightSource;
}