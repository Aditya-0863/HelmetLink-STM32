# Debug Log — HelmetLink-STM32

## 2026-07-20: Initial Setup
- Created bare-metal GPIO project in STM32CubeIDE
- Wrote register-level LED blink code
- **Issue:** ST-Link not detected — ordered new USB data cable

## 2026-07-21: LED Not Responding
- **Symptom:** LD4 did not blink despite correct register code
- **Investigation:**
  1. Verified PA5 = LD4 in UM2324 manual
  2. Tested with deliberate HardFault — confirmed code reaches `main()`
  3. Discovered LD1 (COM) blinks from ST-Link, not user code
  4. Noticed LED blinks only after debugger termination
- **Root Cause:** Debugger breakpoint at `main()` halts CPU
- **Fix:** Unchecked breakpoint in Debug Configurations → Startup
- **Result:** LD4 blinks correctly at ~1 Hz

## Key Distinction: Nucleo-G071RB LEDs
| LED | Label | Color | Controlled By | Pin |
|-----|-------|-------|-------------|-----|
| LD1 | COM | Red/Green | ST-Link (USB status) | N/A |
| LD4 | USER | Green | User code | PA5 |
