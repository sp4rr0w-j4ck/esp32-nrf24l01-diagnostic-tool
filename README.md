# esp32-nrf24l01-diagnostic-tool
Simple ESP32-based diagnostic tool to verify SPI communication and health status of an NRF24L01 wireless transceiver module.



#

A lightweight diagnostic sketch for verifying communication between an ESP32 and an nRF24L01 wireless transceiver module.

## Features

* Tests SPI communication with the nRF24L01.
* Clears internal status flags before testing.
* Reads the module status register using a NOP command.
* Provides human-readable diagnostic output over Serial Monitor.
* Helps identify:

  * Successful communication
  * Wiring issues
  * Power supply problems
  * Unresponsive modules

---

## Hardware Requirements

* ESP32 Development Board
* nRF24L01 or nRF24L01+
* Jumper wires
* Stable 3.3V power supply (Recomend LM2596 Buck converter)

---

## Wiring

| nRF24L01 | ESP32   |
| -------- | ------- |
| VCC      | 3.3V    |
| GND      | GND     |
| CE       | GPIO 4  |
| CSN      | GPIO 5  |
| SCK      | GPIO 18 |
| MISO     | GPIO 19 |
| MOSI     | GPIO 23 |

> Note: Never power the nRF24L01 with 5V.

---

## Serial Output Example

```text
====================================
--- Starting nRF24L01 Module Test ---
====================================

Reading active module status...
Returned Status Byte: 0x0E

------------- DIAGNOSIS -------------
✅ MODULE HEALTHY & READY!
SPI lines are responsive and buffers are clear.
-------------------------------------
Done.
```

---

## Status Code Interpretation

| Status       | Meaning                                                         |
| ------------ | --------------------------------------------------------------- |
| 0x0E         | Module healthy and responding                                   |
| 0x00         | Module responding                                               |
| 0xFF         | SPI communication failure, wiring issue, or disconnected module |
| 0x03         | Possible power instability                                      |
| Other values | Module responding but requires further investigation            |

---[_ESP32_nRF24L01_Health_Check.zip](https://github.com/user-attachments/files/29261230/_ESP32_nRF24L01_Health_Check.zip)

## Usage

1. Open the sketch in Arduino IDE.
2. Select your ESP32 board.
3. Upload the code.
4. Open Serial Monitor.
5. Set baud rate to **115200**.
6. Observe the diagnostic result.

---

## Purpose

This project was created to quickly verify whether an nRF24L01 module is correctly connected and responding before integrating it into larger wireless communication projects.

## License

MIT License
