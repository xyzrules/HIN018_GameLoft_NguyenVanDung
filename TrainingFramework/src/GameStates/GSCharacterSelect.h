#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

#define CHARACTER_SELECT_DELAY		2.2f

class GSCharacterSelect :
	public GameStateBase
{
public:
	GSCharacterSelect();
	~GSCharacterSelect();

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
	std::shared_ptr<Sprite2D> m_splashLogo;
	std::shared_ptr<float> m_timer;
	std::vector<std::shared_ptr<Sprite2D>> m_listSplash;
	std::vector<std::shared_ptr<AnimationSprite>> m_listAnimation;
	std::vector<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<SoLoud::Wav> m_CharacterSound;
	std::shared_ptr<SoLoud::WavStream> m_BGSound;
};

