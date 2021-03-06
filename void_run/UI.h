#pragma once
#include "engine.h"
#include "system_renderer.h"
#include "cmp_player.h"
#include "SpecialAbility.h"

class BasePlayerComponent;
class SpecialAbility;

class CombatUI : UIManager {
protected:
	sf::Font font;

	sf::Sprite attackSprite;
	sf::Sprite healSprite;
	sf::Sprite rechargeSprite;
	sf::Sprite runSprite;
	sf::Sprite special1Sprite;
	sf::Sprite special2Sprite;
	sf::Sprite special3Sprite;
	sf::Sprite special4Sprite;
	sf::Texture attackTex;
	sf::Texture special1Tex;
	sf::Texture special2Tex;
	sf::Texture special3Tex;
	sf::Texture special4Tex;
	sf::Texture healTex;
	sf::Texture rechargeTex;
	sf::Texture runTex;
	sf::FloatRect attackBox;
	sf::FloatRect specialBox;
	sf::FloatRect healBox;
	sf::FloatRect rechargeBox;
	sf::FloatRect runBox;
	sf::FloatRect special1Box;
	sf::FloatRect special2Box;
	sf::FloatRect special3Box;
	sf::FloatRect special4Box;
	sf::Text attackControl;
	sf::Text healControl;
	sf::Text rechargeControl;
	sf::Text runControl;
	sf::Text specialControl1;	
	sf::Text specialControl2;
	sf::Text specialControl3;
	sf::Text specialControl4;
	sf::Text attackCost;
	sf::Text healCost;
	sf::Text rechargeCost;
	sf::Text runCost;
	sf::Text specialCost1;
	sf::Text specialCost2;
	sf::Text specialCost3;
	sf::Text specialCost4;

	const int costOffset = 5;

	std::shared_ptr<BasePlayerComponent> player;

	std::shared_ptr<SpecialAbility> sp1;
	std::shared_ptr<SpecialAbility> sp2;
	std::shared_ptr<SpecialAbility> sp3;
	std::shared_ptr<SpecialAbility> sp4;

	TextureManager* texManager;
public:

	void Update(double dt, const sf::Vector2f cursPos);
	void turnUpdate();
	sf::FloatRect& getAttackBox();
	sf::FloatRect& getHealBox();
	sf::FloatRect& getRechargeBox();
	sf::FloatRect& getRunBox();
	sf::FloatRect& getSp1Box();
	sf::FloatRect& getSp2Box();
	sf::FloatRect& getSp3Box();
	sf::FloatRect& getSp4Box();

	bool CheckBoxes(sf::Vector2f curspos);
	void Render();
	void Load(std::shared_ptr<BasePlayerComponent> p);
	
	void UpdateControls();
	void UpdateCosts();
	void addSpecial(std::string texName, std::shared_ptr<SpecialAbility> sp);
	void resetSpecial();
};

class GameUI : UIManager {
protected:
	int APAmount;
	int MaxAP;
	int height;
	//sf::Sprite APContainer;
	//sf::Texture APContainerTex;
	sf::Texture CellTex;
	std::vector<sf::Sprite> cells;

	sf::Texture statUPTex;
	sf::Sprite stat1;
	sf::Sprite stat2;
	sf::Sprite stat3;
	sf::Font font;

	sf::Sprite playerIcon;
	sf::Texture playerIconTex;

	sf::Text RewardsText;
	sf::Text StrengthText;
	sf::Text HealthText;
	sf::Text DexterityText;
	sf::Text GameOverButton;
	sf::Text backToMenu;
	sf::FloatRect GameOverButtonBox;
	sf::FloatRect backToMenuBox;
	sf::FloatRect stat1Box;
	sf::FloatRect stat2Box;
	sf::FloatRect stat3Box;
	std::shared_ptr<BasePlayerComponent> player;

	sf::Sprite background;
	sf::Texture backgroundTex;

	int strengthUp;
	int hpUp;
	int dexUp;

	bool inStatUp;
	sf::Sound sound;
		
public:
	GameUI() = default;
	~GameUI() = default;

	sf::Text descText;
	void Update(double dt, sf::Vector2f cursPos);
	void Render();
	void Load(int maxAP, std::shared_ptr<BasePlayerComponent> p);

	sf::Sprite getNewCell();

	int getAPAmount();
	void useAP(int amount);
	void gainAP(int amount);

	void UpdateDesc(std::string string);
	void UpdateDescPos(sf::Vector2f pos);

	void statUp();
	bool updateStatOptions();

	void playSound(const std::string& name, int volume);
};

class SettingUI : UIManager {
private:
	sf::Text ResButton;
	sf::Text ResChange;
	sf::Text ResText;
	sf::Text MasterText;
	sf::Text MusicText;
	sf::Text FXText;
	sf::Text MasterTextVolume;
	sf::Text MusicTextVolume;
	sf::Text FXTextVolume;
	sf::Text MasterLeft, MasterRight;
	sf::Text MusicLeft, MusicRight;
	sf::Text FXLeft, FXRight;
	sf::Text AttackText;
	sf::Text HealText;
	sf::Text RechargeText;
	sf::Text RunText;
	sf::Text PauseText;
	sf::Text Special1Text;
	sf::Text Special2Text;
	sf::Text Special3Text;
	sf::Text Special4Text;
	sf::Text AttackKeyText;
	sf::Text HealKeyText;
	sf::Text RechargeKeyText;
	sf::Text RunKeyText;
	sf::Text PauseKeyText;
	sf::Text Special1KeyText;
	sf::Text Special2KeyText;
	sf::Text Special3KeyText;
	sf::Text Special4KeyText;
	sf::Text ResetControls;
	sf::Text BackButton;
	sf::Text HowToText;
	sf::Text toMenuText;

	sf::FloatRect ResButtonBox;
	sf::FloatRect MasterLeftBox;
	sf::FloatRect MasterRightBox;
	sf::FloatRect MusicLeftBox;
	sf::FloatRect MusicRightBox;
	sf::FloatRect FXLeftBox;
	sf::FloatRect FXRightBox;
	sf::FloatRect BackBox;
	sf::FloatRect AttackBox;
	sf::FloatRect HealBox;
	sf::FloatRect RechargeBox;
	sf::FloatRect RunBox;
	sf::FloatRect Special1Box;
	sf::FloatRect Special2Box;
	sf::FloatRect Special3Box;
	sf::FloatRect Special4Box;
	sf::FloatRect PauseBox;
	sf::FloatRect ResetBox;
	sf::FloatRect toMenuBox;

	sf::Clock delayClock;
	float delayTime;
	const float delayAmount = 0.5f;
	const float volumeDelayAmount = 0.05f;

	sf::Sound sound;

	bool pause;

public:
	SettingUI() = default;
	~SettingUI() = default;
	void Update(const double& dt, sf::Vector2f cursPos);
	void Render();
	void Load(sf::Font &font, bool p);

	void CheckKeyPress(sf::Text& changeText, sf::FloatRect& box, sf::Keyboard::Key&);
	void UpdateSettings();
	void ResetKeys();
};