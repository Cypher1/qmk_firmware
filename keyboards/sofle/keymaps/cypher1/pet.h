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

static void update_pet_sneaking(bool sneaking) {
  isSneaking = sneaking;
}

static void update_pet_jump(bool jump) {
  if (jump) {
    if (!isJumping && showedJump) {
      // Finish jumping
      isJumping = true;
      showedJump = false;
    }
  } else {
    isJumping = false;
  }
}

static void update_pet(void) {
  /* switch frame */
  current_frame = (current_frame + 1) % ANIM_LENGTH;
  showedJump = true;
}

/* animation */
static void animate_pet(int PET_X, int PET_Y) {
  /* handle jump */
  int offset = 0;
  if (isJumping || !showedJump) {
    offset = 1;
  }
  oled_set_cursor(PET_X, PET_Y -1 + offset * 3); // Clear at the top or bottom.
  // Clear the previous position.
  oled_write("     ", false);
  oled_set_cursor(PET_X, PET_Y - offset);

  /* current status */
  const int show_frame = abs(1 - current_frame);
  if (get_shift_held() || led_usb_state.caps_lock) {
    oled_write_raw_P(pet.noisey[show_frame], ANIM_SIZE);
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

static void render_pet(int PET_X, int PET_Y) {
  /* animation timer */
  if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
    anim_timer = timer_read32();
    animate_pet(PET_X, PET_Y);
    update_pet();
  }
}
