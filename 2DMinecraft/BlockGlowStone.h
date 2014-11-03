#pragma once
#include "block.h"
class BlockGlowStone :
	public Block
{
public:
	BlockGlowStone(int worldIndex);
	~BlockGlowStone(void);

	static BlockHelper blockhelper;

	bool checkSolid() override;
	bool checkLightSource() override;

	void draw(int x, int y, float SCALE_FACTOR) override;
};

