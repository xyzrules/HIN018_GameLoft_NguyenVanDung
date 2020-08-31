#pragma once
#include "GameCharacter.h"
class GameCharPlayer :
	public GameCharacter
{
public:
	GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameCharPlayer();

	void HandleKeyEvent(int key, bool bIsPressed);

	void Update(GLfloat deltaTime);
private:
	GLint m_playerId;
	GLint m_playerCharacter;
};
