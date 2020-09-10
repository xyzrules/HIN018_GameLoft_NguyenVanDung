#pragma once

#include "GameCharPlayer.h"

class GameCharLina : public GameCharPlayer {
public:
	GameCharLina(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharLina();

private:

};
