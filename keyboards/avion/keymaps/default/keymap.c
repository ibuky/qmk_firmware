#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum avion_layers {
  _BL,
  _LL,
  _RL
};

#define _BL 0 // Default layer
#define _LL 1 // Lower layer
#define _RL 2 // Raise layer

#define LOWER MO(_LL)
#define RAISE MO(_RL)

#define _______ KC_TRNS // Transparent key

enum custom_keycodes {
    KANA = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Default layout
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Esc  | GUI  | Alt  | Menu | Spc  | Lowr | Rais | Kana | Left | Down | Up   |Right |
   * `----------------------------------+------+------+----------------------------------'
   *                                    | Alt  | Kn/R |
   *                                 +---------+---------+
   *                                 | Alt | Kn/R | Kn/R |
   *                                 `-------------------'
   */
  [_BL] = LAYOUT_all(
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,  KC_Y,  KC_U, KC_I,    KC_O,    KC_P,     KC_BSPC, \
    KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,  KC_H,  KC_J, KC_K,    KC_L,    KC_SCLN,  KC_MINS, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,  \
    KC_ESC,  KC_LGUI, KC_LALT, KC_APP, KC_SPC, LOWER, RAISE, KANA, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT, \
                                       KC_LALT,              KC_SPC, \
                                       KC_Q,      KC_W,      KC_A),
};


/* Macro settings */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      // Toggle IME input mode (Hiragana <-> Halfwidth Eisu)
      case KANA:
        SEND_STRING(SS_LALT("`"));  // Alt + `
      return false;
    }
  }
  return true;
};
