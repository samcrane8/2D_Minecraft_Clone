#pragma once

#include "Animation.h"
#include "MyDirectX.h"

class ModelBiped
{
public:
	ModelBiped();
	~ModelBiped(void);
	
	SPRITE foreArm;
	SPRITE backArm;

	SPRITE &headRef;
			SPRITE rightHead;
			SPRITE leftHead;
	SPRITE &torsoRef;
		SPRITE leftTorso;
		SPRITE rightTorso;
	SPRITE foreLeg;
	SPRITE backLeg;

	int totalFrames;
	int increment;
	int limit;

	int totalFramesHitting;
	int incrementHitting;
	int limitHitting;

	bool first; //checks if loop is in first phase".
	bool knocked; //checks if it has "knocked" the block yet. for digging animation

	bool left; //walking
	bool right; //walking
	bool climbing;
	bool digging; //no two of left, right and climbing can both be true, but digging can.

	void animateStanding(int &frame);
	void animateWalkRight(int &frame);
	void animateWalkLeft(int frame);
	void animateClimbing(int frame); //back turned to camera.
	void animateDigging(int frame);
	void draw(LPDIRECT3DTEXTURE9 &texture, int x, int y,
		float scaling, D3DCOLOR color );
};

//this will create a biped "model", or group of textures that make a biped.

//most important thing is to define the pivot points, and degrees of motion.
