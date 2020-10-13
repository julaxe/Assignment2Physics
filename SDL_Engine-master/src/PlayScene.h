#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
struct Ramp
{
	Ramp(int position, int width, int height)
	{
		positionY = 480; //just for this example is always this value
		this->position = position;
		this->width = width;
		this->height = height;
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
	void SetWidth(int width)
	{
		this->width = width;
		Pos[2].x = Pos[1].x + width;
	}
	void SetHeight(int height)
	{
		this->height = height;
		Pos[0].y = Pos[1].y - height;
	}
	
	//coordinates in X,Y plane
	glm::vec2 Pos[3];
	
	//variables just to storage values from UI - need to update after.
	int positionY;
	int position;
	int width;
	int height;
};

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	bool m_playerFacingRight;

	//ramp data -  clockwise starting with top point (high)
	Ramp* ramp;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__PLAY_SCENE__) */