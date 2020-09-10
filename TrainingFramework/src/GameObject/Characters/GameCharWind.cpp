#include "GameCharWind.h"

GameCharWind::GameCharWind(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharPlayer(model, shader, texture, numFrames, frameTime)
{
	m_spriteName = "sprite_wind";
	m_playerChar = CHAR_WR;
}

GameCharWind::~GameCharWind()
{
}
