//MINOR PROJECT - SMART PARKING MANAGEMENT SYSTEM 

//CODE - 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// ---------- ABSTRACT BASE CLASS ----------

class Vehicle {
protected:
    string number;

public:
    Vehicle(string n) {
        number = n;
    }

    string getNumber() {
        return number;
    }

    // Abstraction
    virtual int parkingFee() = 0;

    virtual ~Vehicle() {}
};


// ---------- DERIVED CLASSES ----------

class Car : public Vehicle {
public:
    Car(string n) : Vehicle(n) {}

    int parkingFee() override {
        return 50;
    }
};


class Bike : public Vehicle {
public:
    Bike(string n) : Vehicle(n) {}

    int parkingFee() override {
        return 20;
    }
};


class Truck : public Vehicle {
public:
    Truck(string n) : Vehicle(n) {}

    int parkingFee() override {
        return 80;
    }
};


// ---------- PARKING SLOT ----------

class ParkingSlot {
public:
    int number;
    bool occupied;

    ParkingSlot(int n) {
        number = n;
        occupied = false;
    }
};


// ---------- MAIN ----------

int main() {

    // 1. VECTOR
    // Stores parking slots

    vector<ParkingSlot> slots;

    for (int i = 1; i <= 5; i++) {
        slots.push_back(ParkingSlot(i));
    }


    // 2. UNORDERED_MAP
    // Vehicle number -> Slot number

    unordered_map<string, int> location;


    // 3. SET
    // Stores unique vehicle numbers

    set<string> registered;


    // Create vehicles
    Vehicle* car = new Car("MH31AB1234");
    Vehicle* bike = new Bike("MH31XY5678");
    Vehicle* truck = new Truck("MH31PQ9012");


    // Park the vehicles
    Vehicle* vehicles[] = {car, bike, truck};

    for (Vehicle* v : vehicles) {

        // Check duplicate vehicle
        if (registered.count(v->getNumber())) {
            cout << "Vehicle already registered\n";
            continue;
        }

        // Find empty slot
        for (auto &slot : slots) {

            if (!slot.occupied) {

                slot.occupied = true;

                location[v->getNumber()] =
                    slot.number;

                registered.insert(
                    v->getNumber()
                );

                cout << v->getNumber()
                     << " parked at slot "
                     << slot.number << endl;

                break;
            }
        }
    }


    // Search vehicle

    string number;

    cout << "\nEnter vehicle number: ";
    cin >> number;

    if (location.count(number)) {

        cout << "Vehicle found at slot "
             << location[number] << endl;

    } else {

        cout << "Vehicle not found\n";
    }


    // Runtime polymorphism

    cout << "\nParking fees:\n";

    cout << "Car   : Rs. "
         << car->parkingFee() << endl;

    cout << "Bike  : Rs. "
         << bike->parkingFee() << endl;

    cout << "Truck : Rs. "
         << truck->parkingFee() << endl;


    // Clean memory

    delete car;
    delete bike;
    delete truck;

    return 0;
}