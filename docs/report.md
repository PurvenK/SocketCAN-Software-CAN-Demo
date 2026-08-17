# SocketCAN Software-Only CAN Communication Project Report

## 1. Objective

The objective of this project was to explore Linux SocketCAN and implement a software-only CAN communication network without physical CAN hardware.

A virtual CAN interface (`vcan0`) was used to simulate a CAN bus.

---

## 2. SocketCAN Investigation

SocketCAN is a Linux framework that integrates CAN communication into the Linux networking architecture.

Instead of using vendor-specific CAN APIs, applications communicate using standard socket interfaces.

Advantages:

- Hardware-independent communication
- Multiple applications can monitor the same CAN traffic
- Easy debugging using Linux tools
- Supports virtual CAN networks
- Enables software development before hardware availability

---

## 3. System Implementation

The system consists of three software nodes:

### Vehicle ECU

Responsible for transmitting:

- Vehicle Speed
- Engine RPM
- Coolant Temperature

### Dashboard ECU

Responsible for:

- Receiving CAN messages
- Decoding signals
- Displaying vehicle data
- Detecting ECU communication failure

### Logger ECU

Responsible for:

- Monitoring CAN traffic
- Recording timestamp, CAN ID, DLC and payload

---

## 4. CAN Message Mapping

| CAN ID | Signal | Size |
|---|---|---|
|0x100|Vehicle Speed|1 Byte|
|0x101|Engine RPM|2 Bytes|
|0x102|Coolant Temperature|1 Byte|

Standard 11-bit CAN identifiers were used.

---

## 5. Learning Challenge Results

### Traffic Observation

Multiple applications successfully received the same CAN messages simultaneously.

The Logger ECU operated without affecting communication.

---

### Message Filtering

CAN ID filtering was implemented.

Examples:

- Speed messages: `0x100`
- RPM messages: `0x101`

Filtering allowed applications to process only required messages.

---

### Unknown Message Detection

An undefined CAN message was transmitted.

Results:

- Logger recorded the message.
- Dashboard ignored the unsupported message.

---

### Transmission Rate Study

Increasing transmission frequency improved responsiveness but increased log size and CPU usage.

---

### Node Failure Detection

When the Vehicle ECU was stopped:

- Dashboard stopped updating values.
- Logger received no new messages.
- Offline warning was generated.

---

## 6. CAN FD Study

CAN FD extends Classical CAN by increasing payload capacity.

Comparison:

|Feature|CAN|CAN FD|
|-|-|-|
|Payload|8 bytes|64 bytes|

Benefits:

- Larger data transfer
- Improved efficiency
- Suitable for modern automotive networks

---

## 7. Conclusion

The project successfully demonstrated software-based CAN communication using SocketCAN.

The implementation showed that CAN applications can be developed, tested, and debugged without physical CAN hardware.

---

