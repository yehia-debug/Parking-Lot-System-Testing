#ifndef PARKING_REPOSITORY_H
#define PARKING_REPOSITORY_H

#include "Slot.h"
#include "Vehicle.h"
#include <string>
#include <vector>

class ParkingRepository {
public:
    explicit ParkingRepository(const std::string& filePath = "parking.json");

    std::vector<Slot> loadSlots() const;
    std::vector<Vehicle> loadVehicles() const;
    void saveAll(const std::vector<Slot>& slots, const std::vector<Vehicle>& vehicles) const;
    bool fileExists() const;

private:
    std::string filePath;
};

#endif
