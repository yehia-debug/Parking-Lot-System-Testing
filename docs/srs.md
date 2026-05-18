**System Requirements Specifications: Parking Lot Console System**

------------------------------------------------------------------------

**1. Introduction**

**1.1 Purpose**

This document specifies the functional and non-functional requirements
for a **C++ Console-based Parking Lot System**. The system provides a
standalone interface for managing vehicle parking and tracking slot
availability using a local file-based database.

------------------------------------------------------------------------

**1.2 System Scope**

The system is a simplified standalone utility focusing on **parking
operations management**. It allows a parking attendant to manage vehicle
entries, exits, and slot availability.

The system:

- Does not include authentication or multi-user roles

- Uses a local JSON file for persistence

- Focuses on simplicity, clarity, and maintainability

------------------------------------------------------------------------

**2. Functional Requirements**

**Actor: Parking Attendant**

------------------------------------------------------------------------

**2.1 System Initialization**

**FR-IN-01:** The system shall load all parking slots and parked vehicle
data from the local JSON file at startup.

**FR-IN-02:** If the file does not exist, the system shall initialize an
empty parking state.

------------------------------------------------------------------------

**2.2 Main Menu**

**FR-MM-01:** Upon startup, the system shall present the following
options:

- Park Vehicle

- Remove Vehicle

- View Available Slots

- Search Vehicle

- View Parking Status

- Exit

------------------------------------------------------------------------

**2.3 Park Vehicle**

**FR-PV-01:** The user shall enter vehicle details (e.g., license plate
number).

**FR-PV-02:** The system shall assign an available parking slot.

**FR-PV-03:** The system shall update the slot status to occupied.

**FR-PV-04:** The system shall store the parking record and persist it
to the JSON file.

------------------------------------------------------------------------

**2.4 Remove Vehicle**

**FR-RV-01:** The user shall select a vehicle by license plate or slot
ID.

**FR-RV-02:** The system shall free the associated parking slot.

**FR-RV-03:** The system shall remove the vehicle record and persist
changes.

------------------------------------------------------------------------

**2.5 View Available Slots**

**FR-VS-01:** The system shall display all available parking slots.

------------------------------------------------------------------------

**2.6 Search Vehicle**

**FR-SV-01:** The user shall input a vehicle license plate.

**FR-SV-02:** The system shall return the corresponding parking slot if
found.

------------------------------------------------------------------------

**2.7 View Parking Status**

**FR-PS-01:** The system shall display all parking slots with their
status (Available / Occupied).

**FR-PS-02:** Occupied slots shall display the associated vehicle
information.

------------------------------------------------------------------------

**3. Non-Functional Requirements**

**3.1 Persistence & Reliability**

**NFR-REL-01:** All parking data must be stored in a local parking.json
file using *nlohmann/json*.

**NFR-REL-02:** The system must ensure:

- A slot cannot be both available and occupied simultaneously

- A vehicle cannot occupy more than one slot

------------------------------------------------------------------------

**3.2 Usability**

**NFR-USA-01:** The system shall provide a simple and clear console
interface.

**NFR-USA-02:** The system shall validate all user inputs (invalid slot
IDs, duplicate vehicle entries).

------------------------------------------------------------------------

**3.3 Design Constraints**

**NFR-CON-01:** The codebase must be implemented in C++ and remain under
approximately **500 lines of code**.

**NFR-CON-02:** The system shall be divided into a maximum of **5
logical modules**.

**NFR-CON-03:** The system shall be console-based only.

------------------------------------------------------------------------

**3.4 Technical Constraints**

**NFR-TECH-01:** The system shall use C++11 or later.

**NFR-TECH-02:** The system shall use *nlohmann/json* for persistence.

**NFR-TECH-03:** The system shall avoid advanced C++ features such as:

- Complex templates

- Metaprogramming

- Advanced inheritance

------------------------------------------------------------------------

**3.5 Testability**

**NFR-TST-01:** The business logic shall be independent of the console
interface.

**NFR-TST-02:** The logic layer shall be unit-testable without file or
UI dependencies.

------------------------------------------------------------------------

**4. System Specifications**

**4.1 Module Structure**

<table style="width:82%;">
<colgroup>
<col style="width: 22%" />
<col style="width: 59%" />
</colgroup>
<thead>
<tr>
<th><strong>Module Name</strong></th>
<th><strong>Responsibility</strong></th>
</tr>
</thead>
<tbody>
<tr>
<td><strong>ParkingConsole</strong></td>
<td>Handles UI loop, menu display, and user interaction</td>
</tr>
<tr>
<td><strong>ParkingService</strong></td>
<td>Manages business logic (parking, removal, validation)</td>
</tr>
<tr>
<td><strong>ParkingRepository</strong></td>
<td>Handles JSON file operations</td>
</tr>
<tr>
<td><strong>Slot</strong></td>
<td>Data model representing a parking slot</td>
</tr>
<tr>
<td><strong>Vehicle</strong></td>
<td>Data model representing a vehicle</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

**4.2 Data Model (JSON Schema)**

{\
"slots": \[\
{\
"id": 1,\
"isAvailable": true\
}\
\],\
"vehicles": \[\
{\
"plate": "ABC123",\
"slotId": 1\
}\
\]\
}

------------------------------------------------------------------------

**4.3 Technical Standards**

- **Language:** C++11 or later

- **Libraries:**

  - *nlohmann/json* for persistence

- **Data Structures:**

  - std::vector for storing slots and vehicles

  - std::string for license plate

------------------------------------------------------------------------

**4.4 Development Constraints for Code Minimalism and Simplicity**

- Favor simple and direct implementations

- Avoid unnecessary abstractions

- Maintain strict separation between:

  - Presentation layer

  - Logic layer

  - Data layer

- Keep total LOC within ~500 lines

- Avoid advanced features such as:

  - Complex design patterns

  - Heavy template usage

  - Over-engineering

The resulting system should be:

- Easy to understand

- Easy to maintain

- Highly testable
