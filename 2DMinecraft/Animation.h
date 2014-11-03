#pragma once
#include "MyDirectX.h"

class Animation
{
public:
	Animation();
	~Animation(void);
	void animate();
	void draw(LPDIRECT3DTEXTURE9 image,int x, int y, D3DCOLOR color);

	int frame, columns;
	int width, height;
	float scaling, rotation;
	int startframe, endframe;
	int starttime, delay;
	int direction;
	D3DCOLOR color;

	int startX;
	int startY;
};

