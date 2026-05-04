// Concept: with virtual inheritance, the MOST-DERIVED class is responsible
// for initialising the virtual base directly (its mid-level base ctors are
// ignored for that purpose).
#include <iostream>

class Vehicle {
public:
    Vehicle(int speed) : speed_(speed) {
        std::cout << "  Vehicle ctor speed=" << speed_ << "\n";
    }
    int speed() const { return speed_; }
protected:
    int speed_;
};

class LandVehicle : public virtual Vehicle {
public:
    LandVehicle()  : Vehicle(0) { std::cout << "  LandVehicle ctor\n"; }
};

class WaterVehicle : public virtual Vehicle {
public:
    WaterVehicle() : Vehicle(0) { std::cout << "  WaterVehicle ctor\n"; }
};

class AmphibiousVehicle : public LandVehicle, public WaterVehicle {
public:
    // Most-derived class initialises the VIRTUAL base directly.
    // The LandVehicle/WaterVehicle Vehicle(0) calls above are IGNORED here.
    AmphibiousVehicle(int s) : Vehicle(s) {
        std::cout << "  AmphibiousVehicle ctor (uses Vehicle(" << s << "))\n";
    }
};

int main() {
    AmphibiousVehicle av(90);
    std::cout << "speed = " << av.speed() << " km/h\n";
}
