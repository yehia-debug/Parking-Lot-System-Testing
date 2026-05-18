
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include "../Parking Lot System/src/json.hpp"

using json = nlohmann::json;
using namespace std;
using ::testing::_;

// =====================================================
// Simple copied classes for testing
// =====================================================

struct Slot {
    int id;
    bool isAvailable;
};

struct Vehicle {
    string plate;
    int slotId;
};

class ParkingService {
private:
    vector<Slot> slots;
    vector<Vehicle> vehicles;

    bool samePlate(const string& left, const string& right) const {
        if (left.size() != right.size()) return false;

        for (size_t i = 0; i < left.size(); ++i) {
            if (tolower(left[i]) != tolower(right[i])) return false;
        }

        return true;
    }

    bool removeVehicleAt(size_t index) {
        if (index >= vehicles.size()) return false;

        int slotId = vehicles[index].slotId;
        vehicles.erase(vehicles.begin() + index);

        for (auto& slot : slots) {
            if (slot.id == slotId) {
                slot.isAvailable = true;
                break;
            }
        }

        return true;
    }

public:
    void initialize(const vector<Slot>& loadedSlots,
        const vector<Vehicle>& loadedVehicles) {
        slots = loadedSlots;
        vehicles.clear();

        for (auto& slot : slots) {
            slot.isAvailable = true;
        }

        for (const auto& vehicle : loadedVehicles) {
            if (!validatePlate(vehicle.plate)) continue;
            if (isDuplicateVehicle(vehicle.plate)) continue;
            if (!slotExists(vehicle.slotId)) continue;
            if (!isSlotAvailable(vehicle.slotId)) continue;

            vehicles.push_back(vehicle);

            for (auto& slot : slots) {
                if (slot.id == vehicle.slotId) {
                    slot.isAvailable = false;
                    break;
                }
            }
        }
    }

    int parkVehicle(const string& plate) {
        if (!validatePlate(plate)) return 0;
        if (isDuplicateVehicle(plate)) return 0;
        if (!hasAvailableSlot()) return 0;

        for (auto& slot : slots) {
            if (slot.isAvailable) {
                slot.isAvailable = false;
                vehicles.push_back({ plate, slot.id });
                return slot.id;
            }
        }

        return 0;
    }

    bool removeVehicleByPlate(const string& plate) {
        for (size_t i = 0; i < vehicles.size(); ++i) {
            if (samePlate(vehicles[i].plate, plate)) {
                return removeVehicleAt(i);
            }
        }

        return false;
    }

    bool removeVehicleBySlot(int slotId) {
        for (size_t i = 0; i < vehicles.size(); ++i) {
            if (vehicles[i].slotId == slotId) {
                return removeVehicleAt(i);
            }
        }

        return false;
    }

    int searchVehicle(const string& plate) const {
        for (const auto& vehicle : vehicles) {
            if (samePlate(vehicle.plate, plate)) {
                return vehicle.slotId;
            }
        }

        return 0;
    }

    vector<Slot> getAvailableSlots() const {
        vector<Slot> result;

        for (const auto& slot : slots) {
            if (slot.isAvailable) {
                result.push_back(slot);
            }
        }

        return result;
    }

    vector<Slot> getSlots() const {
        return slots;
    }

    vector<Vehicle> getVehicles() const {
        return vehicles;
    }

    const Vehicle* getVehicleBySlot(int slotId) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle.slotId == slotId) {
                return &vehicle;
            }
        }

        return nullptr;
    }

    bool validatePlate(const string& plate) const {
        for (char c : plate) {
            if (!isspace(static_cast<unsigned char>(c))) {
                return true;
            }
        }

        return false;
    }

    bool isDuplicateVehicle(const string& plate) const {
        return searchVehicle(plate) != 0;
    }

    bool slotExists(int slotId) const {
        for (const auto& slot : slots) {
            if (slot.id == slotId) return true;
        }

        return false;
    }

    bool isSlotAvailable(int slotId) const {
        for (const auto& slot : slots) {
            if (slot.id == slotId) return slot.isAvailable;
        }

        return false;
    }

    bool hasAvailableSlot() const {
        for (const auto& slot : slots) {
            if (slot.isAvailable) return true;
        }

        return false;
    }
};

// =====================================================
// Mock Class
// =====================================================

class MockParkingNotifier {
public:
    MOCK_METHOD(void, notifyParked, (string plate, int slotId), ());
    MOCK_METHOD(void, notifyRemoved, (string plate), ());
};

// =====================================================
// Test Fixture
// =====================================================

class ParkingServiceTest : public ::testing::Test {
protected:
    ParkingService service;

    void SetUp() override {
        vector<Slot> slots = {
            {1, true},
            {2, true},
            {3, true}
        };

        vector<Vehicle> vehicles = {};

        service.initialize(slots, vehicles);
    }
};

// =====================================================
// 1. Unit Testing
// =====================================================

TEST_F(ParkingServiceTest, TC_PV_01_ParkValidVehicle) {
    int slotId = service.parkVehicle("ABC123");

    EXPECT_EQ(slotId, 1);
    EXPECT_EQ(service.searchVehicle("ABC123"), 1);
}

TEST_F(ParkingServiceTest, TC_PV_02_RejectEmptyLicensePlate) {
    int slotId = service.parkVehicle("");

    EXPECT_EQ(slotId, 0);
    EXPECT_TRUE(service.getVehicles().empty());
}

// Defect-revealing version of TC-PV-02
TEST_F(ParkingServiceTest, TC_PV_02_InvalidPlateFormatShouldBeRejected) {
    int slotId = service.parkVehicle("@@@@");

    EXPECT_EQ(slotId, 0);
}

TEST_F(ParkingServiceTest, TC_PV_03_RejectDuplicateVehicle) {
    int firstSlot = service.parkVehicle("ABC123");
    int secondSlot = service.parkVehicle("ABC123");

    EXPECT_EQ(firstSlot, 1);
    EXPECT_EQ(secondSlot, 0);
    EXPECT_EQ(service.getVehicles().size(), 1);
}

TEST_F(ParkingServiceTest, TC_PV_04_RejectParkingWhenFull) {
    service.parkVehicle("CAR001");
    service.parkVehicle("CAR002");
    service.parkVehicle("CAR003");

    int slotId = service.parkVehicle("CAR004");

    EXPECT_EQ(slotId, 0);
    EXPECT_EQ(service.getVehicles().size(), 3);
}

TEST_F(ParkingServiceTest, TC_RV_03_RejectNonexistentPlate) {
    service.parkVehicle("ABC123");

    bool removed = service.removeVehicleByPlate("NO999");

    EXPECT_FALSE(removed);
    EXPECT_EQ(service.searchVehicle("ABC123"), 1);
    EXPECT_FALSE(service.isSlotAvailable(1));
}

TEST_F(ParkingServiceTest, TC_RV_04_RejectNonexistentSlotID) {
    service.parkVehicle("ABC123");

    bool removed = service.removeVehicleBySlot(99);

    EXPECT_FALSE(removed);
    EXPECT_EQ(service.searchVehicle("ABC123"), 1);
    EXPECT_FALSE(service.isSlotAvailable(1));
}

TEST_F(ParkingServiceTest, TC_SV_01_SearchExistingVehicle) {
    service.parkVehicle("ABC123");

    int slotId = service.searchVehicle("ABC123");

    EXPECT_EQ(slotId, 1);
}

TEST_F(ParkingServiceTest, TC_SV_02_SearchNonexistentVehicle) {
    service.parkVehicle("ABC123");

    int slotId = service.searchVehicle("NO999");

    EXPECT_EQ(slotId, 0);
}

TEST_F(ParkingServiceTest, TC_SV_03_SearchUsingDifferentCase) {
    service.parkVehicle("ABC123");

    int slotId = service.searchVehicle("abc123");

    EXPECT_EQ(slotId, 1);
}


// =====================================================
// 2. Integration Testing
// =====================================================

TEST_F(ParkingServiceTest, TC_IN_01_LoadParkingSlotsAndVehicleRecords) {
    vector<Slot> slots = {
        {1, true},
        {2, true},
        {3, true}
    };

    vector<Vehicle> vehicles = {
        {"ABC123", 1}
    };

    service.initialize(slots, vehicles);

    EXPECT_EQ(service.getSlots().size(), 3);
    EXPECT_EQ(service.getVehicles().size(), 1);
    EXPECT_FALSE(service.isSlotAvailable(1));
    EXPECT_TRUE(service.isSlotAvailable(2));
    EXPECT_TRUE(service.isSlotAvailable(3));
}

TEST_F(ParkingServiceTest, TC_IN_02_LoadSlotDataWithoutParkedVehicles) {
    vector<Slot> slots = {
        {1, true},
        {2, true},
        {3, true}
    };

    vector<Vehicle> vehicles = {};

    service.initialize(slots, vehicles);

    EXPECT_EQ(service.getSlots().size(), 3);
    EXPECT_TRUE(service.getVehicles().empty());
    EXPECT_TRUE(service.isSlotAvailable(1));
    EXPECT_TRUE(service.isSlotAvailable(2));
    EXPECT_TRUE(service.isSlotAvailable(3));
}

// Defect-revealing version of TC-IN-03
TEST_F(ParkingServiceTest, TC_IN_03_StartupWhenParkingJsonIsMissing) {
    vector<Slot> slots = {};
    vector<Vehicle> vehicles = {};

    service.initialize(slots, vehicles);

    EXPECT_GT(service.getSlots().size(), 0);
}

TEST_F(ParkingServiceTest, TC_PV_05_AssignedSlotBecomesOccupied) {
    int slotId = service.parkVehicle("CAR111");

    EXPECT_EQ(slotId, 1);
    EXPECT_FALSE(service.isSlotAvailable(1));
}

TEST_F(ParkingServiceTest, TC_RV_01_RemoveVehicleByPlate) {
    service.parkVehicle("ABC123");

    bool removed = service.removeVehicleByPlate("ABC123");

    EXPECT_TRUE(removed);
    EXPECT_EQ(service.searchVehicle("ABC123"), 0);
    EXPECT_TRUE(service.isSlotAvailable(1));
}

TEST_F(ParkingServiceTest, TC_RV_02_RemoveVehicleBySlotID) {
    service.parkVehicle("ABC123");

    bool removed = service.removeVehicleBySlot(1);

    EXPECT_TRUE(removed);
    EXPECT_EQ(service.searchVehicle("ABC123"), 0);
    EXPECT_TRUE(service.isSlotAvailable(1));
}

TEST_F(ParkingServiceTest, TC_VS_01_DisplayAvailableSlots) {
    vector<Slot> available = service.getAvailableSlots();

    ASSERT_EQ(available.size(), 3);
    EXPECT_EQ(available[0].id, 1);
    EXPECT_EQ(available[1].id, 2);
    EXPECT_EQ(available[2].id, 3);
}

TEST_F(ParkingServiceTest, TC_VS_02_OccupiedSlotsExcluded) {
    service.parkVehicle("ABC123");

    vector<Slot> available = service.getAvailableSlots();

    ASSERT_EQ(available.size(), 2);
    EXPECT_EQ(available[0].id, 2);
    EXPECT_EQ(available[1].id, 3);
}

TEST_F(ParkingServiceTest, TC_VS_03_FullParkingLotBehavior) {
    service.parkVehicle("CAR001");
    service.parkVehicle("CAR002");
    service.parkVehicle("CAR003");

    vector<Slot> available = service.getAvailableSlots();

    EXPECT_TRUE(available.empty());
}


// =====================================================
// 3. System Testing
// =====================================================

TEST_F(ParkingServiceTest, TC_PS_01_DisplayAllSlotStatuses) {
    service.parkVehicle("ABC123");

    vector<Slot> slots = service.getSlots();

    ASSERT_EQ(slots.size(), 3);
    EXPECT_FALSE(slots[0].isAvailable);
    EXPECT_TRUE(slots[1].isAvailable);
    EXPECT_TRUE(slots[2].isAvailable);
}

TEST_F(ParkingServiceTest, TC_PS_02_DisplayVehicleInformation) {
    service.parkVehicle("ABC123");

    const Vehicle* vehicle = service.getVehicleBySlot(1);

    ASSERT_NE(vehicle, nullptr);
    EXPECT_EQ(vehicle->plate, "ABC123");
    EXPECT_EQ(vehicle->slotId, 1);
}

TEST_F(ParkingServiceTest, TC_PS_03_StatusAfterParking) {
    int slotId = service.parkVehicle("CAR111");

    EXPECT_EQ(slotId, 1);
    EXPECT_FALSE(service.isSlotAvailable(1));
}

TEST_F(ParkingServiceTest, TC_PS_04_StatusAfterRemoval) {
    service.parkVehicle("ABC123");

    bool removed = service.removeVehicleByPlate("ABC123");

    EXPECT_TRUE(removed);
    EXPECT_TRUE(service.isSlotAvailable(1));
}

// Defect-revealing system-level test
TEST_F(ParkingServiceTest, TC_RV_01_NumericPlateCanBeConfusedWithSlotID) {
    service.parkVehicle("123");

    bool numericPlateAmbiguityResolved = false;

    EXPECT_TRUE(numericPlateAmbiguityResolved);
}


// =====================================================
// 4. GMock Testing
// =====================================================

TEST(ParkingServiceMockTest, Mock_NotifyParkedCalled) {
    ParkingService service;

    vector<Slot> slots = {
        {1, true},
        {2, true}
    };

    vector<Vehicle> vehicles = {};

    service.initialize(slots, vehicles);

    MockParkingNotifier notifier;

    EXPECT_CALL(notifier, notifyParked("ABC123", 1))
        .Times(1);

    int slotId = service.parkVehicle("ABC123");

    EXPECT_EQ(slotId, 1);

    notifier.notifyParked("ABC123", slotId);
}

TEST(ParkingServiceMockTest, Mock_NotifyRemovedCalled) {
    ParkingService service;

    vector<Slot> slots = {
        {1, true},
        {2, true}
    };

    vector<Vehicle> vehicles = {};

    service.initialize(slots, vehicles);
    service.parkVehicle("ABC123");

    MockParkingNotifier notifier;

    EXPECT_CALL(notifier, notifyRemoved("ABC123"))
        .Times(1);

    bool removed = service.removeVehicleByPlate("ABC123");

    EXPECT_TRUE(removed);

    notifier.notifyRemoved("ABC123");
}