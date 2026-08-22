Changelog — HelmetLink-STM32

Hardware BOM decisions and the reasoning behind each swap, in roughly chronological order.

Speaker

OneOdio headphone driver → C20 intercom speakers Original plan was to repurpose OneOdio headphone drivers (50mm), but the helmet's pre-molded speaker sockets are 40mm — the 50mm drivers physically don't fit. Switched to speakers salvaged from a BluArmor C20 intercom unit, sized correctly for the stock helmet sockets. Mic and buttons are also being salvaged from the same C20 harness (shared connector housing), rather than sourced separately.

Audio amplifier

PAM8403 → MAX98308(considered) → MAX98306 Initial assumption was that BT1026D's SPK_LN/LP/RN/RP pins were already amplified speaker-level outputs and a downstream amp was redundant. Confirmed against the BT1026D datasheet and Feasycom's own reference design that these are class-AB outputs sized for driving low-impedance loads directly, but Feasycom's reference schematic still routes them through a dedicated power amp (PAM8908) before the actual speaker — so a downstream amp stage is the vendor-validated approach, not redundant. Landed on MAX98306 over PAM8908: functionally equivalent (filterless class-D, differential input, direct speaker output, similar TDFN package), but simpler gain-select pin scheme and better community documentation/breakout availability.

Battery charger

TP4056 → BQ24074 TP4056 has no power-path management — using the device while charging causes improper charge termination and accelerates battery aging, a real concern for a daily-worn device charged repeatedly. BQ24074 adds dynamic power-path management (DPPM), letting the system run directly off USB input while independently and properly charging the battery. Battery itself has its own onboard protection, so TP4056's lack of protection circuitry was not the deciding factor — power-path was.

Voltage regulator

AMS1117 → TLV75733 AMS1117 has a comparatively high dropout voltage (~1.1V) and mediocre PSRR/noise performance. As a Li-ion-powered wearable discharges toward end-of-charge (~3.6–3.7V), AMS1117 struggles to maintain clean 3.3V regulation. TLV75733 offers a much lower dropout and cleaner rail, better suited to battery-powered portable/audio hardware. This one was actually specified correctly from the start of the KiCad schematic — no rework needed, just confirmed as the right call in hindsight.

IMU

MPU-6050 → MPU-6500 MPU-6050 is effectively legacy/clone-only at this point. Evaluated ICM-42688-P and BMI270 (both offer on-chip wake-on-motion / gesture engines), but stock availability (Robu out of stock on BMI270; India tax overhead on DigiKey/Mouser for the TDK part) made MPU-6500 the practical choice. Same register-map family as MPU-6050, so blocks 03–06 (mpu6050-i2c through sleep-modes) were built and marked done against MPU-6050 and need re-verification against MPU-6500 — expect minor differences in WHO_AM_I and scale/config register values.

USB-C receptacle

PowerOnly_6P → full pinout with SBU1/SBU2 Original footprint only broke out VBUS/GND/CC1/CC2 — fine for charging, but the salvaged C20 harness routes mic/speaker/button signals over other USB-C pins (confirmed present, likely SBU1/SBU2 based on pin-mapping via breakout board). Swapped to a receptacle that exposes the full pin set so those signals can actually be routed to the board.
