# SocketCAN Overview

## What is SocketCAN?

SocketCAN is a Linux framework that allows CAN communication using the standard networking architecture of Linux.

It provides CAN interfaces similar to Ethernet or Wi-Fi interfaces. Applications communicate with CAN networks using sockets.

## Why is CAN treated as a network interface?

Linux represents CAN as a network interface because CAN communication is based on message exchange between multiple nodes. This allows existing networking concepts such as sockets, filtering, and monitoring tools to be used.

## Difference from vendor-specific CAN APIs

Vendor-specific APIs depend on individual CAN hardware manufacturers. SocketCAN provides a common Linux interface independent of hardware vendors.

## Advantages

- Standard programming interface
- Multiple applications can access CAN traffic simultaneously
- Easy debugging using Linux tools
- Supports real and virtual CAN networks
- Allows software testing before hardware availability
