#pragma once

#include "Entity.h"
#include "Animation.h"
#include "BlockHelper.h"

class Block : public Entity
{
public:
	Block(int blockIndex);
	virtual ~Block(void);

	int iworldIndex;

	int worldX;
	int worldY;

	int lightValue;

	static LPDIRECT3DTEXTURE9 terrain;

	static bool createTerrain(string s);
	static bool releaseTerrain();
	static int COLUMN_LENGTH;

	static void setBlocks(int iCOLUMN_LENGTH);

	virtual bool checkSolid() = 0;
	virtual bool checkLightSource() = 0;

	static int getXValue(int blockIndex, int COLUMN_LENGTH);
	static int getYValue(int blockIndex, int COLUMN_LENGTH);

	virtual void draw(int x, int y, float SCALE_FACTOR) = 0;

	void setLightValue(int newLightValue);
	void incrementLightValue(int increment);

};

