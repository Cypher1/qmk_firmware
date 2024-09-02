BOOTLOADER = atmel-dfu

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
# Features
OLED_ENABLE = yes			# Enable OLED for WPM, status and pet
ENCODER_ENABLE = yes		# Enable the two rotary encoders
ENCODER_MAP_ENABLE = yes	# Use the new method for mapping encoders
WPM_ENABLE = yes			# Used to make the pet walk or run based on typing
COMBO_ENABLE = yes			# Special keyboard combos without many many layers
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
FORCE_NKRO = yes			# Require N-Key Rollover (for combos)
OS_DETECTION_ENABLE = yes   # Support shortcuts that perform OS specific actions
KEY_LOCK_ENABLE = yes		# Support locking for things like running in games.

# Save space
CONSOLE_ENABLE = no         # Console for debug
RGBLIGHT_ENABLE = no		# Turn of lighting to save space
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Disable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
VIA_ENABLE = no				# Don't need via, I am happy writing qmk
LTO_ENABLE = yes            # Save space
