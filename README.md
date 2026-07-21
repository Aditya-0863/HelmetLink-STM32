# HelmetLink — STM32

Smart motorcycle helmet with Bluetooth 5.1 audio, crash detection, and automatic emergency calling.

## Features
- [x] Bare-metal GPIO, UART, and power management on STM32G071RB
- [ ] HAL I2C MPU6050 accelerometer
- [ ] Crash detection algorithm
- [ ] Bluetooth audio streaming (A2DP) + calls (HFP)
- [ ] Automatic emergency call via HFP dial on crash
- [ ] Sub-50µA STOP mode standby
- [ ] Custom 2-layer PCB in KiCad

## Hardware
| Component | Role |
|-----------|------|
| STM32G071RB | Main MCU (Nucleo for dev, custom PCB for final) |
| Feasycom BT1026X | Bluetooth 5.1 audio module (A2DP + HFP) |
| MPU6050 | 6-axis IMU for crash detection |
| PAM8403 | Class D audio amplifier |
| OneOdio driver | Helmet speaker (repurposed headphone) |
| TP4056 + AMS1117-3.3 | Battery charging and regulation |

## Progress
| Block | Feature | Status |
|-------|---------|--------|
| 01 | Bare-metal GPIO blink + button | ✅ |
| 02 | Bare-metal UART printf | ⬜ |
| 03 | MPU6050 I2C read | ⬜ |
| 04 | Crash detection | ⬜ |
| 05 | BT1026X control + AT commands | ⬜ |
| 06 | Sleep modes + current measure | ⬜ |
| 07 | Final integration | ⬜ |


## Demo
*(Coming after completion)*

