/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS
#define SPLIT_WPM_ENABLE

#if defined(KEYBOARD_sofle_rev1)
// Add RGB underglow and top facing lighting
#    define RGB_DI_PIN D3
#    define RGBLED_NUM 70
#    define RGBLED_SPLIT \
        { 36, 36 }
#    ifdef RGB_MATRIX_ENABLE
#        define DRIVER_LED_TOTAL RGBLED_NUM
#        define RGB_MATRIX_SPLIT RGBLED_SPLIT
#        define SPLIT_TRANSPORT_MIRROR
#    else
#        define RGBLIGHT_ANIMATIONS
#        define RGBLIGHT_LIMIT_VAL 120
#        define RGBLIGHT_HUE_STEP  10
#        define RGBLIGHT_SAT_STEP  17
#        define RGBLIGHT_VAL_STEP  17
#    endif
#endif

/* encoder support */
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTION 2
#define ENCODER_DIRECTION_FLIP

// Saving space (thanks michal).
#define LAYER_STATE_8BIT
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE
// If michal recalls correctly, these aren't necessary for the sofle
// so I disable them to save more space.
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
