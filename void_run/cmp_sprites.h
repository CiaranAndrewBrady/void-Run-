#pragma once
#include "ecm.h"

class SpriteComponent : public Component {
protected:
	sf::Sprite sprite;
	sf::Texture attackSheet;
	sf::Texture hitSheet;
	sf::Texture dieSheet;

	std::string attackName;
	std::string hitName;
	std::string dieName;

	sf::Vector2f attackSize;
	sf::Vector2f hitSize;
	sf::Vector2f dieSize;

	sf::IntRect sheetRect;

	sf::Vector2f defaultPos;

	int attackSpriteNum;
	int hitSpriteNum;
	int dieSpriteNum;

	bool inAttack;
	bool inHit;
	bool inDie;
public:
	SpriteComponent() = delete;
	explicit SpriteComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	void load();

	virtual void playAttack();
	virtual void playHit();
	virtual void playDie();
	virtual void ResetAnim();

};