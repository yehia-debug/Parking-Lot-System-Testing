#ifndef PARKING_CONSOLE_H
#define PARKING_CONSOLE_H

#include "ParkingRepository.h"
#include "ParkingService.h"
#include <string>

class ParkingConsole {
public:
    ParkingConsole(ParkingService& service, ParkingRepository& repository);

    void run();
    void showMenu() const;
    void initializeSystem();
    void parkVehicle();
    void removeVehicle();
    void viewAvailableSlots() const;
    void searchVehicle() const;
    void viewParkingStatus() const;
    int readInt(const std::string& prompt) const;
    std::string readString(const std::string& prompt) const;

private:
    ParkingService& service;
    ParkingRepository& repository;
};

#endif
