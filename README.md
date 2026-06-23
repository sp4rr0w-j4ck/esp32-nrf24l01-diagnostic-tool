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
* Stable 3.3V power supply (Recommended: LM2596 Buck Converter)
* 100µF Electrolytic Capacitor

### ⚡ Critical Hardware Stability Tips
1. The 100µF Capacitor Fix : Solder or firmly press a **100µF electrolytic capacitor** directly across the `VCC` and `GND` pins right on the nRF24L01 module. This acts as a vital power reservoir to handle sharp electrical spikes. 100µF Electrolytic Capacitor
2. **Watch the Polarity:** Because it is an electrolytic capacitor, it is directional! Ensure the stripe with the **minus symbols (`-`)** connects to the **GND** pin, and the plain/longer leg connects to the **VCC** pin. 
3. **Common Ground:** If you power the nRF module via an external buck converter, you **must** connect a ground wire from the converter's `GND` line to one of the ESP32's `GND` pins. Without a common ground, the SPI data lines will float randomly, returning endless `0xFF` errors. 

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
MIT License

Copyright (c) 2026 sp4rr0w.j4ck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
1. Open the sketch in Arduino IDE.
2. Select your ESP32 board.
3. Upload the code.
4. Open Serial Monitor.
5. Set baud rate to **115200**.
6. Observe the diagnostic result.

---
## License

This project is licensed under the MIT License - see the LICENSE file for details.
## Purpose

This project was created to quickly verify whether an nRF24L01 module is correctly connected and responding before integrating it into larger wireless communication projects.

## License

MIT License
