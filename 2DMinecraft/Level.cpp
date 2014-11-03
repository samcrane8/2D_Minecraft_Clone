#include "Level.h"
#include <math.h>

int COLUMN_LENGTH = 50;

Level::Level(void)
	: SCALE_FACTOR(2.5f),  // limit it from 2.0 to 6.0f
	COLUMN_LENGTH(128),
	BLOCK_NUMBER(100000),
	entityplayer(5000, 60)
{
	Block::setBlocks(COLUMN_LENGTH);

	for (int i = 0; i < BLOCK_NUMBER; i++)
	{
		delete blocks[i];
		blocks[i] = new BlockAir(i);
		if (blocks[i]->worldY >= 150)
		{
			delete blocks[i];
			blocks[i] = new BlockGlowStone(i);
		}
	}
	for (int i = 0; i < BLOCK_NUMBER; i++)
	{
		updateLight(i);
	}
}


Level::~Level(void)
{
	for (int i = 0; i < BLOCK_NUMBER; i++)
	{
		delete blocks[i];
	}
}

void Level::updateScreen(MyMouseCursor mousecursor, InputHandler inputhandler)
{

	entityplayer.updatePlayer(inputhandler, SCALE_FACTOR);
	entityplayer.restingOnBlock = topOfBlockCollision();
	checkCollisions();
	entityplayer.updateCenter(centerX, centerY);
	entityplayer.lightValue = updateLight(getIndexValue(entityplayer.x, entityplayer.y));
	if (entityplayer.inventory.open == true)
	{
		entityplayer.inventory.update(mousecursor);
	}
	if (!entityplayer.inventory.open)
	{
		checkClick(mousecursor);
	}

}

void Level::renderScreen()
{
	int difX = (SCREENW/2) / (SCALE_FACTOR) + 16;
	int difY = (SCREENH/2) / (SCALE_FACTOR) + 16;

	int originX = centerX - difX;
	if (originX < 0) originX = 0;
	int originY = centerY - difY;
	if (originY < 0) originY = 0;

	int originIndex = getIndexValue(centerX, centerY) - getIndexValue(difX, difY);
	if (originIndex < 0) originIndex = 0;
	
	int endIndex = getIndexValue(centerX, centerY) + getIndexValue(difX, difY) + 1;
	if (endIndex > BLOCK_NUMBER) endIndex = BLOCK_NUMBER;

	int endY = (2 * difY) * (2 * difY);
	endY = (int)sqrt((double)endY);
	endY += centerY;

	for(int blockIndex = originIndex; blockIndex < endIndex; blockIndex++)
	{
			if (blocks[blockIndex]->worldY < originY)
			{
				blockIndex = getIndexValue(blocks[blockIndex]->worldX, originY);
			}

			if (blockIndex > BLOCK_NUMBER) blockIndex = BLOCK_NUMBER - 1;

			if (blocks[blockIndex]->worldY > centerY + difY)
			{
				blockIndex = getIndexValue(blocks[blockIndex]->worldX + 16, originY);
				if (blockIndex >= endIndex) blockIndex = endIndex - 1;
			}
			else
			{
			int difX = centerX - blocks[blockIndex]->worldX;
			difX *= SCALE_FACTOR;

			int difY = centerY - blocks[blockIndex]->worldY;
			difY *= SCALE_FACTOR;
				
			int screenX = (SCREENW/2) - difX;
			int screenY = (SCREENH/2) - difY;

			blocks[blockIndex]->draw(screenX, screenY, SCALE_FACTOR);
			}
			

	}

	//drawing of the player.

	entityplayer.draw(SCALE_FACTOR, centerX, centerY);

	if (entityplayer.inventory.open) entityplayer.inventory.draw(entityplayer.playerModel, entityplayer.playerTexture);

	return;
}

void Level::checkClick(MyMouseCursor mousecursor)
{
		double iworldX = mousecursor.mouseX - (SCREENW/2); //this is all correct, it's something else...
		iworldX += SCALE_FACTOR * centerX;  //hmmm...
		iworldX /= SCALE_FACTOR;

		double iworldY = mousecursor.mouseY - (SCREENH/2);
		iworldY += SCALE_FACTOR * centerY;
		iworldY /= SCALE_FACTOR;
		
		int indexValue = getIndexValue((int)iworldX, (int)iworldY);

		

		if (indexValue < 0) return;
		if (indexValue > BLOCK_NUMBER) return;

		if (mousecursor.mouse0 == true)
		{
		delete blocks[indexValue];
		blocks[indexValue] = new BlockAir(indexValue);
		updateLight(indexValue);
		}

		if (mousecursor.mouse1 == true)
		{
		RECT dest;
		RECT block = { blocks[indexValue]->worldX, blocks[indexValue]->worldY, blocks[indexValue]->worldX + 16, blocks[indexValue]->worldY + 16 };
		RECT player = { entityplayer.x, entityplayer.y, entityplayer.x + 16, entityplayer.y + 32};
		if (!Collision(dest, block, player) && !blocks[indexValue]->checkSolid())
			{
			delete blocks[indexValue];
			blocks[indexValue] = new BlockStone(indexValue);
			updateLight(indexValue);
			}
		}
		if (mousecursor.mouse4 == true)
		{
		RECT dest;
		RECT block = { blocks[indexValue]->worldX, blocks[indexValue]->worldY, blocks[indexValue]->worldX + 16, blocks[indexValue]->worldY + 16 };
		RECT player = { entityplayer.x, entityplayer.y, entityplayer.x + 16, entityplayer.y + 32};
		if (!Collision(dest, block, player) && !blocks[indexValue]->checkSolid())
			{
			delete blocks[indexValue];
			blocks[indexValue] = new BlockGlowStone(indexValue);
			updateLight(indexValue);
			}
		}
		if (mousecursor.mouse3 == true)
		{
			blocks[indexValue]->incrementLightValue(1);
		}
		if (mousecursor.mouse2 == true)
		{
			blocks[indexValue]->incrementLightValue(-1);
		}
}

bool Level::topOfBlockCollision()
{
	if (entityplayer.x < 0) entityplayer.x = 0;

	int originIndex = getIndexValue(entityplayer.x, entityplayer.y);
	if (originIndex < 0) originIndex = 0;
	
	int endIndex = getIndexValue(entityplayer.x + 15, entityplayer.y + 29) + 1;
	if (endIndex > BLOCK_NUMBER) endIndex = BLOCK_NUMBER;



	for(int blockIndex = originIndex; blockIndex < endIndex; blockIndex++) //should only check objects in vector direction in future.
	{
			if (blocks[blockIndex]->worldY < entityplayer.y)
			{
				blockIndex = getIndexValue(blocks[blockIndex]->worldX, entityplayer.y);
			}
			if (blocks[blockIndex]->worldY > entityplayer.y + 30)
			{
				blockIndex = getIndexValue(blocks[blockIndex]->worldX + 16, entityplayer.y);
				if (blockIndex >= endIndex) blockIndex = endIndex;
			}
		RECT block = { blocks[blockIndex]->worldX, blocks[blockIndex]->worldY, blocks[blockIndex]->worldX + 16, blocks[blockIndex]->worldY + 16 };
		RECT playerY = { entityplayer.x - entityplayer.velX, entityplayer.y, entityplayer.x + 16 - entityplayer.velX, entityplayer.y + 30};
		RECT dest;

		if (blocks[blockIndex]->checkSolid() && Collision(dest, playerY, block))
			{
				return true;
			}
	}

	return false;
}

void Level::checkCollisions()
{

	if (entityplayer.y < 0) entityplayer.y = 0;
	if (entityplayer.x < 0) entityplayer.x = 0;

	int originIndex = getIndexValue(entityplayer.x, entityplayer.y);
	if (originIndex < 0) originIndex = 0;
	
	int endIndex = getIndexValue(entityplayer.x + 15, entityplayer.y + 29) + 1;
	if (endIndex > BLOCK_NUMBER) endIndex = BLOCK_NUMBER;



	for(int blockIndex = originIndex; blockIndex < endIndex; blockIndex++) //should only check objects in vector direction in future.
	{
			if (blocks[blockIndex]->worldY < entityplayer.y)
			{
				blockIndex = getIndexValue(blocks[blockIndex]->worldX, entityplayer.y);
			}
			if (blocks[blockIndex]->worldY > entityplayer.y + 30)
			{
				blockIndex = getIndexValue(blocks[blockIndex]->worldX + 16, entityplayer.y);
				if (blockIndex >= endIndex) blockIndex = endIndex;
			}

			//checking of teh collisions.
			RECT block = { blocks[blockIndex]->worldX, blocks[blockIndex]->worldY, blocks[blockIndex]->worldX + 16, blocks[blockIndex]->worldY + 16 };
			RECT playerY = { entityplayer.x - entityplayer.velX, entityplayer.y, entityplayer.x + 16 - entityplayer.velX, entityplayer.y + 30};
			RECT dest;

			RECT playerX = { entityplayer.x, entityplayer.y - entityplayer.velY, entityplayer.x + 16, entityplayer.y + 30 - entityplayer.velY};
			
			if (blocks[blockIndex]->checkSolid() && Collision(dest, playerX, block))
			{

				if (entityplayer.velX > 0)
				{
					entityplayer.x += dest.left - dest.right;
				}
				else
				{
					entityplayer.x -= dest.left - dest.right;
				}
				
				entityplayer.velX = 0;
			}
			if (blocks[blockIndex]->checkSolid() && Collision(dest, playerY, block))
			{
				if (entityplayer.velY < 0)
				{
					entityplayer.y -= dest.top - dest.bottom;
				}
				else
				{
					entityplayer.y += dest.top - dest.bottom;
				}
				
				entityplayer.velY = 0;
			}
			
	}
	
}

int Level::updateLight(int indexValue)
{
	int startingPoint = indexValue;

	for (int i = blocks[indexValue]->worldY - 16; i > 0; )
	{
		int newIndexValue = getIndexValue(blocks[indexValue]->worldX, i);
		if (blocks[newIndexValue]->checkSolid() )
		{
			startingPoint = newIndexValue;
		}
		i -= 16;
	}

	int lightDivisor = 1;

	for(int i = 0; i < 20; i++)
	{
		if (blocks[startingPoint + i]->checkSolid() ) lightDivisor++;
		blocks[startingPoint + i]->lightValue = 255 / (2 *lightDivisor);
		if (blocks[startingPoint+ i]->lightValue < 0) blocks[startingPoint+ i]->lightValue = 0;
	}
	int xIndexBack = startingPoint;
	int xIndexForward = startingPoint;
	lightDivisor = 1;
	int lightDivisorForwards = 1;
	for(int i = 1; i < 5; i++)
	{
		xIndexBack -= getIndexValue(1, 0);
		xIndexForward += getIndexValue(1, 0);
		if (blocks[xIndexBack]->checkSolid() ) lightDivisor++;
		if (blocks[xIndexBack]->lightValue < 255 / (2 * lightDivisor) )
		{
			blocks[xIndexBack]->lightValue = 255 / (2 * lightDivisor);
		}
		if (blocks[xIndexForward]->checkSolid() ) lightDivisorForwards++;
		if (blocks[xIndexForward]->lightValue < 255 / (2 * lightDivisor) )
		{
			blocks[xIndexForward]->lightValue = 255 / (2 * lightDivisor);
		}
	}
	return blocks[xIndexForward]->lightValue;
}

int Level::getIndexValue(int x, int y)
{
	return (x / 16) * COLUMN_LENGTH + (y / 16); 
}

int Level::getXValue(int blockIndex)
{
	return (blockIndex / COLUMN_LENGTH) * 16;
}

int Level::getYValue(int blockIndex)
{
	return (blockIndex % (int)COLUMN_LENGTH) * 16;
}