// Copyright 2024 Lukas Hrazky
//
// This file is part of the Refloat VESC package.
//
// Refloat VESC package is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// Refloat VESC package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.

#include "footpad_sensor.h"

#include "vesc_c_if.h"

void footpad_sensor_update(FootpadSensor *fs, const RefloatConfig *config) {
    fs->adc1 = VESC_IF->io_read_analog(VESC_PIN_ADC1);
    // Returns -1.0 if the pin is missing on the hardware
    fs->adc2 = VESC_IF->io_read_analog(VESC_PIN_ADC2);
    if (fs->adc2 < 0.0) {
        fs->adc2 = 0.0;
    }

    fs->state = FS_RIGHT;
    if (fs->adc1 > config->fault_adc1) {
        fs->state = FS_BOTH;
    }
}

int footpad_sensor_state_to_switch_compat(FootpadSensorState v) {
    switch (v) {
    case FS_BOTH:
        return 2;
    case FS_LEFT:
    case FS_RIGHT:
        return 1;
    case FS_NONE:
    default:
        return 0;
    }
}
