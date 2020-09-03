#pragma once
#include "GameCharacter.h"
class GameCharPlayer :
	public GameCharacter
{
public:
	GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, GLfloat moveSpeedVertical, GLfloat moveSpeedHorizontal);
	~GameCharPlayer();

	void HandleKeyEvent(int key, bool bIsPressed);

	void Update(GLfloat deltaTime);

	GLint GetPlayerCharacter();
	void SetPlayerCharacter(GLint playerCharacter);

	GLint GetPlayerId();
	void SetPlayerId(GLint playerId);
	
	bool GetPlayerProjectileReady();
	void SetPlayerProjectileReady(bool ready);

private:
	bool m_playerProjectileReady, m_playerAlive;
	GLint m_playerId;
	GLint m_playerCharacter;
	GLfloat m_playerTimer;
};
