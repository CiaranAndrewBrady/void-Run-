#pragma once
#include <iostream>
#include "enemy_boss.h"
#include "Game.h"

BossEnemy::BossEnemy(Entity* p, int health, int strength, int dex, float expReward, int specialMove)
	: BaseEnemyComponent{ p, health, strength, dex, expReward, specialMove } {}

int behaviour; //0: Aggressive. 1: Defensive. 2: Passive. 3: Desperate.

bool slimed; //Boolean and integer to track the boss' slime DoT effect
int slimedCounter;

void BossEnemy::update(double dt)
{
	if (isTurn && isFinishedTurn != true) //Loop to ensure the boss only acts on its turn
	{
	srand(time(0)); //Random number generation to facilitate replayability
	int i = rand() % 5;

	if (slimed == true) //If slimed, take 5 damage, lose 1 dex
	{
		currentEnemy->addStats(0, 0, -1);
		attackEnemy(5, 10000, "HeavyAttack");
		slimedCounter++;
		gameScene.UpdateTextBox("You are hurt\nby the slime!");
	}
	if (slimedCounter >= 4) //Stay slimed for 3 turns
	{
		slimed = false;
		slimedCounter = 0;
	}
	if (turnCounter == 1) //After their first turn, the player cannot escape.
	{
		gameScene.UpdateTextBox("THE ALIEN LORD ROARS!!!");
		gameScene.gameUI.playSound("Roar", 100);
		currentEnemy->setRunChance(0);
	}
	if (_maxHealth * 0.7) //Whilst above 70% of HP, the enemy is most likely to be passive
	{
		i = rand() % 5;
		if (i == 0 || i == 1 || 1 == 2)		{behaviour = 2;} //Passive
		else if (i == 3)					{behaviour = 0;} //Aggressive
		else if (i == 4)					{behaviour = 1;} //Defensive
	}
	else if (currentHealth <= (_maxHealth * 0.7) && currentHealth >= (_maxHealth * 0.4)) //When at 40%-70% of HP, the enemy is most likely to be aggressive
	{
		i = rand() % 5;
		if (i == 0 || i == 1 || 1 == 2)		{behaviour = 0;} //Aggressive
		else if (i == 3)					{behaviour = 1;} //Defensive
		else if (i == 4)					{behaviour = 2;} //Passive
	}
	else if (currentHealth <= (_maxHealth * 0.4) && currentHealth >= (_maxHealth * 0.1)) //When at 40-70% oh HP, the enemy is most likely to be defensive
	{
		i = rand() % 4;
		if (i == 0 || i == 1 || 1 == 2)		{behaviour = 1;} //Defensive
		else if (i == 3)					{behaviour = 0;} //Aggressive
	}
	else //Otherwise (below 10%), the enemy is DESPERATE
	{
		behaviour = 3; //Desperate
	}
	
		int enemyAI = rand() % 4;
		if (behaviour == 0) //Aggressive
		{
			spriteManager->ChangeIcon(0, "Aggressive", "AGGRESSIVE\The Alien Lord is mad at you!");
			if ((currentHealth <= _maxHealth * 0.8 && enemyAI == 0) || ((currentHealth < _maxHealth * 0.4) && enemyAI == 1)) //20% chance below 80%HP, 40% below 40% HP.
			{
				std::cout << "The enemy drains your life! \n"; //Life drain. Deals damage, if successful, gain health.
				gameScene.UpdateTextBox("The Alien Lord absorbs your health!");
				if (attackEnemy(_strength, _dexterity, "HeavyAttack"))
				{
					currentHealth += _strength;
				}
				EndTurn();
			}
			else if ((currentEnemy->getCurrentHealth() >= currentHealth) || enemyAI == 2) //Flat 20% chance, or guaranteed if the player has more HP than the alien
			{
				std::cout << "The enemy attacks twice with a relentless determination! \n"; //Double attack, hits twice with high damage but low accuracy
				gameScene.UpdateTextBox("The Alien Lord attacks twice!");
				attackEnemy(_strength * 1.5, _dexterity - 25, "HeavyAttack");
				attackEnemy(_strength * 1.5, _dexterity - 25, "HeavyAttack");
				EndTurn();
			}
			else if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2) //If neither others happen, 60% chance for a strong attack
			{
				std::cout << "The enemy makes a strong attack! \n"; //Strong attack
				gameScene.UpdateTextBox("The Alien Lord makes a powerful attack!");
				attackEnemy(_strength * 2, _dexterity, "HeavyAttack");
				EndTurn();
			}
			else //If nothing else, medium attack
			{
				std::cout << "The enemy makes a medium attack! \n"; //Medium attack
				gameScene.UpdateTextBox("The Alien Lord attacks you!");
				attackEnemy(_strength + 5, _dexterity, "HeavyAttack");
				EndTurn();
			}
		}
		else if (behaviour == 1) //Defensive
		{
			spriteManager->ChangeIcon(0, "Defensive", "DEFENSIVE\The Alien Lord is conserving resources!");
			if (((currentHealth >= (_maxHealth * 0.8)) && enemyAI == 0) //For every 20% of missing HP, the monster is 20% more likely to heal
				|| ((currentHealth >= (_maxHealth * 0.6)) && ((enemyAI == 0 || enemyAI == 1)))
				|| ((currentHealth >= (_maxHealth * 0.4)) && ((enemyAI == 0 || enemyAI == 1 || enemyAI == 2)))
				|| ((currentHealth >= (_maxHealth * 0.2)) && ((enemyAI == 0 || enemyAI == 1 || enemyAI == 3))))
			{
				std::cout << "The enemy grows stronger, regaining lost health! \n"; //Regains 10% max HP
				gameScene.UpdateTextBox("The Alien Lord heals!");
				currentHealth += (_maxHealth * 0.1);
				EndTurn();
			}
			else if ((_dexterity > currentEnemy->getDexterity()) || (_strength > currentEnemy->getStrength())) //If the PC has better stats, it buffs itself
			{
				std::cout << "The enemy is gaining more power to match your skill!"; //Str + Dex increase
				gameScene.UpdateTextBox("The Alien Lord gains power!");
				_strength += 4;
				_dexterity += 4;
			}
			else if ((currentHealth < currentEnemy->getCurrentHealth()) || (enemyAI == 0 || enemyAI == 1 || enemyAI == 2)) //If the PC has more HP, it'll Life Drain. Otherwise, a 60% chance.
			{
				std::cout << "The enemy makes a drains your life! \n"; //Deals damage and heals for the same amount
				gameScene.UpdateTextBox("The Alien Lord absorbs your health!");
				if (attackEnemy(_strength, _dexterity, "HeavyAttack"))
				{
					currentHealth += _strength;
				}
				EndTurn();
			}
			else //Otherwise, it removes your AP
			{
				std::cout << "The enemy saps your will to fight! \n"; //Takes away 3AP from the player
				gameScene.UpdateTextBox("The Alien Lord drains your AP!");
				currentEnemy->SpendAP(3);
				EndTurn();
			}
		}
		else if (behaviour == 2) //Passive
		{
			spriteManager->ChangeIcon(0, "Passive", "PASSIVE\The Alien Lord is indifferent towards you!");
			int enemyAI = rand() % 6;
			if ((turnCounter % 3 == 1) || enemyAI == 5) //Every 3 turns, starting from turn 1 (1, 4, 7, 10 etc), or a 1/6 chance, it passes its turn
			{
				std::cout << "The enemy sneers at you! \n"; //Skips its turn
				gameScene.UpdateTextBox("The Alien Lord laughs at you.");
				EndTurn();
			}
			else if (enemyAI == 0 || enemyAI == 1 || enemyAI == 2 || (_dexterity < currentEnemy->getDexterity() && enemyAI == 4)) //3/6 chance of attack. 4/6 if the player has higher dexterity
			{
				if (attackEnemy(0, _dexterity + 1, "HeavyAttack"))
				{
					std::cout << "The enemy produces a viscous fluid, flinging it over you!"; //Damage over time and dex damage effect
					gameScene.UpdateTextBox("The Alien Lord spits\ngoo on you!");
					slimed = true;
				}
				else
				{
					std::cout << "The enemy throws slime at you, but you sidestep it!"; //If the attack returns false, it misses
					gameScene.UpdateTextBox("The Alien Lord fails\nto spit goo on you.");
				}
				EndTurn();
			}
			else if ((currentHealth >= (_maxHealth * 0.65)) && enemyAI == 6) //Otherwise, if it has below 65%HP, there's a 1/6 chance it heals
			{
				std::cout << "The enemy grows stronger, gathering energy! \n"; //Regains 10% HP
				gameScene.UpdateTextBox("The Alien Lord grows stronger!");
				currentHealth += (_maxHealth * 0.1);
				EndTurn();
			}
			else //Otherwise, normal attack
			{
				std::cout << "The enemy makes a medium attack! \n"; //Normal attack
				gameScene.UpdateTextBox("The Alien Lords attacks you.");
				attackEnemy(_strength + 5, _dexterity, "HeavyAttack");
				EndTurn();
			}
		}
		else if (behaviour == 3) //Desperate
		{
			spriteManager->ChangeIcon(0, "Desperate", "DESPERATE\The Alien Lord is desperate to kill you! Finish it now!");
			if (turnCounter % 4 == 0) //Turns in the 4 times table provoke a massive buff to stats
			{
				std::cout << "The enemy is harnessing a massive amount of energy!"; //Large stat increase
				gameScene.UpdateTextBox("The Alien Lord gathers energy!");
				_strength += 8;
				_dexterity += 8;
			}
			else //Otherwise, it just makes constant deadly attacks
			{
				std::cout << "The enemy attacks twice with a relentless determination! \n";
				gameScene.UpdateTextBox("The Alien Lord attacks desperately!");
				attackEnemy(_strength * 1.5, _dexterity - 20, "HeavyAttack");
				attackEnemy(_strength * 1.5, _dexterity - 20, "HeavyAttack");

				EndTurn();
			}
		}
	}
	BaseEnemyComponent::update(dt);
}

void BossEnemy::load()
{
	auto sm = _parent->GetCompatibleComponent<SpriteComponent>(); //Play component
	spriteManager = sm[0];

	spriteManager->AddIcon("Passive", "PASSIVE\The Alien Lord is indifferent towards you!", true); //Alien Lord starts Indifferent

	BaseEnemyComponent::load();

}

void BossEnemy::render()
{
	BaseEnemyComponent::render(); //Renders enemy code
}