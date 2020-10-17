#pragma once
#include <glm/glm.hpp>
#include "Util.h"

// (0) ------- (3)
//  |			|
//  |			|
//  |			|
//  |			|
// (1) ------- (2)

struct Square
{
	Square(int positionX, int positionY, float angle, float sizeSide)
	{
		this->positionX = positionX;
		this->positionY = positionY;
		this->angle = angle + 45*Util::Deg2Rad;
		this->size = sizeSide;
		h = sqrt((size/2)*(size/2) * 2);
		UpdatePosition();
	}
	void SetPositionX(int positionX)
	{
		this->positionX = positionX;
		UpdatePosition();
	}
	void SetPositionY(int positionY)
	{
		this->positionY = positionY;
		UpdatePosition();
	}
	
	void SetAngle(float angle)
	{
		this->angle = angle + 45*Util::Deg2Rad;
		UpdatePosition();
		
	}

	void UpdatePosition()
	{
		Pos[0] = { positionX - h*sin(this->angle), positionY - h*cos(this->angle)};
		Pos[1] = { positionX - h*cos(this->angle), positionY + h*sin(this->angle)};
		Pos[2] = { positionX + h*sin(this->angle), positionY + h*cos(this->angle) };
		Pos[3] = { positionX + h*cos(this->angle), positionY - h*sin(this->angle)};
	}
	void Draw()
	{
		Util::DrawLine(Pos[0], Pos[1], { 1,0,0,1 });
		Util::DrawLine(Pos[1], Pos[2], { 0,0,0,1 });
		Util::DrawLine(Pos[2], Pos[3], { 0,0,0,1 });
		Util::DrawLine(Pos[3], Pos[0], { 0,0,0,1 });
	}
	
	//coordinates in X,Y plane
	glm::vec2 Pos[4];
	
	//variables just to storage values from UI - need to update after.
	float h;
	int positionY;
	int positionX;
	int size;
	float angle;
};
