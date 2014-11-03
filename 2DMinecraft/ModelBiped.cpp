#include "ModelBiped.h"
#include <math.h>


ModelBiped::ModelBiped()
	: headRef(rightHead),
	torsoRef(leftTorso),
	totalFrames(20),
	increment( 160 / totalFrames),
	limit(58 * PI / 180),
	totalFramesHitting(20),
	incrementHitting( 20 / totalFramesHitting),
	limitHitting(3)
{
	//rightHead
	rightHead.textureX = 0;
	rightHead.textureY = 8;
	rightHead.width = 8;
	rightHead.height = 8;
	rightHead.pivotX = 3;
	rightHead.pivotY = 8;
	rightHead.rotation = 0;

	//leftHead
	leftHead.textureX = 16;
	leftHead.textureY = 8;
	leftHead.width = 8;
	leftHead.height = 8;
	leftHead.pivotX = 5;
	leftHead.pivotY = 8;
	leftHead.rotation = 0;

	//foreleg
	foreLeg.textureX = 4;
	foreLeg.textureY = 20;
	foreLeg.height = 12;
	foreLeg.width = 4;
	foreLeg.pivotX = 2;
	foreLeg.pivotY = 2;
	foreLeg.rotation = 0;

	//backLeg
	backLeg.textureX = 0;
	backLeg.textureY = 20;
	backLeg.width = 4;
	backLeg.height = 12;
	backLeg.pivotX = 2;
	backLeg.pivotY = 2;
	backLeg.rotation = 0;

	//leftTorso
	leftTorso.textureX = 16;
	leftTorso.textureY = 20;
	leftTorso.width = 4;
	leftTorso.height = 12;
	leftTorso.rotation = 0;
	
	//rightTorso
	rightTorso.textureX = 28;
	rightTorso.textureY = 20;
	rightTorso.width = 4;
	rightTorso.height = 12;
	rightTorso.rotation = 0;

	//foreArm
	foreArm.textureX = 40;
	foreArm.textureY = 20;
	foreArm.width = 4;
	foreArm.height = 12;
	foreArm.pivotX = 2;
	foreArm.pivotY = 2;
	foreArm.rotation = 0;

	//backArm 
	backArm.textureX = 48;
	backArm.textureY = 20;
	backArm.width = 4;
	backArm.height = 12;
	backArm.pivotX = 2;
	backArm.pivotY = 2;
	backArm.rotation = 0;

	//start in right direction

	headRef = rightHead;
	torsoRef = rightTorso;
}


ModelBiped::~ModelBiped(void)
{

}


void ModelBiped::animateWalkRight(int &frame)
{
	if (first)
	{
		foreArm.rotation += increment * PI / 180;
		backArm.rotation -= increment * PI / 180;
		foreLeg.rotation += increment * PI / 180;
		backLeg.rotation -= increment * PI / 180;
		if (foreArm.rotation > limit)
		{
			first = false;
		}
	}
	if (!first)
	{
		foreArm.rotation -= increment * PI / 180;
		backArm.rotation += increment * PI / 180;
		foreLeg.rotation -= increment * PI / 180;
		backLeg.rotation += increment * PI / 180;
		if (foreArm.rotation < -limit)
		{
			first = true;
		}
	}


	frame++;
	if (frame > totalFrames) frame = 0;
}

void ModelBiped::animateWalkLeft(int frame)
{
	
}

void ModelBiped::animateClimbing(int frame)
{

}

void ModelBiped::animateDigging(int frame)
{
	/*

	*/
}

void ModelBiped::animateStanding(int &frame)
{
		foreLeg.rotation = 0;
		backLeg.rotation = 0;
		foreArm.rotation = 0;
		backArm.rotation = 0;
}

void ModelBiped::draw(LPDIRECT3DTEXTURE9 &texture, int x, int y, float scaling, D3DCOLOR color)
{
	int headX = 4 * scaling;
	int torsoX = 6 * scaling;
	int torsoY = 8 * scaling;
	int armX = 6 * scaling;
	int armY = 8 * scaling;
	int legX = 6 * scaling;
	int legY = 18 * scaling;

	//head
	Sprite_Transform_Draw_Pivot(texture, x + headX, y, headRef.width, headRef.height, headRef.pivotX, headRef.pivotY, headRef.rotation, scaling, color);
	//backArm
	Sprite_Transform_Draw_Pivot(texture, x + armX, y + armY, backArm.width, backArm.height, backArm.pivotX, backArm.pivotY, backArm.rotation, scaling, color);
	//backLeg
	Sprite_Transform_Draw_Pivot(texture, x + legX, y + legY, backLeg.width, backLeg.height, backLeg.pivotX, backLeg.pivotY, backLeg.rotation, scaling, color);
	//torso
	Sprite_Transform_Draw_Pivot(texture, x + torsoX, y + torsoY, torsoRef.width, torsoRef.height, torsoRef.pivotX, torsoRef.pivotY, torsoRef.rotation, scaling, color);
	//foreArm
	Sprite_Transform_Draw_Pivot(texture, x + armX, y + armY , foreArm.width, foreArm.height, foreArm.pivotX, foreArm.pivotY, foreArm.rotation, scaling, color);
	//foreLeg
	Sprite_Transform_Draw_Pivot(texture, x + legX, y + legY, foreLeg.width, foreLeg.height, foreLeg.pivotX, foreLeg.pivotY, foreLeg.rotation, scaling, color);

	//Sprite_Transform_Draw_Pivot(texture, 20, 30, 20, 30, 0, 0, 0, 2);
}
