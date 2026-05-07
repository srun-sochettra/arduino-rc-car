# 🏎️ Arduino Bluetooth RC Car

A lightweight, high-performance Arduino firmware designed to control a 2-wheel drive (2WD) robotic car via Bluetooth or Serial communication. This project was developed as part of the **University ARP (Arduino Programming)** curriculum.

---

## 🚀 Overview

This firmware implements a robust command-processing engine that translates Serial signals into precise motor movements. By utilizing a simple character-based protocol, the car can be controlled via a smartphone app, computer serial monitor, or any Bluetooth-enabled device.

## ✨ Key Features

- **Binary Motor Logic**: High-speed switching between Forward, Reverse, and Stop states.
- **Diagonal Steering**: Dedicated handlers for diagonal movements (`G`, `I`, `H`, `J`).
- **Safety First**: Automatic "Stop" logic for unrecognized commands or serial timeouts.
- **Optimized Footprint**: Uses `constexpr` for pin definitions and `inline` functions to reduce execution overhead.

## 🛠️ Tech Stack

- **Microcontroller**: Arduino (Atmega328P based boards like Uno/Nano recommended).
- **Motor Driver**: L298N, L293D, or similar H-Bridge modules.
- **Communication**: HC-05/HC-06 Bluetooth Module (Serial UART).
- **Tooling**: Arduino IDE 2.0+, C++11.

---

## 🔌 Hardware Architecture

### Pin Mapping

| Component | Arduino Pin | Function | Logic |
|-----------|-------------|----------|-------|
| **L1**    | 13          | Left Motor A | `HIGH` = Forward |
| **L2**    | 12          | Left Motor B | `HIGH` = Reverse |
| **R1**    | 11          | Right Motor A | `HIGH` = Forward |
| **R2**    | 10          | Right Motor B | `HIGH` = Reverse |

### Data Flow Diagram

```mermaid
graph LR
    A[Smartphone App] -- Bluetooth --> B[HC-05 Module]
    B -- Serial 9600 bps --> C[Arduino Uno]
    C -- Digital Signal --> D[Motor Driver]
    D -- Power --> E[DC Motors]
```

---

## 🎮 Command Protocol

The firmware listens for ASCII characters at **9600 baud**. Below is the mapping of characters to physical movements:

| Char | Action | Motor Logic (L, R) |
|:----:|:-------|:-------------------|
| `F`  | Forward | (FWD, FWD) |
| `B`  | Backward | (REV, REV) |
| `L`  | Left | (STOP, FWD) |
| `R`  | Right | (FWD, STOP) |
| `G`  | Forward-Right* | (FWD, STOP) |
| `I`  | Forward-Left* | (STOP, FWD) |
| `H`  | Back-Left | (REV, STOP) |
| `J`  | Back-Right | (STOP, REV) |
| `S`/`D` | Stop | (STOP, STOP) |

*\*Note: In this implementation, 'G' and 'R' trigger the same movement (Left motor only), while 'I' and 'L' trigger the same movement (Right motor only).*

---

## 🔧 Installation & Setup

### 1. Circuit Assembly
1. Connect the **L298N Motor Driver** pins 10, 11, 12, and 13 to the Arduino.
2. Connect your 7V-12V battery pack to the L298N power input.
3. Wire the Bluetooth module:
   - **VCC** → 5V
   - **GND** → GND
   - **TX** → Arduino **RX (Pin 0)**
   - **RX** → Arduino **TX (Pin 1)**

### 2. Uploading Code
> [!WARNING]
> **IMPORTANT:** You must disconnect the Bluetooth module's RX and TX wires from the Arduino before clicking "Upload". Failure to do so will result in an `avrdude: stk500_getsync()` error.

1. Open `RC_Car.ino` in your Arduino IDE.
2. Select **Tools > Board > Arduino Uno**.
3. Select the correct **Port**.
4. Click **Upload**.
5. Reconnect the Bluetooth wires.

### 3. Pairing and Control
1. Power on the car. The Bluetooth LED should blink rapidly.
2. Search for "HC-05" or "HC-06" on your phone.
3. Pair using `1234` or `0000`.
4. Use the **"Arduino Bluetooth RC Car"** app (or any terminal app) to send commands.

---

## 🧠 Code Breakdown

### `setMotor(uint8_t a, uint8_t b, Dir d)`
This inline function handles the H-bridge logic. It ensures that both pins of a motor are never `HIGH` at the same time, preventing short circuits in the driver.

### `handle(char c)`
The core switch-case logic that parses serial input. It ignores speed commands (`0-9`, `q`) to maintain compatibility with apps that send analog speed data, while executing the digital direction commands.

---

## 📜 License & Acknowledgments

- Developed for **NUM University** (Year 2, Semester 1).
- Based on standard Bluetooth RC car protocols.
- Free to use for educational purposes.
