#pragma once

#include "Animation.h"

class BlockHelper
{
public:
	BlockHelper(int terrainIndex, float hardness,
		bool bsolid = true, bool blightsource = false, int animationLength = 0);
	~BlockHelper(void);

	bool breakBlock(LPDIRECT3DTEXTURE9 lpTerrain, int x, int y);
	void renderBlock(LPDIRECT3DTEXTURE9 lpTerrain, int x, int y);

	Animation abreaking;
	Animation arender;

	float hardness;
	bool solid;
	bool lightSource;

	int startX;  //x and y coordinates of Terrain .png
	int startY; 
};

