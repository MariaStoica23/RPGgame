#include "Character.h"

const int Character::baseAttackDamage = 2;
const int Character::baseDefence = 40;
const int Character::baseHealthPoints = 35;

const int Character::maxAttackDamage = 44;
const int Character::maxDefence = 450;
const int Character::maxHealthPoints = 300;

const int Character::startLvl = 1;
const int Character::startHealthPointsCount = 4;
const int Character::healPotionRestorationEffect = 30;

std::string Character::getName() const {
    return this->name;
}

int Character::getLvl() const {
    return this->lvl;
}

int Character::getAttackDamage() const {
    return this->attackDamage;
}

int Character::getDefence() const {
    return this->defence;
}

int Character::getHealthPoints() const {
    return this->healthPoints;
}

int Character::getRemainingHealthPoints() const {
    return this->remainingHealthPoints;
}

int Character::getHealthPotionsCount() const {
    return this->healthPotionsCount;
}

void Character::setName(const std::string& name) {
    this->name = name;
}

void Character::setLvl(const int& lvl) {
    this->lvl = std::max(lvl, 1);
}

void Character::setAttackDamage(const int& attackDamage) {
    this->attackDamage = std::min(attackDamage, maxAttackDamage);
    this->attackDamage = std::max(attackDamage, baseAttackDamage);
}

void Character::setDefence(const int& defence) {
    this->defence = std::min(defence, maxDefence);
    this->defence = std::max(defence, baseDefence);
}

void Character::setHealthPoints(const int& healthPoints) {
    this->healthPoints = std::min(healthPoints, maxHealthPoints);
    this->healthPoints = std::max(healthPoints, baseHealthPoints);
}

void Character::setRemainingHealthPoints(const int& remainingHealthPoints) {
    this->remainingHealthPoints = std::min(remainingHealthPoints, maxHealthPoints);
    this->remainingHealthPoints = std::max(remainingHealthPoints, 0);
}

void Character::setHealthPotionsCount(const int& healthPotionsCount) {
    this->healthPotionsCount = std::max(healthPotionsCount, 0);
}

Character::Character() : name(), 
    lvl(startLvl), 
    attackDamage(baseAttackDamage), 
    defence(baseDefence), 
    healthPoints(baseHealthPoints), 
    remainingHealthPoints(baseHealthPoints), 
    healthPotionsCount(startHealthPointsCount) 
{}

Character::Character(const std::string& name, const int& attackDamage, const int& healthPoints, const int& defence) {
    setName(name);
    setLvl(startLvl);
    setAttackDamage(attackDamage);
    setDefence(defence);
    setHealthPoints(healthPoints);
    setRemainingHealthPoints(healthPoints);
    setHealthPotionsCount(startHealthPointsCount);
}

void Character::heal() {
    if (healthPotionsCount > 0) {
        remainingHealthPoints = std::min(remainingHealthPoints + healPotionRestorationEffect, healthPoints);
        healthPotionsCount = std::max(healthPotionsCount - 1, 0);
    }
}

void Character::attack(Character& enemy) {
    int damageDealt = attackDamage * std::min((double)enemy.healthPoints / enemy.defence, 1.0);
    enemy.setRemainingHealthPoints(enemy.remainingHealthPoints - damageDealt);
}

bool Character::isAlive() const {
    return (remainingHealthPoints != 0);
}

bool Character::operator<(const Character& other) const {
    return (this->attackDamage * this->defence * this->healthPoints) < (other.attackDamage * other.defence * other.healthPoints);
}

bool Character::operator>(const Character& other) const {
    return (this->attackDamage * this->defence * this->healthPoints) > (other.attackDamage * other.defence * other.healthPoints);
}

bool Character::operator==(const Character& other) const {
    return (this->attackDamage * this->defence * this->healthPoints) == (other.attackDamage * other.defence * other.healthPoints);
}

bool Character::operator!=(const Character& other) const {
    return !(*this == other);
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        this->name = other.name;
        this->lvl = other.lvl;
        this->attackDamage = other.attackDamage;
        this->defence = other.defence;
        this->healthPoints = other.healthPoints;
        this->remainingHealthPoints = other.remainingHealthPoints;
        this->healthPotionsCount = other.healthPotionsCount;
    }
    return *this;
}

Character& Character::operator++() {
    setLvl(lvl + 1);
    setAttackDamage(attackDamage + baseAttackDamage);
    setDefence(defence + baseDefence);
    setHealthPoints(healthPoints + baseHealthPoints);
    setRemainingHealthPoints(healthPoints);
    setHealthPotionsCount(startHealthPointsCount);
    return *this;
}

Character Character::operator++(int) {
    Character aux = *this;
    setLvl(lvl + 1);
    setAttackDamage(attackDamage + baseAttackDamage);
    setDefence(defence + baseDefence);
    setHealthPoints(healthPoints + baseHealthPoints);
    setRemainingHealthPoints(healthPoints);
    setHealthPotionsCount(startHealthPointsCount);
    //++(this);
    return aux;
}

std::istream& operator>>(std::istream& in, Character& currentCharacter) {
    std::string name;
    int attackDamage, defence, healthPoints;
    in >> name >> attackDamage >> defence >> healthPoints;
    currentCharacter.setName(name);
    currentCharacter.setAttackDamage(attackDamage);
    currentCharacter.setDefence(defence);
    currentCharacter.setHealthPoints(healthPoints);
    currentCharacter.setRemainingHealthPoints(healthPoints);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Character& currentCharacter) {
    out << "Name: " << currentCharacter.name << std::endl;
    out << "Level: " << currentCharacter.lvl << std::endl;
    out << "Attack damage: " << currentCharacter.attackDamage << std::endl;
    out << "Defence: " << currentCharacter.defence << std::endl;
    out << "Health points: " << currentCharacter.healthPoints << std::endl;
    out << "Remaining health points: " << currentCharacter.remainingHealthPoints << std::endl;
    out << "Health potions count: " << currentCharacter.healthPotionsCount << std::endl;
    return out;
}
