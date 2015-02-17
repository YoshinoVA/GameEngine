#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "soil/soil.h"

struct vertex
{
	float PosX, PosY;
	float Rd, Gn, Bl, Al;
	float UVx, UVy, UVz, UVw;
};

class Sprite
{
	public:
		Sprite(const char* a_file, int a_BPP);
		~Sprite();
		vertex vertices[4];
		int spriteID;
		unsigned int loadTexture(const char* a_file, int & a_width, int & a_height, int & a_BPP);
		void Draw();
		void Update(float a_DeltaTime);

		void setUVdata();
};

#endif