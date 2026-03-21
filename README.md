# Custom Calculator & Bluetooth Macropad

<img width="1200" height="712" alt="12312312" src="https://github.com/user-attachments/assets/a353e855-2876-48ad-b29b-a769eaac16ca" />

A portable 25-key embedded device built around the **ESP32-S3-WROOM-1-N8R8**, combining a scientific calculator, a fully customizable Bluetooth HID macropad, and real-time weather display — all on a single custom PCB with a 3D-printed enclosure.

---

## Features
- **Scientific Calculator** — Full expression evaluation via custom GUI
- **Bluetooth HID Macropad** — 25 keys with 47 fully customizable macro bindings via BLE
- **Real-Time Weather** — Fetches live temperature data from OpenWeatherMap over Wi-Fi
- **Dual-Radio** — Simultaneous Wi-Fi and BLE operation on a single board
- **3.5" HMI Display** — 480×320 touchscreen driven via UART with mode switching
- **LiPo Battery** — Onboard charging circuit with deep-sleep power optimization
- **<4ms HID Latency** — Interrupt-driven key matrix scanning for instantaneous input

---


---

## Demo

### Calculator Mode
https://github.com/user-attachments/assets/d92eaae9-ccc6-4540-ab36-3ccdf94c4ab0

### Macropad Mode
https://github.com/user-attachments/assets/1930882c-5ee2-4487-85e7-eceab5c94025

---

## Hardware

### Core Components
| Component | Details |
|-----------|---------|
| MCU | ESP32-S3-WROOM-1-N8R8 (8MB Flash, 8MB PSRAM) |
| Display | 3.5" 480×320 HMI (UART) |
| Switches | Kalih Choc V1 Ambient Silent |
| Battery | 1000mAh LiPo battery|
| PCB | Custom 4-layer, designed in Altium Designer |
| Enclosure | Multi-part 3D printed (PA12-HP Nylon) |
| Display Module | https://www.buydisplay.com/3-5-inch-480x320-hmi-intelligent-smart-uart-spi-touch-ips-tft-lcd-display |
| *All PCB and 3D printed parts from JLCPCB.com |

### PCB Design
- 4-layer stackup with dedicated power and ground planes
- RF keep-out zones around ESP32-S3 antenna to prevent detuning
- Integrated LiPo charging circuit

📁 Altium design files available in `/PCB`

---

## Firmware Architecture

The firmware is structured as a **main file + multiple custom libraries**, each handling a distinct subsystem:

```
/
├── src/
│   └── main.cpp              # Main file, calls the libraries
├── lib/
│   ├── Calculator/           # Scientific calculator logic
│   ├── Keypad/               # Scans key matrix & BLE HID profile 
│   ├── NetworkManagement/    # Handles, BLE, WiFi, weather, and time
│   ├── Display/              # UART HMI display & GUI state machine
│   └── PowerManagement/      # Handles power management
├── lib/
│   ├── Config/               # Contains pin definitions, addresses and variables
```

### Key Design Decisions
- **Non-blocking architecture** — Wi-Fi REST requests and BLE HID run concurrently without latency interference
- **Interrupt-driven matrix scanning** — Achieves <4ms HID response time while minimizing CPU overhead
- **Deep-sleep optimization** — Reduces idle power draw to extend battery life
- **Modular state machine** — GUI toggles cleanly between calculator and macropad modes

---

## Technical Highlights

### RF Design
The ESP32-S3-WROOM-1 module requires careful PCB layout to maintain antenna performance. This design implements:
- Localized copper keep-out zones beneath the module antenna
- Dedicated RF ground plane on inner layer 2
- Physical separation of noisy switching circuits from the RF section

### Power Management
- Deep-sleep triggered after configurable idle timeout
- LiPo charging via onboard circuit (add IC part number here)
- Interrupt-driven wake from any keypress

### Display Communication
The HMI display is driven over UART using a custom GUI subsystem that manages two distinct screen states — calculator mode and macropad mode — with clean transitions between them.

---

## Project Structure
```
/
├── 3D_models/          # Fusion 360 CAD files (.step, .stl)
├── Code/               # All code for project
├── fab/                # fabrication files for PCB production
├── pcb/                # Schematic and PCB files
└── README.md
```

---

## Built With
- [Visual Studio Code](https://code.visualstudio.com/) / PlatformIO
- [Altium Designer](https://www.altium.com/) — PCB design
- [Fusion 360](https://www.autodesk.com/products/fusion-360/) — Enclosure design
- [UI Editor](https://www.buydisplay.com/3-5-inch-480x320-hmi-intelligent-smart-uart-spi-touch-ips-tft-lcd-display) - Design UI (specific for this display)
- [OpenWeatherMap API](https://openweathermap.org/api) — Weather data

---

## Author
**David Shimizu**
[LinkedIn](https://linkedin.com/in/davidshimizu) · [GitHub](https://github.com/davidshimizu1)

<!--
![IMG_0332](https://github.com/user-attachments/assets/3b640d5e-4a3a-493a-8fa4-46986a46d832)


https://github.com/user-attachments/assets/d92eaae9-ccc6-4540-ab36-3ccdf94c4ab0



https://github.com/user-attachments/assets/1930882c-5ee2-4487-85e7-eceab5c94025

![comparison](https://github.com/user-attachments/assets/92db343a-2714-455a-88ce-03647a39ccdb)

![sidecomparison](https://github.com/user-attachments/assets/7a27574d-f005-4f37-92e9-b8760f2ecc49)
-->
