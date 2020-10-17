
#pragma once
#include <glm/glm.hpp>
#include "Util.h"

struct Ramp
{
	Ramp(int position, int width, int height)
	{
		positionY = 480; //just for this example is always this value
		this->position = position;
		this->width = width;
		this->height = height;
		angle = atan2(width,height);
		Pos[0] = { position, positionY - height };
		Pos[1] = { position, positionY };
		Pos[2] = { position + width, positionY };
	}
	void SetPosition(int position)
	{
		this->position = position;
		Pos[0].x = position;
		Pos[1].x = position;
		Pos[2].x = position + width;
	}
	glm::vec2 getPosition()
	{
		glm::vec2 nposition = {position, positionY- height};
		return nposition;
	}
	void SetWidth(int width)
	{
		this->width = width;
		angle = atan2(width,height);
		Pos[2].x = Pos[1].x + width;
	}
	void SetHeight(int height)
	{
		this->height = height;
		angle = atan2(width,height);
		Pos[0].y = Pos[1].y - height;
	}

	float GetAngle()
	{
		return angle;
	}
	void Draw()
	{
		Util::DrawLine(Pos[0], Pos[1], { 0,0,0,1 });
		Util::DrawLine(Pos[1], Pos[2], { 0,0,0,1 });
		Util::DrawLine(Pos[2], Pos[0], { 0,0,0,1 });
	}
	
	//coordinates in X,Y plane
	glm::vec2 Pos[3];
	
	//variables just to storage values from UI - need to update after.
	float angle;
	int positionY;
	int position;
	int width;
	int height;
};