/* state variables */
uint16_t shift_held = 0;

static const bool get_shift_held(void) {
  return shift_held > 0;
}
