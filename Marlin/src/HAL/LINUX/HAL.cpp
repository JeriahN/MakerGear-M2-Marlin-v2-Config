/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifdef __PLAT_LINUX__

#include "../../inc/MarlinConfig.h"
#include "../shared/Delay.h"

// ------------------------
// Serial ports
// ------------------------

MSerialT usb_serial(TERN0(EMERGENCY_PARSER, true));

// U8glib required functions
extern "C" {
  void u8g_xMicroDelay(uint16_t val) { DELAY_US(val); }
  void u8g_MicroDelay()              { u8g_xMicroDelay(1); }
  void u8g_10MicroDelay()            { u8g_xMicroDelay(10); }
  void u8g_Delay(uint16_t val)       { delay(val); }
}

//************************//

// return free heap space
int freeMemory() { return 0; }

// ------------------------
// ADC
// ------------------------

uint8_t MarlinHAL::active_ch = 0;

uint16_t MarlinHAL::adc_value() {
  const pin_t pin = analogInputToDigitalPin(active_ch);
  if (!VALID_PIN(pin)) return 0;
  return uint16_t((Gpio::get(pin) >> 2) & 0x3FF); // return 10bit value as Marlin expects
}

void MarlinHAL::reboot() { /* Reset the application state and GPIO */ }

#endif // __PLAT_LINUX__
