#pragma once
#include "GameCharacter.h"

class GameCharPlayer :
	public GameCharacter
{
public:
	GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId);
	~GameCharPlayer();

	void HandleKeyEvent(int key, bool bIsPressed);

	void Update(GLfloat deltaTime);
	
	// Player 1 or 2
	GLint GetPlayerId();
	void SetPlayerId(GLint playerId);

	// Player character
	GLint GetPlayerChar();

	// Player fire projectile
	bool GetPlayerProjectileReady();
	void SetPlayerProjectileReady(bool ready);

	// Skill off cooldown or not
	bool GetPlayerSkillReady();

	// Skill cooldown
	GLfloat GetPlayerSkillTimer();

	// For passive skill with cooldown
	bool GetPlayerSkillEnded();

	// Skill activation
	bool GetPlayerSkillActivated();

	

protected:
	virtual void ActivateSkill() = 0;

	GLint m_playerId, m_playerChar;
	bool m_playerProjectileReady, m_playerSkillReady, m_playerSkillActivated, m_playerSkillEnded;
	GLfloat m_playerAttackTimer, m_playerSkillTimer, m_playerDeathTimer, m_playerSkillDurationTimer;
	GLfloat m_playerAttackSpeedMultiplyer, m_playerMovementSpeedMultiplyer;
};
