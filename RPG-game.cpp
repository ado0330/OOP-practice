#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Entity {
protected:
    string Name;
    int HealthPoints;
    int ATK;
    int ManaPoints;
public:
    Entity(string name, int hp, int atk, int mp) {
        Name = name;
        HealthPoints = hp;
        ATK = atk;
        ManaPoints = mp;
    }

    string getName() {
        return Name;
    }

    int getATK() {
        return ATK;
    }

    void AddMP(int mp) {
        ManaPoints += mp;
    }

    void TakeDamage(int damage) {
        HealthPoints -= damage;
    }

    void BasicAttack(Entity & target) {
        cout << Name << " use Basic Attack." << endl;
        target.TakeDamage(getATK());
        cout << Name << " deals " << getATK() << " damage to " << target.getName() << "." << endl;

    }

    bool IsAlive() {
        if (HealthPoints > 0) return true;
        else return false;
    }
};


class Warrior:public Entity {
public:
    Warrior(string name):Entity(name, 100, 50, 0) {}
    void SpecialAttack(Entity &target) {
            int totalDamage = ATK * 2 + rand() % 10;
            cout << "Tactical Attack!" << endl;
            target.TakeDamage(totalDamage);
            cout << Name << " deals " << totalDamage << " damage to " << target.getName() << "." << endl;
        }
};

class Mage: public Entity {
public:
    Mage(string name):Entity(name, 100, 30, 50) {}
    const int FIREBALL_COST = 25;
    void FireBall(Entity &target) {
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
    Slime():Entity("Slime", 300, 10, 0) {}
};



int main() {
    
    srand(time(0));

    Mage player("Jason");
    Slime slime;

    cout << "---Battle Start---" << endl;
    while (player.IsAlive() && slime.IsAlive()) {
        player.FireBall(slime);
        
        if (slime.IsAlive()) {
            slime.BasicAttack(player); 
        }
        cout << "--------------------" << endl;
        player.AddMP(5);
    }

    if (player.IsAlive()) {
        cout << "You WON!!" << endl;
    } else {
        cout << "GAME OVER" << endl;
    }
}