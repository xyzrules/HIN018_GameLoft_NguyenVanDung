#pragma once
#include "AnimationSprite.h"
#include "GameManager.h"

enum CHAR_MOVE_DIRECTION {
	CHAR_MOVE_DIRECTION_UP		=	1 << 0,
	CHAR_MOVE_DIRECTION_DOWN	=	1 << 1,
	CHAR_MOVE_DIRECTION_LEFT	=	1 << 2,
	CHAR_MOVE_DIRECTION_RIGHT	=	1 << 3,
};

class GameCharacter :
	public AnimationSprite
{
public:
	GameCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharacter();

	// Move
	virtual void SetMoveDirection();

	// Hitbox
	GLfloat GetHitboxVertical();
	GLfloat GetHitboxHorizontal();
	
	// Health & Damage
	void TakeDamage(GLfloat damage);
	GLfloat GetDamagePoint();
	bool GetCharacterAlive();

	// Other
	std::string GetSprite();
	void Update(GLfloat deltaTime);
	


protected:
	bool m_characterAlive;
	GLint m_moveDirection;
	GLfloat m_healthPoints, m_damagePoints;
	GLfloat m_moveSpeedVertical, m_moveSpeedHorizontal;
	GLfloat m_hitboxVertical, m_hitboxHorizontal;
	std::string m_spriteName;

};