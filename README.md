# HelmetLink — STM32
Smart motorcycle helmet with Bluetooth 5.1 audio, crash detection, and automatic emergency calling.

## Features
- [x] Bare-metal GPIO, UART, and power management on STM32G071RB
- [x] HAL I2C MPU6500 accelerometer
- [x] Crash detection algorithm
- [x] Bluetooth audio streaming (A2DP) + calls (HFP)
- [x] Automatic emergency call via HFP dial on crash
- [ ] Sub-50µA STOP mode standby
- [ ] Custom 2-layer PCB in KiCad

## Hardware
| Component | Role |
|-----------|------|
| STM32G071RB | Main MCU (Nucleo for dev, custom PCB for final) |
| Feasycom BT1026D | Bluetooth 5.1 audio module (A2DP + HFP) |
| MPU-6500 | 6-axis IMU for crash detection |
| MAX98306 | Class D audio amplifier (differential input, direct speaker drive) |
| Salvaged intercom harness (speaker/mic/button, USB-C shell) | Helmet speaker, mic, and button interface — repurposed |
| BQ24074 + TLV75733 | Battery charging with power-path management, and 3.3V regulation |

## Progress
| Block | Feature | Status |
|-------|---------|--------|
| 01 | Bare-metal GPIO blink + button | ✅ |
| 02 | Bare-metal UART printf | ✅ |
| 03 | MPU-6500 I2C read | ✅* |
| 04 | Crash detection | ✅* |
| 05 | BT1026D control + AT commands | ✅ |
| 06 | Sleep modes + current measure | ✅* |
| 07 | Final integration | ⬜ |

\* Written/tested against MPU-6050; pending re-verification on MPU-6500 hardware (register map is near-identical, minor differences expected in WHO_AM_I and scale config)

## Demo
*(Coming after completion)*
