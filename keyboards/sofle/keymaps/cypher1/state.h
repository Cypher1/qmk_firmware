/* state variables */
uint16_t shift_held = 0;
uint16_t fn_held = 0;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

static const bool get_shift_held(void) {
  return shift_held > 0;
}

// static const bool get_fn_held(void) {
  // return fn_held > 0;
// }
