#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using std::string;
using std::cout;
using std:: cin;
using std::vector;
using std::endl;

class Card {
protected:
    string Name;
    int Damage;
    string Element;
public:
    Card(string name, int damage, string element) {
        Name = name;
        Damage = damage;
        Element = element;
    }
    
    int getDamage() {
        return Damage;
    }

    string getElement() {
        return Element;
    }

    string getName() {
        return Name;
    }


};

class FireCard: public Card {
public: 
    FireCard():Card("FireCard", 10, "FIRE") {}
};
class WaterCard: public Card {
public: 
    WaterCard():Card("WaterCard", 10, "WATER") {}
};
class GrassCard: public Card {
public: 
    GrassCard():Card("GrassCard", 10, "GRASS") {}
};

class Player {
private:
    string Name;
    int HP;
    vector<Card*> hand;
public:
    Player(string name, int hp) {
        Name = name;
        HP = hp;   
    }

    bool IsAlive() {
        if (HP <= 0) return false;
        return true;
    }

    void drawCard() {
        int r = rand() % 3;
        if (r == 0) {
            hand.push_back(new FireCard());
        } else if (r == 1) {
            hand.push_back(new WaterCard());
        } else {
            hand.push_back(new GrassCard());
        }
    }

    void showHand() {
        cout << Name << "'s Hand: " << endl;
        for (int i = 0; i < hand.size(); i++) {
            cout << "[" << i << ": " << hand[i]->getName() << "] ";
        }
        cout << endl;
    }

    Card* playCard(int index) {
        Card* selected = hand[index];
        hand.erase(hand.begin()+ index);
        return selected;
    }

    string getName() {
        return Name;
    }

    int getHP() {
        return HP;
    }

    void takeDamage(int damage) {
        HP -= damage;
    }

};

void calculateBatlle(Card* cardPlayer1, Card* cardPlayer2, Player* player1, Player* player2) {
    int finalDamage = cardPlayer1->getDamage();

    if ((cardPlayer1->getElement() == "FIRE" && cardPlayer2->getElement() == "GRASS")||(cardPlayer1->getElement() == "WATER" && cardPlayer2->getElement() == "FIRE")||(cardPlayer1->getElement() == "GRASS" && cardPlayer2->getElement() == "WATER")) {
        finalDamage *= 2;
        cout << "It's super effective!" << endl;
    } else if ((cardPlayer1->getElement() == "GRASS" && cardPlayer2->getElement() == "FIRE")||(cardPlayer1->getElement() == "FIRE" && cardPlayer2->getElement() == "WATER")||(cardPlayer1->getElement() == "WATER" && cardPlayer2->getElement() == "GRASS")) {
        finalDamage *= 0.5;
        cout << "It's non effective." << endl;
    }

    cout << "Total Damage dealt by "<< player1->getName() << ": " << finalDamage << endl;
    player2->takeDamage(finalDamage);
}


int main() {

    srand(time(0));


    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    Player * player1 = new Player(name, 100);
    Player * computer = new Player("Computer", 100);
    
    cout << "Now each player draw 3 cards" << endl;
    for (int i = 0; i < 3; i++) {
            player1->drawCard();
            computer->drawCard();
    }
    cout << "--------------------------------------------" << endl;
    cout << "                 Battle start               " << endl;
    cout << "--------------------------------------------" << endl;
    while(player1->IsAlive() && computer->IsAlive()) {
        cout << endl;
        cout << player1->getName() << "[HP: " << player1->getHP() << "]           " << computer->getName() << "[HP: " << computer->getHP() << "]" << endl;
        cout << endl;
        player1->showHand();
        int index;
        cout << "Choose Card You Want to Play(0-2): ";
        cin >> index;
        cin.ignore();

        cout << "--------------------------------------------" << endl;

        Card* myCard = player1->playCard(index);
        Card* computerCard = computer->playCard(rand()%3);

        cout << player1->getName() << " played " << myCard->getName() << " [" << myCard->getElement() << "]" << endl;
        cout << computer->getName() << " played " << computerCard->getName() << " [" << computerCard->getElement() << "]" << endl;

        calculateBatlle(myCard, computerCard, player1, computer);
        calculateBatlle(computerCard, myCard, computer, player1);

        cout << "--------------------------------------------" << endl;
        cout << "Press Enter to Continue..." << endl;

        cin.get();


        player1->drawCard();
        computer->drawCard();

        delete myCard;
        delete computerCard;

    }

    if(player1->IsAlive()) {
        cout << "Congrats, You WON!!" << endl;
    } else {
        cout << "You were defeated..." << endl;
    }

    delete player1;
    delete computer;    





    return 0;
}