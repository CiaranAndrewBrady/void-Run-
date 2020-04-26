#include "ItemDB.h"
#include <iterator>

//Function that adds items to a common, and rare vector
void ItemDB::PopulateDB()
{
	//Common Items
	commonItems["BlasterUpgrade"] = Item(5, 5, 0, "BlasterUpgrade", "Blaster Upgrade", "Pointy");
	commonItems["ExtraPadding"] = Item(0, 10, 0, "ExtraPadding", "Extra Padding", "ExtraPadding");
	commonItems["Stimulant"] = Item(0, 5, 5, "Stimulant", "Stimulant", "Stimulant");

	//Rare Items
	rareItems["PrecisionWatch"] = Item(15, 0, 0, "PrecisionWatch", "Precision Watch", "SpaceWatch");
	rareItems["WristGuard"] = Item(0, 30, 0, "WristGuard", "Wrist Guard", "WristGuard");
	rareItems["Mask"] = Item(0, 0, 15, "Mask", "Mask", "FaceMask");

	auto lb = std::make_shared<LaserBurst>();
	lb->load();
	specialItems["*TargetingDevice"] =
		SpecialItem(5, 50, 5, "*TargetingDevice", "Targeting Device", "SpaceWatch", lb);
}

//Gets a random common item from list
std::shared_ptr<Item> ItemDB::randomCommonItem()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(0, commonItems.size() - 1); 

	int randValue = distributionInteger(generator);
	//std::cout << "Random Item is: " << commonItems[randValue].description << "\n";
	//std::shared_ptr<Item> randItem = std::make_shared<Item>(commonItems[randValue]);

	std::map<std::string, Item>::iterator it = commonItems.begin();
	std::advance(it, randValue);
	std::shared_ptr<Item> randItem = std::make_shared<Item>(it->second);
	return randItem;
}
//Gets a random item from list
std::shared_ptr<Item> ItemDB::randomRareItem()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(0, rareItems.size() - 1);
	//gets random value from 0 to vector size
	int randValue = distributionInteger(generator);
	//what item is
	//std::cout << "Random Item is: " << rareItems[randValue].description << "\n";
	//makes a shared pointer
//	std::shared_ptr<Item> randItem = std::make_shared<Item>(rareItems[randValue]);

	std::map<std::string, Item>::iterator it = rareItems.begin();
	std::advance(it, randValue);
	std::shared_ptr<Item> randItem = std::make_shared<Item>(it->second);
	return randItem;
}

std::shared_ptr<SpecialItem> ItemDB::randomSpecialItem()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	//Sets value for random distribution
	std::uniform_int_distribution<int> distributionInteger(0, specialItems.size() - 1);
	//gets random value from 0 to vector size
	int randValue = distributionInteger(generator);
	//what item is
	//std::cout << "Random Item is: " << specialItems[randValue].description << "\n";
	//makes a shared pointer
	//std::shared_ptr<SpecialItem> randItem = std::make_shared<SpecialItem>(specialItems[randValue]);
	std::map<std::string, SpecialItem>::iterator it = specialItems.begin();
	std::advance(it, randValue);
	std::shared_ptr<SpecialItem> randItem = std::make_shared<SpecialItem>(it->second);
	return randItem;
}

std::shared_ptr<Item> ItemDB::getCommonItem(std::string& name)
{
	std::shared_ptr<Item> item = std::make_shared<Item>(commonItems[name]);
	return item;
}

std::shared_ptr<Item> ItemDB::getRareItem(std::string& name)
{
	std::shared_ptr<Item> item = std::make_shared<Item>(rareItems[name]);
	return item;
}

std::shared_ptr<SpecialItem> ItemDB::getSpecialItem(std::string& name)
{
	std::shared_ptr<SpecialItem> item = std::make_shared<SpecialItem>(specialItems[name]);
	return item;
}

std::shared_ptr<Item> ItemDB::getItem(std::string& name)
{
	if (commonItems.count(name) > 0)
	{
		std::shared_ptr<Item> item = std::make_shared<Item>(commonItems[name]);
		return item;
	}
	else if (rareItems.count(name) > 0)
	{
		std::shared_ptr<Item> item = std::make_shared<Item>(rareItems[name]);
		return item;
	}
	//else if (specialItems.count(name) > 0)
	//{
	//	std::shared_ptr<SpecialItem> item = std::make_shared<SpecialItem>(rareItems[name]);
	//	return item;
	//}
	else
	{
		std::cout << "Couldn't find item: " << name << "\n";
	}
}