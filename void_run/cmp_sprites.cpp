#include "cmp_sprites.h"
#include "system_renderer.h"

sf::Clock animClock;
float animDelay;
int animCounter;
int animRowCounter;

SpriteComponent::SpriteComponent(Entity* p) 
	: Component(p) {}

void SpriteComponent::load()
{
	animCounter = 0;
	animRowCounter = 0;
}

void SpriteComponent::render()
{
	Renderer::queue(&sprite);
}

void SpriteComponent::update(double dt)
{
	if (inAttack)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay)
		{
			if (animCounter < attackSpriteNum)
			{
				if (animRowCounter <= 3)
				{
					if (animRowCounter == 3)
					{
						sheetRect.top += attackSize.y;
						sheetRect.left = 0;
						animRowCounter = 0;
					}
					else
					{
						sheetRect.left += attackSize.x;
						animRowCounter++;
					}
				}
				sprite.setTextureRect(sheetRect);
				animClock.restart();
				animCounter++;
			}
			else
			{
				ResetAnim();
			}
		}
	}
	if (inHit)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay)
		{
			if (animCounter < hitSpriteNum)
			{
				if (animRowCounter <= 3)
				{
					if (animRowCounter == 3)
					{
						sheetRect.top += hitSize.y;
						sheetRect.left = 0;
						animRowCounter = 0;
					}
					else
					{
						sheetRect.left += hitSize.x;
						animRowCounter++;
					}
				}
				sprite.setTextureRect(sheetRect);
				animClock.restart();
				animCounter++;
			}
			else
			{
				ResetAnim();
			}
		}
	}
	if (inDie)
	{
		if (animClock.getElapsedTime().asSeconds() > animDelay)
		{
			if (animCounter < dieSpriteNum)
			{
				if (animRowCounter <= 3)
				{
					if (animRowCounter == 3)
					{
						sheetRect.top += dieSize.y;
						sheetRect.left = 0;
						animRowCounter = 0;
					}
					else
					{
						sheetRect.left += dieSize.x;
						animRowCounter++;
					}
				}
				sprite.setTextureRect(sheetRect);
				animClock.restart();
				animCounter++;
			}
			else
			{
			//	ResetAnim();
			}
		}
	}
}

void SpriteComponent::playAttack()
{
	inAttack = true;
	animDelay = 0.05f;
}

void SpriteComponent::playHit()
{
	inHit = true;
	sheetRect = sf::IntRect(0, 0, 310, 447);
	sprite = sf::Sprite(hitSheet, sheetRect);

	sprite.setScale(-1.0f, 1.0f);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);
	animDelay = 0.05f;
}

void SpriteComponent::playDie()
{
	inDie = true;

	//auto tempSprite = sprite.getPosition().x; //+ (sprite.getGlobalBounds().width / 2);
	sheetRect = sf::IntRect(0, 0, 320, 516);
	sprite = sf::Sprite(dieSheet, sheetRect);

	sprite.setScale(-1.0f, 1.0f);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);
	animDelay = 0.05f;
}

void SpriteComponent::ResetAnim()
{
	inAttack = false;
	inHit = false;
	inDie = false;
	sheetRect = sf::IntRect(0, 0, 460, 411);
	sprite = sf::Sprite(attackSheet, sheetRect);
	animRowCounter = 0;
	animCounter = 0;

	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0.0f));
	sprite.setPosition(defaultPos);
	sprite.setScale(-1.0f, 1.0f);
}
