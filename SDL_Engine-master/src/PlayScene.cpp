#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"


PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0.0f, 0.0f);
	

	drawDisplayList();
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	
	//reset render color back to white
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	//draw ramp
	//SDL_RenderSetScale(Renderer::Instance()->getRenderer(), 3.0f,3.0f);
	ramp->Draw();

	square->Draw();
	
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	//background
	TextureManager::Instance()->load("../Assets/sprites/backgroundA2.png", "background");
	
	// Set GUI Title
	m_guiTitle = "Play Scene";

	

	//ramp initial data
	//position, width, height
	ramp = new Ramp(400,100,100);

	int sizeSquare = 50;
	int h = sizeSquare/2 + 1;
	//int h = sqrt((sizeSquare/2)*(sizeSquare/2) * 2);
	int nPosX = ramp->getPosition().x + h*cos(ramp->GetAngle()); 
	int nPosY = ramp->getPosition().y - h*sin(ramp->GetAngle()); 
	square = new Square(nPosX,nPosY,ramp->GetAngle(),sizeSquare);
	
	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 585.0f);

	addChild(m_pInstructionsLabel);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Physics Simulation Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Throw"))
	{
		std::cout << "Simulation started - button pressed" << std::endl;
	}

	ImGui::Separator();

	
	//ramp position
	ImGui::SliderInt("Ramp Position", &ramp->position,5,795);
	ramp->SetPosition(ramp->position);
	
	//ramp width
	ImGui::SliderInt("Ramp Width", &ramp->width, 20, 500);
	ramp->SetWidth(ramp->width);

	//ramp height
	ImGui::SliderInt("Ramp Height", &ramp->height, 20, 300);
	ramp->SetHeight(ramp->height);

	int sizeSquare = 50;
	int h = sizeSquare/2 + 1;

	square->SetPositionX(ramp->getPosition().x + h*cos(ramp->GetAngle()));
	square->SetPositionY(ramp->getPosition().y - h*sin(ramp->GetAngle()));
	square->SetAngle(ramp->GetAngle());
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
