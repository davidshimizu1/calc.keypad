# Custom Dual-Radio Calculator & Bluetooth HID Macropad

<img width="2496" height="1696" alt="picture123" src="https://github.com/user-attachments/assets/80da3b0b-101f-4b8c-ab5f-07199e314ca6" />

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
| Keys | 25 low-profile mechanical switches |
| Battery | LiPo with onboard charging circuit |
| PCB | Custom 4-layer, designed in Altium Designer |
| Enclosure | Multi-part 3D printed (add filament here) |
| Display Module | (add part number here) |

### PCB Design
- 4-layer stackup with dedicated power plane
- RF keep-out zones around ESP32-S3 antenna to prevent detuning
- Impedance-matched traces for stable dual-radio (Wi-Fi/BLE) performance
- Integrated LiPo charging circuit

📁 Altium design files available in `/hardware`

---

## Firmware Architecture

The firmware is structured as a **main file + multiple custom libraries**, each handling a distinct subsystem:

```
/
├── main/
│   └── main.cpp          # Entry point, task orchestration
├── lib/
│   ├── calculator/       # Scientific calculator logic
│   ├── macropad/         # BLE HID profile & macro management
│   ├── weather/          # OpenWeatherMap REST API client
│   ├── display/          # UART HMI display & GUI state machine
│   └── keymatrix/        # Interrupt-driven switch matrix scanner
```

### Key Design Decisions
- **Non-blocking architecture** — Wi-Fi REST requests and BLE HID run concurrently without latency interference
- **Interrupt-driven matrix scanning** — Achieves <4ms HID response time while minimizing CPU overhead
- **Deep-sleep optimization** — Reduces idle power draw to extend battery life
- **Modular state machine** — GUI toggles cleanly between calculator and macropad modes

---

## Getting Started

### Prerequisites
- [PlatformIO](https://platformio.org/) (recommended) or Arduino IDE with ESP32-S3 board support
- OpenWeatherMap API key (free tier works)

### Setup
1. Clone the repository
```bash
git clone https://github.com/davidshimizu1/your-repo-name.git
cd your-repo-name
```

2. Copy the config template and fill in your credentials
```cpp
// config.h
#define WIFI_SSID       "your_ssid"
#define WIFI_PASSWORD   "your_password"
#define OWM_API_KEY     "your_openweathermap_key"
#define OWM_CITY        "San Diego"
#define OWM_UNITS       "imperial"  // or "metric"
```

3. Flash to your ESP32-S3
```bash
pio run --target upload
```

### Customizing Macros
Macros are defined in `lib/macropad/macros.h`. Each key can be bound to any HID keycode or macro sequence:
```cpp
// Example macro binding
MACRO_MAP(
    KEY(HID_KEY_CTRL, HID_KEY_C),   // Copy
    KEY(HID_KEY_CTRL, HID_KEY_V),   // Paste
    // ...
);
```

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
├── hardware/           # Altium PCB & schematic files
├── mechanical/         # Fusion 360 enclosure files (.f3d, .stl)
├── main/               # Main firmware entry point
├── lib/                # Custom libraries
└── README.md
```

---

## Built With
- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/) / PlatformIO
- [Altium Designer](https://www.altium.com/) — PCB design
- [Fusion 360](https://www.autodesk.com/products/fusion-360/) — Enclosure design
- [OpenWeatherMap API](https://openweathermap.org/api) — Weather data

---

## Author
**David Shimizu**
[LinkedIn](https://linkedin.com/in/davidshimizu) · [GitHub](https://github.com/davidshimizu1)


![IMG_0332](https://github.com/user-attachments/assets/3b640d5e-4a3a-493a-8fa4-46986a46d832)


https://github.com/user-attachments/assets/d92eaae9-ccc6-4540-ab36-3ccdf94c4ab0



https://github.com/user-attachments/assets/1930882c-5ee2-4487-85e7-eceab5c94025

![comparison](https://github.com/user-attachments/assets/92db343a-2714-455a-88ce-03647a39ccdb)

![sidecomparison](https://github.com/user-attachments/assets/7a27574d-f005-4f37-92e9-b8760f2ecc49)
