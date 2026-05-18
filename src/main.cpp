#include "ParkingConsole.h"

int main() {
    ParkingRepository repository;
    ParkingService service;
    ParkingConsole console(service, repository);
    console.run();
    return 0;
}
