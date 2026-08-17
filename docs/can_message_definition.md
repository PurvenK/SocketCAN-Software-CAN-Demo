# CAN Message Definition

## CAN Frame Structure

A CAN frame contains:

- CAN Identifier (CAN ID)
- Data Length Code (DLC)
- Data Payload

## Message Mapping

| CAN ID | Signal | Data Length | Range |
|--------|--------|-------------|-------|
| 0x100 | Vehicle Speed | 1 byte | 0-120 km/h |
| 0x101 | Engine RPM | 2 bytes | 800-5000 rpm |
| 0x102 | Coolant Temperature | 1 byte | 20-120 °C |

## Signal Encoding

### Vehicle Speed

CAN ID:
