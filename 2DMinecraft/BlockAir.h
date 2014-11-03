#pragma once
#include "Block.h"
#include "BlockHelper.h"
class BlockAir :
	public Block
{
public:
	BlockAir(int worldIndex);
	~BlockAir(void);

	bool checkSolid();
	bool checkLightSource();

	void draw(int x, int y, float SCALE_FACTOR) override;

	static BlockHelper blockhelper;
};

