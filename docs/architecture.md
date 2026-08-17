# SocketCAN System Architecture

## Architecture Diagram
          +----------------+
          |  Vehicle ECU   |
          +----------------+
                   |
                   |
                vcan0
                   |
    +--------------+--------------+
    | Dashboard ECU | | Logger ECU |
    +----------------+ +----------+

    
## Explanation

The system uses Linux SocketCAN with a virtual CAN interface (vcan0).

### Vehicle ECU

- Generates vehicle data.
- Transmits CAN messages.
- Sends:
  - Vehicle speed
  - Engine RPM
  - Coolant temperature

### Dashboard ECU

- Receives CAN messages.
- Decodes CAN IDs.
- Displays vehicle information.

### Logger ECU

- Observes CAN traffic.
- Stores:
  - Timestamp
  - CAN ID
  - DLC
  - Payload data

## Virtual CAN Network

The vcan0 interface allows CAN communication without physical CAN hardware.

All applications connect to the same CAN interface and can observe CAN traffic simultaneously.
