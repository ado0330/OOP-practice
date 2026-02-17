#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Entity {
protected:
    string Name;
    int HealthPoints;
    int ATK;
    int ManaPoints;
    int Gold = 1000000;
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

void goToCave(Entity *player) {
    //Battle Logic
    Slime slime;
    int amount = 100;
    cout << "\n--- You entered a dark cave and found a Slime! ---" << endl;
    while (player->IsAlive() && slime.IsAlive()) {
        player->ShowStatus();
        player->UseSkill(slime);
        
        if (slime.IsAlive()) {
            slime.BasicAttack(*player); 
        }
        player->AddMP(5); 
    }   
    if (player->IsAlive()) {
        player->AddGold(amount);
        cout << "You WON!!" << endl;
        cout << "You gain " << amount << " gold!" << endl;
        cout << "Now you have " << player->getGold() << " gold!" << endl;
    } else {
        cout << "You were defeated..." << endl;
    }
}

void goToShop(Entity *player) {
    int choice = 0;
    const int AMOUNT_WARRIOR_WEAPON = 300;
    const int AMOUNT_MAGE_WEAPON = 300;
    const string WEAPON_WARRIOR = "Katana";
    const string WEAPON_MAGE = "Wand of Sparking";

    do {
    cout << "---WELCOME TO WEAPON STORE---" << endl;
    cout << "1. "<< WEAPON_WARRIOR << "(Warrior)            --- " << AMOUNT_WARRIOR_WEAPON << " Gold" << endl;
    cout << "2. "<< WEAPON_MAGE << " (Mage)     --- " << AMOUNT_MAGE_WEAPON << " Gold" << endl;
    cout << "3. Exit Shop" << endl;
    cout << "Enter your choice: " << endl;
    cin  >> choice;

    if (choice == 3) {
        break;
    }
    
    int gold = player->getGold();
    string className = player->getClassName();

    if (gold >= 300 && className == "Warrior" && choice == 1) {
        cout << "Purchase successful!" << endl;
        player->spendGold(AMOUNT_WARRIOR_WEAPON);
        player->setWeapon(WEAPON_WARRIOR);
        player->WeaponBuff(10, 10, 0);
        

    } else if (gold >= 300 && className == "Mage" && choice == 2) {
        cout << "Purchase successful!" << endl;
        player->spendGold(AMOUNT_MAGE_WEAPON);
        player->setWeapon(WEAPON_MAGE);
        player->WeaponBuff(5, 15, 15);
    } else {
        cout << "Purchase unsuccessful.\n Please check you buy the weapon match with your class!" << endl;
    }

    } while (true);


}



int main() {
    
    srand(time(0));

    string name;
    int choice;
    Entity* player = nullptr;

    cout << "Enter your name: " << endl;
    getline(cin, name);

    //Initilize the player class
    do {
        cout << "----------SELECT YOUR CLASS----------" << endl;
        cout << "1. Warrior" << endl;
        cout << "2. Mage" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice != 1 && choice != 2) cout << "Invalid choice!" << endl;
    } while (choice != 1 && choice != 2);

    switch (choice) {
        case 1:
            player = new Warrior(name);
            break;
        case 2:
            player = new Mage(name);
            break;

    }


    //Menu
    bool gameRunning = true;
    while (gameRunning && player->IsAlive()) {
        int action;
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Go to Cave (Battle)" << endl;
        cout << "2. Go to Shop (Upgrade)" << endl;
        cout << "3. Check Status" << endl;
        cout << "4. Quit Game" << endl;
        cin >> action;

        switch(action) {
            case 1:
                goToCave(player);
                break;
            case 2:
                goToShop(player);
                break;
            case 3:
                player->ShowStatus();
                break;
            case 4:
                gameRunning = false;
                break;
        }
    }

    delete player;
    player = nullptr;

    return 0;
}