#pragma once
#include <glm/glm.hpp>
#include "Util.h"

// (0) ------- (3)
//  |			|
//  |			|
//  |			|
//  |			|
// (1) ------- (2)

enum class StateSquare
{
	NONE = 0,
	FALLING,
	PLAINING
};
struct Square
{
	Square(glm::vec2 position, float angle, float sizeSide)
	{
		this->distancePlanning = 0.0f;
		this->startSimulation = false;
		this->friction = 0.42f;
		this->mass = 12.8f;
		this->acceleration = {0,0};
		this->velocity = {0,0};
		this->position = position;
		this->angle = angle + 45*Util::Deg2Rad;
		this->size = sizeSide;
		currentState = StateSquare::NONE;
		h = sqrt((size/2)*(size/2) * 2);
		UpdatePosition();
	}
	glm::vec2 getPosition() const
	{
		return position;
	}

	void SetPosition(glm::vec2 pos)
	{
		this->position = pos;
		UpdatePosition();
	}
	
	void SetAngle(float angle)
	{
		this->angle = angle + 45*Util::Deg2Rad;
		UpdatePosition();
		
	}

	void UpdatePosition()
	{
		Pos[0] = { position.x - h*sin(this->angle), position.y - h*cos(this->angle)};
		Pos[1] = { position.x - h*cos(this->angle), position.y + h*sin(this->angle)};
		Pos[2] = { position.x + h*sin(this->angle), position.y + h*cos(this->angle) };
		Pos[3] = { position.x + h*cos(this->angle), position.y - h*sin(this->angle)};
	}
	void Draw()
	{
		Util::DrawLine(Pos[0], Pos[1], { 0,0,0,1 });
		Util::DrawLine(Pos[1], Pos[2], { 0,0,0,1 });
		Util::DrawLine(Pos[2], Pos[3], { 0,0,0,1 });
		Util::DrawLine(Pos[3], Pos[0], { 0,0,0,1 });
	}

	void Falling()
	{
		//define deltatime
		float tempAngle = angle - 45*Util::Deg2Rad;
		const float deltaTime = 1.0f / 60.f;
		acceleration = {cos(tempAngle)*9.81*sin(tempAngle),cos(tempAngle)*9.81*cos(tempAngle)};
		velocity += acceleration*deltaTime;
		position += velocity*deltaTime;

		UpdatePosition();
		 
	}
	void InitPlanning()
	{
			
			float NormalForce = mass*9.81;
			float FrictionForce = friction*NormalForce;
			acceleration.x = -FrictionForce/mass;
			acceleration.y = 0;
			SetAngle(0); //now is horizontal
			float initialSpeed = Util::magnitude(velocity);
			std::cout << "Initial Speed for planning: " << initialSpeed << std::endl;
			velocity = {initialSpeed,0};
	}
	void Plaining()
	{
		//define deltatime
		const float deltaTime = 1.0f / 60.f;
		velocity += acceleration*deltaTime;
		position += velocity*deltaTime;
		distancePlanning += velocity.x*deltaTime;
		UpdatePosition();
		if(velocity.x <= 0)
		{
			setState(StateSquare::NONE);
		}

	}
	void setVelocity(glm::vec2 vel)
	{
		velocity = vel;
	}
	bool getStartSimulation() const
	{
		return startSimulation;
	}
	void setStartSimulation(bool value)
	{
		startSimulation = value;
	}
	glm::vec2 getForce() 
	{
		force = mass*acceleration;
		return force;
	}
	void Update()
	{
		switch (currentState)
		{
			case StateSquare::NONE:
				velocity = {0,0};
				acceleration = {0,0};
			break;
		case StateSquare::FALLING:
			Falling();
			break;
		case StateSquare::PLAINING:
			Plaining();
			break;
		default:
				break;
		}
	}
	StateSquare getState()
	{
		return currentState;
	}
	void setState(StateSquare state)
	{
		currentState = state;
		switch (currentState)
		{
		case StateSquare::NONE:
			break;
		case StateSquare::FALLING:
			break;
		case StateSquare::PLAINING:
			InitPlanning();
			break;
		default:
				break;
		}
	}
	//coordinates in X,Y plane
	glm::vec2 Pos[4];

	float mass;
	float friction;

	float distancePlanning;
	StateSquare currentState;
	bool startSimulation;
	//variables just to storage values from UI - need to update after.
	float h;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::vec2 force;
	int size;
	float angle;
};
