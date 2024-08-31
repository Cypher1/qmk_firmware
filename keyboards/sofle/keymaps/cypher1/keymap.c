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

#include QMK_KEYBOARD_H
#define ALT_TAB_TIMEOUT 1250
#define LF_SPC LT(FUNCS, KC_SPC)
#define LC_BSPC LT(CNTRL, KC_BSPC)
#define MT_RSHN MT(MOD_RSFT, KC_ENT)
#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_BTN3 KC_MS_BTN3
#define MS_WUP KC_MS_WH_UP
#define MS_WDN KC_MS_WH_DOWN
#define MS_WLFT KC_MS_WH_LEFT
#define MS_WRGHT KC_MS_WH_RIGHT
#define MS_UP KC_MS_UP
#define MS_DOWN KC_MS_DOWN
#define MS_LEFT KC_MS_LEFT
#define MS_RGHT KC_MS_RIGHT

enum LAYERS {
  QWERT, // All the bells and whistles for coding.
  FUNCS, // Function keys (e.g. screen brightness, media keys).
  CNTRL, // Controls for the keyboard (e.g. brightness, colours) and mouse (buttons and movement).
};

#include "os_detection.h" // Detect which OS we're talking to.
#include "state.h"   // Include the global state that the pet looks at.
#include "luna.h"    // Include the pet you want.
#include "pet.h"     // Include the pet library.
#include "oled.h"    // Include the oled (call the pet from here).

enum custom_keycodes {
  ALT_TAB,
  RALT_TAB,
  USR_CUT,
  USR_COPY,
  USR_PASTE,
  USR_NEWTAB,
  NONE = SAFE_RANGE,
};

enum combo_events {
  USR_CUT_COMBO,
  USR_COPY_COMBO,
  USR_PASTE_COMBO,
  USR_NEWTAB_COMBO,
};

// Set up combos with modifiers.
const uint16_t PROGMEM cut_combo[] = {KC_LCTL, KC_X, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_LCTL, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_LCTL, KC_V, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_LCTL, KC_T, COMBO_END};

combo_t key_combos[] = {
  [USR_CUT_COMBO] = COMBO(cut_combo, USR_CUT),
  [USR_COPY_COMBO] = COMBO(copy_combo, USR_COPY),
  [USR_PASTE_COMBO] = COMBO(paste_combo, USR_PASTE),
  [USR_NEWTAB_COMBO] = COMBO(tab_combo, USR_NEWTAB),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERT] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [FUNCS] = { ENCODER_CCW_CW(MS_RGHT, MS_LEFT), ENCODER_CCW_CW(MS_DOWN, MS_UP) },
    [CNTRL] = { ENCODER_CCW_CW(KC_RGHT, KC_LEFT), ENCODER_CCW_CW(KC_DOWN, KC_UP) },
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERT] = LAYOUT(
   KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS,
   KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   KC_EQL,
   KC_ESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  KC_MUTE,  ALT_TAB,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  MT_RSHN,
                      KC_BSLS,  KC_LALT,  KC_LGUI,  LF_LCTL,   KC_SPC,  LC_BSPC,   LF_SPC,  KC_PGUP,  KC_PGDN,  KC_BSLS
),
[FUNCS] = LAYOUT(
  _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
  _______,  _______,  _______,  _______,  _______,  _______,                      MS_WLFT,   MS_WDN,   MS_WUP, MS_WRGHT,  _______,   KC_F12,
  _______,  _______,  _______,  _______,  KC_HOME,   KC_END,                      MS_LEFT,  MS_DOWN,    MS_UP,  MS_RGHT,  _______,  _______,
  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,  _______, RALT_TAB,  ALT_TAB,  MS_BTN1,  MS_BTN3,  MS_BTN2,  _______,  _______,  _______,
                      _______,  _______,  _______,  _______,  _______,   KC_DEL,  _______,  _______,  _______,  _______
),
[CNTRL] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,                      KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  _______,  _______,
  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,  _______, RALT_TAB,  ALT_TAB,  _______,  _______,  _______,  _______,  _______,  _______,
                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
)
};

void tap_super_with_key(uint16_t keycode, bool pressed) {
  os_variant_t host_os = detected_host_os();
  uint16_t to_tap = C(keycode);
  if (host_os == OS_MACOS || host_os == OS_IOS) {
    to_tap = G(keycode);
  }
  if (pressed) {
    register_code(to_tap);
  } else {
    unregister_code(to_tap);
  }
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  // Map combos to custom keys.
  uint16_t keycode = 0;
  switch(combo_index) {
    case USR_CUT:
      keycode = KC_X;
      break;
    case USR_COPY:
      keycode = KC_C;
      break;
    case USR_PASTE:
      keycode = KC_V;
      break;
    case USR_NEWTAB:
      keycode = KC_T;
      break;
    case ALT_TAB:
      if (!is_alt_tab_active) {
        register_code(KC_LALT);
        is_alt_tab_active = true;
      }
      alt_tab_timer = timer_read();
      tap_code16(KC_TAB);
      break;
    case RALT_TAB:
      if (!is_alt_tab_active) {
        register_code(KC_LALT);
        is_alt_tab_active = true;
      }
      alt_tab_timer = timer_read();
      tap_code16(S(KC_TAB));
      break;
    default:
      return;
  }
  tap_super_with_key(keycode, pressed);
}

void matrix_scan_user(void) {
  if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > ALT_TAB_TIMEOUT) {
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
  }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combos when gaming layer is the default */
    return true;
}

bool data_reset;
uint16_t data_in;
uint16_t message_counter = 0;

uint16_t data_index = 0;

bool led_update_user(led_t led_state) {
  // I can now send two bits of data at a time!
  // caps + num 0 = 0
  // caps + num 1 = 1
  // no caps = ignore (i.e. it's a clock).
  /*
  data_str[0] = led_state.num_lock    ? 'n' : ' ';
  data_str[1] = led_state.caps_lock   ? 'C' : ' ';
  data_str[2] = led_state.scroll_lock ? 's' : ' ';
  data_str[3] = led_state.kana        ? 'k' : ' ';
  data_str[4] = led_state.compose     ? 'c' : ' ';
  data_str[5] = '\0';
  */
  if (led_state.num_lock) {
    uint16_t signal = led_state.caps_lock;
    if (data_reset) {
      if (signal == 1) {
        data_reset = false;
      }
      return true;
    }
    data_in = (data_in << 1) | signal;
    message_counter++;

    if (message_counter == 8) {
      if (data_in == 0) { // reset.
        for(int i = 0; i < DATA_LEN; i++) {
          data_str[i] = ' ';
        }
        data_index = 0;
        message_counter = 0;
        data_reset = true;
      } else {
        data_str[data_index] = data_in;
        data_in = 0;
        data_index++;
        data_index = data_index%(DATA_LEN-1);
        message_counter = 0;
      }
    }
  }

  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            /* Smart Backspace Delete */
        case KC_RSFT:
        case KC_LSFT:
            // Set shift status for other modules to use.
            if (record->event.pressed) {
              shift_held++;
            } else {
              shift_held--;
            }
            break;
        case KC_LCTL:
        case KC_RCTL:
            update_pet_sneaking(record->event.pressed);
            break;
        case LF_SPC:
        case KC_SPC:
            if (record->event.pressed) {
              fn_held++;
            } else {
              fn_held--;
            }
            update_pet_jump(record->event.pressed);
            break;
    }
    return true;
}
