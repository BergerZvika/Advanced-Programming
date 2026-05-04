// Concept: when do you reach for friend instead of a public getter?
// Use a getter when ANY caller might want the value.  Use friend when ONLY
// a specific helper needs raw access — keeping the data otherwise hidden.
#include <iostream>

class Sensor {
public:
    Sensor(double raw) : raw_(raw) {}

    // Calibration helper needs the raw, uncalibrated reading.
    // Other callers should NEVER see raw_.
    friend double calibrate(const Sensor& s, double offset);

private:
    double raw_;
};

double calibrate(const Sensor& s, double offset) {
    return s.raw_ + offset;       // raw_ stays private to everyone else
}

int main() {
    Sensor s(36.4);
    std::cout << "calibrated reading = " << calibrate(s, 0.4) << "\n";
    std::cout << "(raw_ has no public getter — only calibrate() can read it)\n";
}
