#include <iostream>
#include <vector>

class CarbonFootprint {
public:
    virtual double getCarbonFootprint() const = 0;
    virtual ~CarbonFootprint() {}
};

class Building : public CarbonFootprint {
private:
    double squareFootage;
    double electricityUsage;

public:
    Building(double sqft, double usage) : squareFootage(sqft), electricityUsage(usage) {}

    double getCarbonFootprint() const override {
        // Calculate carbon footprint for a building
        return squareFootage * electricityUsage * 0.5; // Example calculation
    }
};

class Car : public CarbonFootprint {
private:
    double fuelConsumption;
    double mileage;

public:
    Car(double fuel, double miles) : fuelConsumption(fuel), mileage(miles) {}

    double getCarbonFootprint() const override {
        // Calculate carbon footprint for a car
        return fuelConsumption * mileage * 0.7; // Example calculation
    }
};

class Bicycle : public CarbonFootprint {
private:
    bool isElectric;

public:
    Bicycle(bool electric) : isElectric(electric) {}

    double getCarbonFootprint() const override {
        // Calculate carbon footprint for a bicycle
        if (isElectric) {
            return 0.1; // Example carbon footprint for electric bicycle
        } else {
            return 0.05; // Example carbon footprint for regular bicycle
        }
    }
};

int main() {
    std::vector<CarbonFootprint*> objects;

    // Creating objects
    Building building(1000, 10);
    Car car(30, 1000);
    Bicycle bicycle(true);

    // Adding pointers to objects in the vector
    objects.push_back(&building);
    objects.push_back(&car);
    objects.push_back(&bicycle);

    // Iterating through the vector, polymorphically invoking each object's getCarbonFootprint method
    for (const auto& obj : objects) {
        // Printing identifying information (type) and the object's carbon footprint with appropriate units
        if (dynamic_cast<Building*>(obj)) {
            std::cout << "Building's carbon footprint: " << obj->getCarbonFootprint() << " kgCO2/year" << std::endl;
        } else if (dynamic_cast<Car*>(obj)) {
            std::cout << "Car's carbon footprint: " << obj->getCarbonFootprint() << " kgCO2/year" << std::endl;
        } else if (dynamic_cast<Bicycle*>(obj)) {
            std::cout << "Bicycle's carbon footprint: " << obj->getCarbonFootprint() << " kgCO2/year" << std::endl;
        }
    }

    return 0;
}

