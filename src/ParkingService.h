#ifndef PARKING_SERVICE_H
#define PARKING_SERVICE_H

#include "Slot.h"
#include "Vehicle.h"
#include <string>
#include <vector>

class ParkingService {
public:
    void initialize(const std::vector<Slot>& slots, const std::vector<Vehicle>& vehicles);
    int parkVehicle(const std::string& plate);
    bool removeVehicleByPlate(const std::string& plate);
    bool removeVehicleBySlot(int slotId);
    std::vector<Slot> getAvailableSlots() const;
    int searchVehicle(const std::string& plate) const;
    std::vector<Slot> getSlots() const;
    const Vehicle* getVehicleBySlot(int slotId) const;
    std::vector<Vehicle> getVehicles() const;
    bool isDuplicateVehicle(const std::string& plate) const;
    bool slotExists(int slotId) const;
    bool isSlotAvailable(int slotId) const;
    bool hasAvailableSlot() const;
    bool validatePlate(const std::string& plate) const;

private:
    bool removeVehicleAt(size_t index);
    bool samePlate(const std::string& left, const std::string& right) const;

    std::vector<Slot> slots;
    std::vector<Vehicle> vehicles;
};

#endif
