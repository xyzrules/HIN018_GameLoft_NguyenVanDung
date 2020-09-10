#include "GameCharLina.h"

GameCharLina::GameCharLina(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharPlayer(model, shader, texture, numFrames, frameTime)
{
	m_spriteName = "sprite_lina";
	m_playerChar = CHAR_LI;
}

GameCharLina::~GameCharLina()
{
}
