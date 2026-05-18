
#include "ParkingService.h"
#include <algorithm>
#include <cctype>

void ParkingService::initialize(const std::vector<Slot>& loadedSlots,
    const std::vector<Vehicle>& loadedVehicles) {
    slots = loadedSlots;
    vehicles.clear();

    for (size_t i = 0; i < slots.size(); ++i) {
        slots[i].isAvailable = true;
    }

    for (size_t i = 0; i < loadedVehicles.size(); ++i) {
        const Vehicle& vehicle = loadedVehicles[i];
        if (!validatePlate(vehicle.plate) || isDuplicateVehicle(vehicle.plate)
            || !slotExists(vehicle.slotId) || !isSlotAvailable(vehicle.slotId)) {
            continue;
        }

        vehicles.push_back(vehicle);
        for (size_t j = 0; j < slots.size(); ++j) {
            if (slots[j].id == vehicle.slotId) {
                slots[j].isAvailable = false;
                break;
            }
        }
    }
}

int ParkingService::parkVehicle(const std::string& plate) {
    if (!validatePlate(plate) || isDuplicateVehicle(plate) || !hasAvailableSlot()) {
        return 0;
    }

    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].isAvailable) {
            slots[i].isAvailable = false;
            Vehicle vehicle;
            vehicle.plate = plate;
            vehicle.slotId = slots[i].id;
            vehicles.push_back(vehicle);
            return slots[i].id;
        }
    }

    return 0;
}

bool ParkingService::removeVehicleByPlate(const std::string& plate) {
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (samePlate(vehicles[i].plate, plate)) {
            return removeVehicleAt(i);
        }
    }
    return false;
}

bool ParkingService::removeVehicleBySlot(int slotId) {
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].slotId == slotId) {
            return removeVehicleAt(i);
        }
    }
    return false;
}

std::vector<Slot> ParkingService::getAvailableSlots() const {
    std::vector<Slot> available;
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].isAvailable) {
            available.push_back(slots[i]);
        }
    }
    return available;
}

int ParkingService::searchVehicle(const std::string& plate) const {
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (samePlate(vehicles[i].plate, plate)) {
            return vehicles[i].slotId;
        }
    }
    return 0;
}

std::vector<Slot> ParkingService::getSlots() const {
    return slots;
}

const Vehicle* ParkingService::getVehicleBySlot(int slotId) const {
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].slotId == slotId) {
            return &vehicles[i];
        }
    }
    return 0;
}

std::vector<Vehicle> ParkingService::getVehicles() const {
    return vehicles;
}

bool ParkingService::isDuplicateVehicle(const std::string& plate) const {
    return searchVehicle(plate) != 0;
}

bool ParkingService::slotExists(int slotId) const {
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].id == slotId) {
            return true;
        }
    }
    return false;
}

bool ParkingService::isSlotAvailable(int slotId) const {
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].id == slotId) {
            return slots[i].isAvailable;
        }
    }
    return false;
}

bool ParkingService::hasAvailableSlot() const {
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].isAvailable) {
            return true;
        }
    }
    return false;
}

bool ParkingService::validatePlate(const std::string& plate) const {
    for (size_t i = 0; i < plate.size(); ++i) {
        if (!std::isspace(static_cast<unsigned char>(plate[i]))) {
            return true;
        }
    }
    return false;
}

bool ParkingService::removeVehicleAt(size_t index) {
    if (index >= vehicles.size()) {
        return false;
    }

    int slotId = vehicles[index].slotId;
    vehicles.erase(vehicles.begin() + static_cast<std::vector<Vehicle>::difference_type>(index));
    for (size_t i = 0; i < slots.size(); ++i) {
        if (slots[i].id == slotId) {
            slots[i].isAvailable = true;
            break;
        }
    }
    return true;
}

bool ParkingService::samePlate(const std::string& left, const std::string& right) const {
    if (left.size() != right.size()) {
        return false;
    }

    for (size_t i = 0; i < left.size(); ++i) {
        unsigned char a = static_cast<unsigned char>(left[i]);
        unsigned char b = static_cast<unsigned char>(right[i]);
        if (std::tolower(a) != std::tolower(b)) {
            return false;
        }
    }
    return true;
}
