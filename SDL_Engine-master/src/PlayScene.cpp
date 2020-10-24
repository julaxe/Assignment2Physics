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
	ramp->Draw();

	square->Draw();
	
}

void PlayScene::update()
{
	updateDisplayList();
	
	int sizeSquare = 50;
	int h = sizeSquare/2 + 1;
	if(square->getStartSimulation())
	{
		square->Update();
		if(square->position.x - h*cos(ramp->GetAngle()) > ramp->position + ramp->width 
			&& square->getState()== StateSquare::FALLING)
		{
			square->setState(StateSquare::PLAINING);
		}
	}
	
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

	//start variables
	m_StartSimulation = new bool(false);

	//ramp initial data
	//position, width, height
	ramp = new Ramp(400,100,100);

	int sizeSquare = 50;
	int h = sizeSquare/2 + 1;
	//int h = sqrt((sizeSquare/2)*(sizeSquare/2) * 2);
	int nPosX = ramp->getPosition().x + h*cos(ramp->GetAngle()); 
	int nPosY = ramp->getPosition().y - h*sin(ramp->GetAngle()); 
	square = new Square(glm::vec2(nPosX,nPosY),ramp->GetAngle(),sizeSquare);
	
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

	ImGui::Text("1 pixel is 1 meter");
	if(ImGui::Button("Start Simulation"))
	{
		std::cout << "Simulation started - button pressed" << std::endl;
		square->setStartSimulation(true);
		square->setState(StateSquare::FALLING);
	}

	if(ImGui::Button("Reset"))
	{
		std::cout << "Simulation reseted - button pressed" << std::endl;
		square->setStartSimulation(false);
		square->setVelocity(glm::vec2(0,0));
		square->setState(StateSquare::NONE);
	}

	ImGui::Separator();

	ImGui::SliderFloat("= Mass (kg)", &square->mass, 1.f,200.f);
	ImGui::SliderFloat("= Friction", &square->friction,0.0f,1.0f);
	
	ImGui::Separator();
	
	ImGui::LabelText("Planning Distance (m)", std::to_string(square->distancePlanning).c_str());

	ImGui::LabelText("Position Box X (m)", std::to_string(square->getPosition().x).c_str());
	ImGui::LabelText("Position Box Y (m)", std::to_string(square->getPosition().y).c_str());
	ImGui::LabelText("Velocity Box X (m/s)", std::to_string(square->velocity.x).c_str());
	ImGui::LabelText("Velocity Box Y (m/s)", std::to_string(square->velocity.y).c_str());
	ImGui::LabelText("Acceleration Box X (m/s^2)", std::to_string(square->acceleration.x).c_str());
	ImGui::LabelText("Acceleration Box Y (m/s^2)", std::to_string(square->acceleration.y).c_str());
	ImGui::LabelText("Force Box X (N)", std::to_string(square->getForce().x).c_str());
	ImGui::LabelText("Force Box Y (N)", std::to_string(square->getForce().y).c_str());
	
	//ImGui::TextUnformatted("%f", ramp->height);
	//ramp position
	ImGui::Separator();
	
	ImGui::InputInt("Ramp Position (m)", &ramp->position,5,795);
	
	
	//ramp width
	ImGui::InputInt("Ramp Width (m)", &ramp->width, 10, 500);
	

	//ramp height
	ImGui::InputInt("Ramp Height (m)", &ramp->height, 10, 300);
	

	int sizeSquare = 50;
	int h = sizeSquare/2 + 1;

	//Update the position of the square relative to the ramp
	if(!square->getStartSimulation())
	{
		ramp->SetPosition(ramp->position);
		ramp->SetWidth(ramp->width);
		ramp->SetHeight(ramp->height);
		square->SetPosition(glm::vec2(ramp->getPosition().x + h*cos(ramp->GetAngle()),
			ramp->getPosition().y - h*sin(ramp->GetAngle())));
		
		square->SetAngle(ramp->GetAngle());
	}
	
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
