#pragma once
#include "block.h"
class BlockStone :
	public Block
{
public:
	BlockStone(int worldIndex);
	~BlockStone(void);

	static BlockHelper blockhelper;

	bool checkSolid() override;
	bool checkLightSource() override;

	void draw(int x, int y, float SCALE_FACTOR) override;
};

