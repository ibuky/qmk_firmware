#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum avion_layers {
  _BL,  // Base
  _LL,  // Lower
  _RL,  // Raise
  _FL   // Function
};

#define _______ KC_TRNS // Transparent key

enum custom_keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
    FUNC,
    KANA,
    EMOJI,
    LED_TGL,
};

bool is_active_emoji_kb = false;
bool is_active_led_flash = true;
void change_txrx_led_state(char* led, bool state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base Layer
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Esc  | GUI  | Menu | Alt  | Space| Lower| Raise| Kana | Left | Down | Up   |Right |
   * `----------------------------------+------+------+----------------------------------'
   *                                    | (    | )    |
   *                                 +---------+---------+
   *                                 | '   | Emoji| Bksp |
   *                                 `-------------------'
   */
  [_BL] = LAYOUT_all(
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,  KC_Y,  KC_U, KC_I,    KC_O,    KC_P,     KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,  KC_H,  KC_J, KC_K,    KC_L,    KC_SCLN,  KC_MINS,
    KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
    KC_ESC,  KC_LGUI, KC_LALT, KC_APP, KC_SPC, LOWER, RAISE, KANA, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT,
                                       KC_LPRN,              KC_RPRN,
                                       KC_QUOT,    EMOJI,    KC_BSPC
  ),

  /* Lower Layer
   * ,-----------------------------------------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |   <  |   >  |   {  |   }  |      |      |   =  |   +  |   -  |      |   '  |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |      |   '  |   "  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `----------------------------------+------+------+----------------------------------'
   *                                    | [    | ]    |
   *                                 +---------+---------+
   *                                 | <   |      | >    |
   *                                 `-------------------'
   */
  [_LL] = LAYOUT_all(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_LT,   KC_GT,   KC_LCBR, KC_RCBR, _______, _______, KC_EQL,  KC_PLUS, KC_MINS, _______, KC_QUOT,
    _______, _______, _______, KC_QUOT, KC_DQUO, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, FUNC,    _______, _______, _______, _______, _______,
                                        KC_LBRC,                   KC_RBRC, \
                                        KC_LT,        _______,     KC_GT
  ),

  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  \   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  F11 |  F12  |     |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      | FUNC |      |      | Home | Vol- | Vol+ | End  |
   * `-----------------------------------------------------------------------------------'
   *                                    | {    | }    |
   *                                 +---------+---------+
   *                                 | Home |     | End  |
   *                                 `-------------------'
   */
  [_RL] = LAYOUT_all(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSLS,
      _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, FUNC,    _______, _______, KC_HOME, KC_VOLD, KC_VOLU, KC_END,
                                          KC_LCBR,                   KC_RCBR,
                                          KC_HOME,      _______,     KC_END
  ),

  /* Function Layer
   * ,-----------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `----------------------------------+------+------+----------------------------------'
   *                                    |LEDtgl|      |
   *                                 +---------+---------+
   *                                 |     | SLEEP|      |
   *                                 `-------------------'
   */
  [_FL] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                        LED_TGL,                   _______,
                                        _______,      KC_SLEP,     _______
  ),
};


/* Macro settings */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
      /* Move to Lower Layer */
      case LOWER:
        if (record->event.pressed) {
          layer_on(_LL);
        } else {
          layer_off(_LL);
        }
        break;

      /* Move to Raise Layer */
      case RAISE:
        if (record->event.pressed) {
          layer_on(_RL);
        } else {
          layer_off(_RL);
        }
        break;

      /* Move to Function Layer */
      case FUNC:
        if (record->event.pressed) {
          layer_on(_FL);
        } else {
          layer_off(_FL);
        }
        break;

      // Toggle IME input mode (Hiragana <-> Halfwidth Eisu)
      case KANA:
        if (record->event.pressed) {
          SEND_STRING(SS_LALT("`"));  // Alt + `
        }
        break;

      // Launch Emoji keyboard
      case EMOJI:
        if (record->event.pressed) {
          if (is_active_emoji_kb) {
            // Hit Esc key to exit Emoji keyboard (without this, next launch should fail)
            tap_code(KC_ESC);
          } else {
            SEND_STRING(SS_LGUI(";"));  // Win + ;
            is_active_emoji_kb = !is_active_emoji_kb;
          }
        }
        break;

      // Toggle LED flash function (default to on)
      case LED_TGL:
        if (record->event.pressed) is_active_led_flash = !is_active_led_flash;
        break;
  }

  if (is_active_led_flash && record->event.pressed) {
    if (record->event.key.col < 6) {
      change_txrx_led_state("TX", false);
      _delay_ms(20);
      change_txrx_led_state("TX", true);
    } else {
      change_txrx_led_state("RX", false);
      _delay_ms(20);
      change_txrx_led_state("RX", true);
    }
  } else {
    if (record->event.key.col < 6) {
      change_txrx_led_state("TX", false);
    } else {
      change_txrx_led_state("RX", false);
    }
  }
  return true;
};

void change_txrx_led_state(char* led, bool state) {
  if (strcmp(led, "TX") == 0) {
    // right side
    if (state) {
      PORTB &= ~(1<<0);
    } else {
      PORTB |= (1<<0);
    }
  } else if (strcmp(led, "RX") == 0) {
    // left side
    if (state) {
      PORTD &= ~(1<<5);
    } else {
      PORTD |= (1<<5);
    }
  }
}