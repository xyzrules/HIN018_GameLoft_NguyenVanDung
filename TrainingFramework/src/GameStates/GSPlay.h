#pragma once
#include "gamestatebase.h"

#define WAVE_DELAY 2.0f // seconds

enum WAVE_TRANSITION {
	TRANSITION_NONE = 0,
	TRANSITION_CLEAR_WAVE,
	TRANSITION_PICK_ITEM,
	TRANSITION_START_WAVE,
};

enum PORTRAIT_POSITION {
	PORTRAIT_P1 = 200,
	PORTRAIT_P2 = 350,
};

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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
	void Gameplay();
	void SortSprite();
	void SpawnPlayer(int playerId, Vector2 playerPos);
	void SpawnEnemy(int enemySpecial, Vector2 enemyPos);
	void SpawnProjectile(int playerChar, int projectileType, Vector2 pos);
	void ProcessCollision(std::shared_ptr<GameCharacter> char1, std::shared_ptr<GameCharacter> char2);
	void ProcessSkill(std::shared_ptr<GameCharPlayer> player);
	void ProcessSkillSprite(std::shared_ptr<GameCharPlayer> player);
	void PlayBackgroundSound();

	// waveTransition
	std::shared_ptr<GLfloat> m_transitionTimer;
	std::shared_ptr<int> m_waveTransition;

	// UI
	std::vector<std::shared_ptr<GameCharPlayer>> m_listPlayer;
	std::vector<std::shared_ptr<GameProjectile>> m_listProjectile;
	std::vector<std::shared_ptr<GameCharEnemy>> m_listEnemy;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::vector<std::shared_ptr<Sprite2D>> m_listPortrait;
	std::vector<std::shared_ptr<Sprite2D>> m_listIcon;
	std::vector<std::shared_ptr<Text>> m_listCooldownCounter;
	std::shared_ptr<Text>  m_ancient;
	std::shared_ptr<Text>  m_score;

	// Transition start wave
	std::shared_ptr<Text>  m_transitionScore;

	// Transition clear wave
	std::shared_ptr<Text>  m_transitionClear;

	// Transition pick items
	std::shared_ptr<SoLoud::WavStream> m_BGSound;
	std::shared_ptr<SoLoud::WavStream> m_pickItemsSound;
	std::shared_ptr<SoLoud::Wav> m_cmSound, m_liSound, m_wrSound, m_drSound;
};

