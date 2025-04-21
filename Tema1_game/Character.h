#pragma once
#include<iostream>
#include<string>

class Character
{
public:
	std::string getName() const;
	int getLvl() const;
	int getAttackDamage() const;
	int getDefence() const;
	int getHealthPoints() const;
	int getRemainingHealthPoints() const;
	int getHealthPotionsCount() const;

	void setName(const std::string& name);
	void setLvl(const int& lvl);
	void setAttackDamage(const int& attackDamage);
	void setDefence(const int& defence);
	void setHealthPoints(const int& healthPoints);
	void setRemainingHealthPoints(const int& remainingHealthPoints);
	void setHealthPotionsCount(const int& healthPotionsCount);

	Character();
	Character(const std::string& name, const int& attackDamage, const int& healthPoints, const int& defence);

	void heal();
	void attack(Character& enemy);

	bool isAlive() const;

	friend std::istream& operator>>(std::istream& in, Character& currentCharacter);
	friend std::ostream& operator<<(std::ostream& out, const Character& currentCharacter);

	bool operator<(const Character& other) const;
	bool operator>(const Character& other) const;
	bool operator==(const Character& other) const;
	bool operator!=(const Character& other) const;

	Character& operator=(const Character& other);

	Character& operator++();
	Character operator++(int);

private:
	static const int baseAttackDamage;
	static const int baseDefence;
	static const int baseHealthPoints;

	static const int maxAttackDamage;
	static const int maxDefence;
	static const int maxHealthPoints;

	static const int startLvl;
	static const int startHealthPointsCount;
	static const int healPotionRestorationEffect;

private:
	std::string name;
	int lvl;
	int attackDamage;
	int defence;
	int healthPoints;
	int remainingHealthPoints;
	int healthPotionsCount;
};

