#include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSMenu::GSMenu()
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//1 player button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play_1p");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, MENU_BUTTON_POS_PLAY_1);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameManager::GetInstance()->SetNumberOfPlayers(1);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_CharacterSelect);
		});
	m_listButton.push_back(button);

	//2 players button
	// fix
	/*
	texture = ResourceManagers::GetInstance()->GetTexture("button_play_2p");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, MENU_BUTTON_POS_PLAY_2);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameManager::GetInstance()->SetNumberOfPlayers(2);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_CharacterSelect);
		});
	m_listButton.push_back(button);
	*/
	//option button
	texture = ResourceManagers::GetInstance()->GetTexture("button_option");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, MENU_BUTTON_POS_OPTION);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Option);
		});
	m_listButton.push_back(button);

	//credits button
	texture = ResourceManagers::GetInstance()->GetTexture("button_credits");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, MENU_BUTTON_POS_CREDITS);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Credits);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, MENU_BUTTON_POS_EXIT);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SAMPLE NAME", TEXT_COLOR::GREEN, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
