#pragma once
#include "gamestatebase.h"

class GSInGamePause :
	public GameStateBase
{
public:
	GSInGamePause();
	~GSInGamePause();

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
};

