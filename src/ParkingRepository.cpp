#include "ParkingRepository.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

ParkingRepository::ParkingRepository(const std::string& path) : filePath(path) {}

std::vector<Slot> ParkingRepository::loadSlots() const {
    std::vector<Slot> slots;
    std::ifstream input(filePath.c_str());
    if (!input) {
        return slots;
    }

    try {
        json data;
        input >> data;
        if (!data.contains("slots") || !data["slots"].is_array()) {
            return slots;
        }

        for (size_t i = 0; i < data["slots"].size(); ++i) {
            const json& item = data["slots"][i];
            if (!item.contains("id") || !item.contains("isAvailable")) {
                continue;
            }

            Slot slot;
            slot.id = item["id"].get<int>();
            slot.isAvailable = item["isAvailable"].get<bool>();
            slots.push_back(slot);
        }
    } catch (...) {
        slots.clear();
    }

    return slots;
}

std::vector<Vehicle> ParkingRepository::loadVehicles() const {
    std::vector<Vehicle> vehicles;
    std::ifstream input(filePath.c_str());
    if (!input) {
        return vehicles;
    }

    try {
        json data;
        input >> data;
        if (!data.contains("vehicles") || !data["vehicles"].is_array()) {
            return vehicles;
        }

        for (size_t i = 0; i < data["vehicles"].size(); ++i) {
            const json& item = data["vehicles"][i];
            if (!item.contains("plate") || !item.contains("slotId")) {
                continue;
            }

            Vehicle vehicle;
            vehicle.plate = item["plate"].get<std::string>();
            vehicle.slotId = item["slotId"].get<int>();
            vehicles.push_back(vehicle);
        }
    } catch (...) {
        vehicles.clear();
    }

    return vehicles;
}

void ParkingRepository::saveAll(const std::vector<Slot>& slots,
                                const std::vector<Vehicle>& vehicles) const {
    json data;
    data["slots"] = json::array();
    data["vehicles"] = json::array();

    for (size_t i = 0; i < slots.size(); ++i) {
        json item;
        item["id"] = slots[i].id;
        item["isAvailable"] = slots[i].isAvailable;
        data["slots"].push_back(item);
    }

    for (size_t i = 0; i < vehicles.size(); ++i) {
        json item;
        item["plate"] = vehicles[i].plate;
        item["slotId"] = vehicles[i].slotId;
        data["vehicles"].push_back(item);
    }

    std::ofstream output(filePath.c_str());
    output << data.dump(2);
}

bool ParkingRepository::fileExists() const {
    std::ifstream input(filePath.c_str());
    return input.good();
}
