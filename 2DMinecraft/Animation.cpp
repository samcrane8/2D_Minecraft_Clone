#include "Animation.h"
#include "MyDirectX.h"

Animation::Animation()
{
	frame = 0;
		columns = 1;
		width = height = 0;
		scaling = 1.0f;
		rotation = 0.0f;
		startframe = endframe = 0;
		direction = 1;
		starttime = delay = 0;
		color = D3DCOLOR_XRGB(255, 255, 255);
}


Animation::~Animation(void)
{

}

void Animation::animate()
{
	if ((int)GetTickCount() > starttime + delay)
	{
		starttime = GetTickCount();

		frame += direction;
		if (frame > endframe) frame = startframe;
		if (frame < startframe) frame = endframe;
	}	
}

void Animation::draw(LPDIRECT3DTEXTURE9 image, int x, int y, D3DCOLOR color)
{
	 //create a scale vector
    D3DXVECTOR2 scale( scaling, scaling );

    //create a translate vector
    D3DXVECTOR2 trans( x, y );

    //set center by dividing width and height by two
    D3DXVECTOR2 center( (float)( width * scaling )/2, (float)( height * scaling )/2);

    //create 2D transformation matrix
    D3DXMATRIX mat;

    D3DXMatrixTransformation2D( &mat, NULL, 0, &scale, &center, rotation, &trans );
    
    //tell sprite object to use the transform
    spriteobj->SetTransform( &mat );

    //calculate frame location in source image
    int fx = startX + (frame % columns) * width;
    int fy = startY + (frame / columns) * height;
    RECT srcRect = {fx, fy, fx + width, fy + height};

    //draw the sprite frame
    spriteobj->Draw( image, &srcRect, NULL, NULL, color );
}
