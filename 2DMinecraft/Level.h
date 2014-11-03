#pragma once

#include <sstream>

#include "InputHandler.h"
#include "Block.h"
#include "BlockAir.h"
#include "BlockStone.h"
#include "BlockGlowStone.h"
#include "entity.h"
#include "EntityPlayer.h"

class Level
{
public:
	Level(void);
	~Level(void);

	int centerX;
	int centerY;

	EntityPlayer entityplayer;

	float SCALE_FACTOR;
	double COLUMN_LENGTH;
	int BLOCK_NUMBER; // 100

	void updateScreen(MyMouseCursor mousecursor, InputHandler inputhandler);
	void renderScreen();
	int getIndexValue(int x, int y);
	int getXValue(int blockIndex);
	int getYValue(int blockIndex);
	void checkCollisions();

	bool topOfBlockCollision();
	void verticalCollision();

	int updateLight(int indexValue);

	void checkClick(MyMouseCursor mousecursor);

	Block* blocks[100000];
};

