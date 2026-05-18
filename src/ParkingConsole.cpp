#include "ParkingConsole.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>

namespace {
std::string trim(const std::string& value) {
    size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }

    size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    return value.substr(start, end - start);
}
}

ParkingConsole::ParkingConsole(ParkingService& serviceRef, ParkingRepository& repositoryRef)
    : service(serviceRef), repository(repositoryRef) {}

void ParkingConsole::run() {
    initializeSystem();

    while (true) {
        showMenu();
        int choice = readInt("Select option: ");

        if (choice == 1) {
            parkVehicle();
        } else if (choice == 2) {
            removeVehicle();
        } else if (choice == 3) {
            viewAvailableSlots();
        } else if (choice == 4) {
            searchVehicle();
        } else if (choice == 5) {
            viewParkingStatus();
        } else if (choice == 6) {
            std::cout << "Exiting application.\n";
            break;
        } else {
            std::cout << "Invalid choice. Enter a number from 1 to 6.\n";
        }
    }
}

void ParkingConsole::showMenu() const {
    std::cout << "\n--- Parking Lot System ---\n";
    std::cout << "1. Park Vehicle\n";
    std::cout << "2. Remove Vehicle\n";
    std::cout << "3. View Available Slots\n";
    std::cout << "4. Search Vehicle\n";
    std::cout << "5. View Parking Status\n";
    std::cout << "6. Exit\n";
}

void ParkingConsole::initializeSystem() {
    service.initialize(repository.loadSlots(), repository.loadVehicles());
    std::cout << "Parking data loaded from "
              << (repository.fileExists() ? "existing" : "new")
              << " storage.\n";
}

void ParkingConsole::parkVehicle() {
    std::string plate = readString("Enter license plate: ");
    int slotId = service.parkVehicle(plate);
    if (slotId == 0) {
        std::cout << "Unable to park vehicle. Check plate, duplicates, and slot availability.\n";
        return;
    }

    repository.saveAll(service.getSlots(), service.getVehicles());
    std::cout << "Vehicle parked successfully in slot " << slotId << ".\n";
}

void ParkingConsole::removeVehicle() {
    std::string input = readString("Enter license plate or slot ID: ");
    std::istringstream stream(input);
    int slotId = 0;
    bool removed = false;

    if (stream >> slotId && stream.eof()) {
        removed = service.removeVehicleBySlot(slotId);
    } else {
        removed = service.removeVehicleByPlate(input);
    }

    if (!removed) {
        std::cout << "Unable to remove vehicle. Check the plate or slot ID.\n";
        return;
    }

    repository.saveAll(service.getSlots(), service.getVehicles());
    std::cout << "Vehicle removed successfully.\n";
}

void ParkingConsole::viewAvailableSlots() const {
    std::vector<Slot> slots = service.getAvailableSlots();
    if (slots.empty()) {
        std::cout << "No available slots.\n";
        return;
    }

    std::cout << "Available slots:";
    for (size_t i = 0; i < slots.size(); ++i) {
        std::cout << " " << slots[i].id;
    }
    std::cout << "\n";
}

void ParkingConsole::searchVehicle() const {
    std::string plate = readString("Enter license plate: ");
    int slotId = service.searchVehicle(plate);
    if (slotId == 0) {
        std::cout << "Vehicle not found.\n";
        return;
    }

    std::cout << "Vehicle is parked in slot " << slotId << ".\n";
}

void ParkingConsole::viewParkingStatus() const {
    std::vector<Slot> slots = service.getSlots();
    if (slots.empty()) {
        std::cout << "No parking slots configured.\n";
        return;
    }

    for (size_t i = 0; i < slots.size(); ++i) {
        std::cout << "Slot " << slots[i].id << ": "
                  << (slots[i].isAvailable ? "Available" : "Occupied");
        const Vehicle* vehicle = service.getVehicleBySlot(slots[i].id);
        if (vehicle != 0) {
            std::cout << " | Vehicle: " << vehicle->plate;
        }
        std::cout << "\n";
    }
}

int ParkingConsole::readInt(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            return 0;
        }

        std::istringstream stream(line);
        int value = 0;
        if (stream >> value && stream.eof()) {
            return value;
        }

        std::cout << "Invalid number. Please try again.\n";
    }
}

std::string ParkingConsole::readString(const std::string& prompt) const {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return trim(value);
}
