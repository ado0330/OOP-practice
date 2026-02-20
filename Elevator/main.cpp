#include <iostream>
using namespace std;

class Elevator {
private:
    int CurrentFloor;
    string Direction;
    int MaxFloor;
public:
    Elevator(int maxFloor) {
        CurrentFloor = 1;
        Direction = "";
        MaxFloor = maxFloor;
    }

    void moveTo(int targetFloor) {
        if (targetFloor > MaxFloor)  {
            cout << "Max Floor is " << MaxFloor << endl; 
            return;
        }
        if (targetFloor > CurrentFloor) {
            Direction = "UP";
            for (int i = CurrentFloor; i <= targetFloor; i++) {
                cout << "Elevator is at floor " << i << "." << endl;
                CurrentFloor = i;
            }
        } else if (targetFloor < CurrentFloor) {
            Direction = "DOWN";
            for (int j = CurrentFloor; j >= targetFloor; j--) {
                cout << "Elevator is at floor " << j << "." << endl;
                CurrentFloor = j;
            }
        } else {
            cout << "SAME FLOOR!" << endl;
        }
    }
};

class Building {
private:
    Elevator elevator;
public:
    Building(int floors) : elevator(floors) {}
    void pressButton(int floor) {
        cout << "\n[Building] Button pressed for floor: " << floor << endl;
        elevator.moveTo(floor);
    }

};



int main() {

    Building myBuilding(10);

    myBuilding.pressButton(5);
    myBuilding.pressButton(8);
    myBuilding.pressButton(4);
    myBuilding.pressButton(10);

} 