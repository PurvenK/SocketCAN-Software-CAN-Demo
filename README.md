# SocketCAN Software-Only CAN Communication Demo

## Overview

This project demonstrates a software-only CAN communication network using Linux SocketCAN without requiring physical CAN hardware.

A virtual CAN interface (`vcan0`) is used to simulate a real CAN bus. The implementation is developed in **C language** using the Linux SocketCAN API.

The system consists of three software ECU nodes:

- Vehicle ECU (CAN Transmitter)
- Dashboard ECU (CAN Receiver)
- Logger ECU (CAN Traffic Monitor)

The project demonstrates CAN communication, message decoding, filtering, traffic logging, diagnostics, and CAN FD concepts.

---

# System Architecture

```
                 +----------------+
                 |  Vehicle ECU   |
                 +----------------+
                         |
                         |
                      vcan0
                         |
          +--------------+--------------+
          |                             |
 +----------------+          +----------------+
 | Dashboard ECU  |          |   Logger ECU   |
 +----------------+          +----------------+
```

The virtual CAN interface (`vcan0`) acts as the communication bus. Multiple applications can communicate and monitor the same CAN traffic simultaneously.

---

# Project Structure

```
SocketCAN-Software-CAN-Demo
│
├── src
│   ├── vehicle_ecu.c
│   ├── dashboard_ecu.c
│   └── logger_ecu.c
│
├── docs
│   ├── socketcan_summary.md
│   ├── can_message_definition.md
│   ├── architecture.md
│   └── report.md
│
├── screenshots
│   ├── vehicle_ecu.png
│   ├── dashboard_output.png
│   ├── logger_output.png
│   └── candump_output.png
│
└── README.md
```

---

# Software Requirements

## Operating System

- Ubuntu Linux

## Required Packages

Install CAN utilities and compiler:

```bash
sudo apt update

sudo apt install can-utils gcc
```

---

# Creating Virtual CAN Interface

Load the virtual CAN driver:

```bash
sudo modprobe vcan
```

Create the virtual CAN interface:

```bash
sudo ip link add dev vcan0 type vcan
```

Enable the interface:

```bash
sudo ip link set up vcan0
```

Verify:

```bash
ip link show vcan0
```

---

# CAN Message Definition

The system uses standard 11-bit CAN identifiers.

| CAN ID | Signal | Data Length | Range |
|---|---|---|---|
| 0x100 | Vehicle Speed | 1 Byte | 0-120 km/h |
| 0x101 | Engine RPM | 2 Bytes | 800-5000 rpm |
| 0x102 | Coolant Temperature | 1 Byte | 20-120 °C |

---

# Software Nodes

## 1. Vehicle ECU

File:

```
src/vehicle_ecu.c
```

Functions:

- Generates vehicle parameters
- Creates CAN frames
- Transmits messages on vcan0

Transmitted signals:

- Vehicle Speed
- Engine RPM
- Coolant Temperature

---

## 2. Dashboard ECU

File:

```
src/dashboard_ecu.c
```

Functions:

- Receives CAN frames
- Decodes CAN IDs
- Displays vehicle information
- Detects communication loss

Example output:

```
--------------------------------
Vehicle Dashboard
--------------------------------
Speed       : 65 km/h
Engine RPM  : 2450 rpm
Temperature : 88 C
--------------------------------
```

---

## 3. Logger ECU

File:

```
src/logger_ecu.c
```

Functions:

- Captures CAN traffic
- Stores CAN frames
- Records:
  - Timestamp
  - CAN ID
  - DLC
  - Payload

Output file:

```
can_log.csv
```

---

# Compilation

Navigate to the source folder:

```bash
cd src
```

Compile Vehicle ECU:

```bash
gcc vehicle_ecu.c -o vehicle_ecu
```

Compile Dashboard ECU:

```bash
gcc dashboard_ecu.c -o dashboard_ecu
```

Compile Logger ECU:

```bash
gcc logger_ecu.c -o logger_ecu
```

---

# Running the Demonstration

Open four terminals.

## Terminal 1 - Vehicle ECU

```bash
./vehicle_ecu
```

The Vehicle ECU starts transmitting CAN messages.

---

## Terminal 2 - Dashboard ECU

```bash
./dashboard_ecu
```

The Dashboard displays decoded vehicle data.

---

## Terminal 3 - Logger ECU

```bash
./logger_ecu
```

The Logger records CAN traffic into `can_log.csv`.

---

## Terminal 4 - CAN Traffic Monitoring

```bash
candump vcan0
```

Displays all CAN frames transmitted on the virtual CAN network.

---

# Features Demonstrated

## SocketCAN Communication

- Software CAN network without hardware
- Linux SocketCAN API usage
- CAN frame transmission and reception

---

## Message Filtering

The system supports CAN ID based filtering.

Examples:

Speed message:

```
CAN ID: 0x100
```

RPM message:

```
CAN ID: 0x101
```

---

## Traffic Logging

The Logger ECU records all observed CAN traffic.

Stored information:

- Timestamp
- Message Identifier
- Payload Length
- Payload Data

---

## Unknown Message Detection

An unknown CAN message can be injected:

```bash
cansend vcan0 200#AABBCCDD
```

Observation:

- Logger ECU records the message
- Dashboard ECU ignores unsupported messages

---

## Transmission Rate Study

Different transmission rates can be tested by changing the delay in Vehicle ECU.

Example:

```c
sleep(1);
```

Faster transmission:

```c
usleep(100000);
```

Observations:

- Faster updates
- Increased log file size
- Increased processing requirement

---

## Node Failure Detection

When the Vehicle ECU is stopped:

- Dashboard stops receiving updates
- Logger receives no new messages
- Communication loss can be detected

Example:

```
WARNING: Vehicle ECU Offline
```

---

# CAN FD Exploration

CAN FD extends Classical CAN capabilities.

| Feature | Classical CAN | CAN FD |
|---|---|---|
| Maximum Payload | 8 bytes | 64 bytes |
| Data Rate | Lower | Higher |
| Efficiency | Lower | Higher |

Benefits:

- Larger payload size
- Improved communication efficiency
- Suitable for modern automotive networks

---

# Learning Outcomes

After completing this project:

- Understood Linux SocketCAN architecture
- Implemented CAN communication in C
- Created software-only CAN nodes
- Developed CAN transmitter and receiver applications
- Implemented CAN traffic logging
- Explored CAN filtering and diagnostics
- Studied CAN FD improvements

---

# Documentation

Additional documentation is available in the `docs` folder:

- SocketCAN Overview
- CAN Message Definition
- System Architecture
- Technical Report

---

# Author

Purven Khadke
