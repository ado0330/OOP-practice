#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

using namespace std;

class Entity {
protected:
    string Name;
    int HealthPoints;
    int ATK;
    int ManaPoints;
    int Gold = 100;
    string Weapon;
public:
    Entity(string name, int hp, int atk, int mp, string weapon) {
        Name = name;
        HealthPoints = hp;
        ATK = atk;
        ManaPoints = mp;
        Weapon = weapon;
    }

    virtual ~Entity(){};

    string getName() {
        return Name;
    }

    int getHP() {
        return HealthPoints;
    }

    int getMP() {
        return ManaPoints;
    }

    int getATK() {
        return ATK;
    }

    int getGold() {
        return Gold;
    }

    void spendGold(int amount) {
        Gold -= amount;
    }

    void setWeapon(string weapon) {
        Weapon = weapon;
    }

    void AddMP(int mp) {
        ManaPoints += mp;
    }

    void TakeDamage(int damage) {
        HealthPoints -= damage;
    }

    void AddGold(int amount) {
        Gold += amount;
    }


    void BasicAttack(Entity & target) {
        cout << Name << " use Basic Attack." << endl;
        int r = rand() % 100;
        int totalDamage;
        if(r < 33) {
            totalDamage = ATK*2;
            cout << Name << " hits Critical Damage!" << endl;
        } else {
            totalDamage = ATK;
        }
        target.TakeDamage(totalDamage);
        cout << Name << " deals " << totalDamage << " damage to " << target.getName() << "." << endl;

    }
    bool IsAlive() {
        if (HealthPoints > 0) return true;
        else return false;
    }

    virtual void UseSkill(Entity & target) {}
    virtual string getClassName() = 0;
    virtual void ShowStatus() {
        cout << "---------Status---------" << endl;
        cout << "Name: " << Name << endl;
        cout << "Class: " << getClassName() << endl; 
        cout << "HP: " << HealthPoints << endl;
        cout << "ATK: " << ATK << endl;
        cout << "MP: " << ManaPoints << endl;
        cout << "Weapon: " << Weapon << endl;
        cout << "Gold: " << getGold() << endl;
        cout << "------------------------" << endl;
        cout << "Press Enter to Continue\n" << endl;
    }

    void WeaponBuff(int hp, int atk, int mp) {
        HealthPoints += hp;
        ATK += atk;
        ManaPoints += mp;

    }

    

};


class Warrior:public Entity {
public:
    Warrior(string name):Entity(name, 100, 25, 0, "Longsword") {}
    string getClassName() {return "Warrior";}
    void UseSkill(Entity &target) override{
            int totalDamage = ATK * 2 + rand() % 10;
            cout << "Tactical Attack!" << endl;
            target.TakeDamage(totalDamage);
            cout << Name << " deals " << totalDamage << " damage to " << target.getName() << "." << endl;
        }
};

class Mage: public Entity {
public:
    Mage(string name):Entity(name, 80, 30, 50, "Wand") {}
    string getClassName() {return "Mage";}
    const int FIREBALL_COST = 25;
    void UseSkill(Entity &target) override{
        int totalDamage = ATK * 3;
            if (ManaPoints >= FIREBALL_COST) {
                cout << "Fire Ball!" << endl;
                target.TakeDamage(totalDamage);
                cout << Name << " deals " << totalDamage << " damage to " << target.getName() << "." << endl;
                ManaPoints -= FIREBALL_COST;
            } else {
                cout << "Out of MP" << endl;
                BasicAttack(target);
            }
        }
};

class Slime:public Entity {
public:
    Slime():Entity("Slime", 300, 15, 0, "") {}
    void UseSkill(Entity &target) override {
        BasicAttack(target);
    }
    string getClassName() {return "Monster";}
};

class Goblin:public Entity {
public:
    Goblin():Entity("Goblin", 300, 15, 0, "") {}
    void UseSkill(Entity &target) override {
        BasicAttack(target);
    }
    string getClassName() {return "Monster";}
};

#endif