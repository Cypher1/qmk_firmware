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

/* settings */
#define MIN_WALK_SPEED      10
#define MIN_RUN_SPEED       40
/* advanced settings */
#define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms

#include "anim.h"
#include "luna_anim.h"

/* timers */
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */

static void update_luna_sneaking(bool sneaking) {
  isSneaking = sneaking;
}

static void update_luna_jump(bool jump) {
  if (jump) {
      if (isJumping || !showedJump) {
        // Still falling :D
      } else {
          isJumping = true;
          showedJump = false;
      }
  } else {
      isJumping = false;
  }
}

/* animation */
void animate_luna(int LUNA_X, int LUNA_Y) {
    /* jump */
    if (isJumping || !showedJump) {
        /* clear */
        oled_set_cursor(LUNA_X, LUNA_Y + 2);
        oled_write("     ", false);

        oled_set_cursor(LUNA_X, LUNA_Y - 1);

        showedJump = true;
    } else {
        /* clear */
        oled_set_cursor(LUNA_X, LUNA_Y - 1);
        oled_write("     ", false);

        oled_set_cursor(LUNA_X, LUNA_Y);
    }

    /* switch frame */
    current_frame = (current_frame + 1) % 2;

    const Anim pet = luna;

    int show_frame = abs(1 - current_frame);
    /* current status */
    if (get_shift_held() || led_usb_state.caps_lock) {
        oled_write_raw_P(pet.bark[show_frame], ANIM_SIZE);
    } else if (isSneaking) {
        oled_write_raw_P(pet.sneak[show_frame], ANIM_SIZE);
    } else if (current_wpm <= MIN_WALK_SPEED) {
        oled_write_raw_P(pet.sit[show_frame], ANIM_SIZE);
    } else if (current_wpm <= MIN_RUN_SPEED) {
        oled_write_raw_P(pet.walk[show_frame], ANIM_SIZE);
    } else {
        oled_write_raw_P(pet.run[show_frame], ANIM_SIZE);
    }
}

static void render_luna(int LUNA_X, int LUNA_Y) {
    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna(LUNA_X, LUNA_Y);
    }
}
