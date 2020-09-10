#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

enum MENU_BUTTON_POS {
	MENU_BUTTON_POS_PLAY_1 = 200,
	MENU_BUTTON_POS_PLAY_2 = 300,
	MENU_BUTTON_POS_OPTION = 400,
	MENU_BUTTON_POS_CREDITS = 500,
	MENU_BUTTON_POS_EXIT = 600,
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
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameName;
};

