#include "Entity.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>

void goToCave(Entity *player) {
    int AMOUNT_MONSTER_TYPE = 2;
    Entity *enemy = nullptr;
    //Random Monster logic
    int r = rand() % AMOUNT_MONSTER_TYPE;

    switch(r) {
        case 0:
            enemy = new Slime();
            break;
        case 1:
            enemy = new Goblin();
            break;
    }



    int goldReward = 100;
    cout << "\n--- You entered a dark cave and found a " << enemy->getName() << "  ---" << endl;
    while (player->IsAlive() && enemy->IsAlive()) {
        //Battle Menu
        cout << "\n[" << player->getName() << " HP: " << player->getHP() << " | MP: " << player->getMP() << "]" << endl;
        cout << "[Enemy " << enemy->getName() << " HP: " << enemy->getHP() << "]" << endl;
        
        int choice;
        cout << "1. Basic Attack   2. Skill   3. Skip\nChoice: ";
        cin >> choice;

        //Player turn
        switch(choice) {
            case 1:
                player->BasicAttack(*enemy);
                break;
            case 2:
                player->UseSkill(*enemy);
                break;
            case 3:
                cout << "You Skipped your turn." << endl;
                break;
            default:
                cout << "You hesitated and wasted your turn!" << endl;
        }

        //Monster turn
        if(enemy->IsAlive()) {
            cout << " --- " << enemy->getName() << "'s Turn --- " << endl;
            enemy->UseSkill(*player);
        } else {
            cout << enemy->getName() << " has been defeated..." << endl;
        }

        player->AddMP(5);
        cout << "-----------------------------" << endl;
        cout << "Press Enter to Continue." << endl;
        cin.ignore();
        cin.get();
    }   
    if (player->IsAlive()) {
        player->AddGold(goldReward);
        cout << "You WON!!" << endl;
        cout << "You gain " << goldReward << " gold!" << endl;
        cout << "Now you have " << player->getGold() << " gold!" << endl;
    } else {
        cout << "You were defeated..." << endl;
    }

    delete enemy;
    enemy = nullptr;
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

    if (gold >= AMOUNT_WARRIOR_WEAPON && className == "Warrior" && choice == 1) {
        cout << "Purchase successful!" << endl;
        player->spendGold(AMOUNT_WARRIOR_WEAPON);
        player->setWeapon(WEAPON_WARRIOR);
        player->WeaponBuff(10, 10, 0);
        

    } else if (AMOUNT_MAGE_WEAPON && className == "Mage" && choice == 2) {
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