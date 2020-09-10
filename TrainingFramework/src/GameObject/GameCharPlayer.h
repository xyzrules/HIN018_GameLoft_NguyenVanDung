#pragma once
#include "GameCharacter.h"

class GameCharPlayer :
	public GameCharacter
{
public:
	GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharPlayer();

	void HandleKeyEvent(int key, bool bIsPressed);

	void Update(GLfloat deltaTime);

	GLint GetPlayerId();
	void SetPlayerId(GLint playerId);

	GLint GetPlayerChar();

	bool GetPlayerProjectileReady();
	void SetPlayerProjectileReady(bool ready);

	bool GetPlayerSkillReady();
	void SetPlayerSkillReady(bool ready);

	void ActivateSkill();

protected:
	GLint m_playerId, m_playerChar;
	bool m_playerProjectileReady, m_playerSkillReady;
	GLfloat m_playerAttackTimer, m_playerSkillTimer, m_playerDeathTimer;
	GLfloat m_playerAttackSpeedMultiplyer, m_playerMovementSpeedMultiplyer;
};
