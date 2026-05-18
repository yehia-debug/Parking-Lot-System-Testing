Here is the improved QA/testing-focused README version:

````markdown
# Parking Lot System Testing Project

A complete software testing and quality assurance project performed on a C++ console-based Parking Lot Management System.

This repository focuses on testing activities rather than application development.
 The project demonstrates practical QA engineering techniques including static review, automated testing, manual system testing, defect reporting, and full test documentation.

The testing process covered:

* Static testing and review
* Test analysis and decision-table design
* Unit testing
* Integration testing
* System testing
* Automated testing using Google Test and Google Mock
* Manual console testing
* Dynamic execution logging
* Defect identification and reporting

---

# System Features Tested

The following functional areas were tested:

* Vehicle parking and removal
* Slot management
* Vehicle search
* Parking status monitoring
* Persistent JSON-based storage
* Console menu navigation
* Input validation behavior

---

# Testing Activities Performed

## Static Testing

The project included several static testing activities before execution:

* Requirements review
* UML/Class Diagram review
* Sequence Diagram review
* Source code review
* Test condition extraction
* Decision table analysis
* Test case design and reduction

## Dynamic Testing

Dynamic testing was performed through both automated and manual execution:

* Unit Testing
* Integration Testing
* System Testing
* Manual Console Testing
* Automated GTest/GMock Execution

---

# Technologies and Tools Used

| Technology / Tool   | Purpose                              |
| ------------------- | ------------------------------------ |
| C++                 | Tested application language          |
| Visual Studio       | IDE and execution environment        |
| Google Test (GTest) | Automated test execution             |
| Google Mock (GMock) | Mock object interaction testing      |
| nlohmann/json       | JSON file handling                   |
| Git & GitHub        | Version control and project hosting  |
| Excel               | Dynamic test execution logging       |
| Microsoft Word      | QA documentation and reporting       |

---

# Repository Structure

```text
Parking Lot System/
│
├── Parking Lot System.sln
├── src/
├── packages/
├── docs/
│   ├── Test Plan
│   ├── Static Review
│   ├── Test Design
│   ├── Test Implementation
│   ├── Dynamic Test Execution
│   └── Test Completion Report
│
├── parking.json
└── README.md
````

---

# Functional Areas Covered During Testing

## 1. System Initialization

* Loading parking slots from `parking.json`
* Loading existing vehicle records
* Startup behavior with missing or invalid storage files

## 2. Main Menu Navigation

* Console menu display verification
* Menu routing validation
* Invalid input handling

## 3. Park Vehicle

* Parking valid vehicles
* Rejecting duplicate vehicles
* Rejecting invalid license plate input
* Handling full parking scenarios

## 4. Remove Vehicle

* Removing vehicles using plate number
* Removing vehicles using slot ID
* Handling nonexistent vehicles or slots

## 5. View Available Slots

* Displaying available parking spaces
* Excluding occupied slots
* Handling fully occupied parking state

## 6. Search Vehicle

* Searching existing vehicles
* Searching nonexistent vehicles
* Case-insensitive search behavior

## 7. View Parking Status

* Displaying all slot states
* Displaying parked vehicle information
* Verifying state changes after parking/removal

---

# Automated Testing

Automated tests were implemented using Google Test and Google Mock.

### Areas Covered

* Initialization behavior
* Parking validation
* Duplicate parking rejection
* Slot occupancy updates
* Vehicle removal logic
* Search functionality
* Parking status behavior
* Mock interaction verification

### Example GTest Case

```cpp
TEST_F(ParkingServiceTest, TC_PV_01_ParkValidVehicle) {
    int slotId = service.parkVehicle("ABC123");

    EXPECT_EQ(slotId, 1);
    EXPECT_FALSE(service.isSlotAvailable(1));
}
```

---

# Defects Identified During Testing

The testing process intentionally included defect-revealing scenarios.

| Defect ID | Description                                                          |
| --------- | -------------------------------------------------------------------- |
| DEF-001   | Missing `parking.json` may initialize a parking system with no slots |
| DEF-002   | Invalid license plate formats such as `@@@@` are accepted            |
| DEF-003   | Numeric license plates may be confused with slot IDs during removal  |

---

# Test Documentation Included

This repository contains complete QA/testing artifacts:

* Test Plan
* Static Review Reports
* Test Conditions
* Decision Tables
* Reduced Decision Tables
* Test Case Design
* Test Implementation Procedures
* Dynamic Test Execution Logs
* Defect Reports
* Test Completion Report

---

# How to Run the Project

## Requirements

* Visual Studio with C++ Desktop Development
* NuGet enabled
* Same Visual Studio version used during testing

## Steps

1. Clone or download the repository
2. Open:

```text
Parking Lot System.sln
```

3. Restore NuGet packages if needed
4. Build the solution
5. Run the application

---

# Running Automated Tests

1. Open the solution in Visual Studio
2. Open:

```text
Test → Test Explorer
```

3. Build the test project
4. Run all tests

---

# Sample JSON Test Data

```json
{
  "slots": [
    { "id": 1, "isAvailable": true },
    { "id": 2, "isAvailable": false }
  ],
  "vehicles": [
    { "plate": "ABC123", "slotId": 2 }
  ]
}
```

---

# QA Practices Demonstrated

* Static Testing
* Dynamic Testing
* White-Box Testing
* Black-Box Testing
* Test Automation
* Decision Table Testing
* Boundary and Validation Testing
* Traceability Between Requirements and Tests
* Defect Reporting and Risk Analysis

---

# Future Testing Improvements

* Additional edge-case automation
* Better license plate validation rules
* Improved usability testing
* Continuous Integration (CI) test pipeline
* Performance and stress testing
* Expanded mock interaction coverage

---

# Project Purpose

This repository was created to demonstrate practical software testing, QA engineering, and test automation skills using a real C++ application and a complete end-to-end testing workflow.

```
```
