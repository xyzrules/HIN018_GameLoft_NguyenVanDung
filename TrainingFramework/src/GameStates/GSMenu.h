#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

enum MENU_BUTTON_POS {
	MENU_BUTTON_POS_PLAY_1 = 150,
	MENU_BUTTON_POS_PLAY_2 = 250,
	MENU_BUTTON_POS_OPTION = 350,
	MENU_BUTTON_POS_CREDITS = 450,
	MENU_BUTTON_POS_EXIT = 550,
};

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround, m_Logo;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<SoLoud::WavStream> m_BGMenuSound;
};

