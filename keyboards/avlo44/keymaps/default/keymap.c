/* Copyright 2021 johnplanow
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

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

// Left-hand home row mods
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_avlo44(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,       KC_P,   KC_BSPC,
    KC_TAB,   CTL_A,   ALT_S,    GUI_D,    SFT_F,      KC_G,               KC_H,    SFT_J,    GUI_K,    ALT_L,   CTL_SCLN,   KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,   KC_RSFT,
                            KC_LCTL, KC_LCMD, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_RALT,   _______
  ),

  [_LOWER] = LAYOUT_avlo44(
    KC_TILD,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,             KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,   KC_DEL,
     KC_GRV,  _______,  _______,  _______,  _______,  _______,             KC_PIPE,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_TILD,
    _______,  _______,  _______,  _______,  _______,  _______,             KC_BSLS,  KC_MINS,   KC_EQL,  KC_LBRC,  KC_RBRC,   KC_GRV,
                                _______, _______, _______,  _______, _______,  _______, _______, _______
  ),

  [_RAISE] = LAYOUT_avlo44(
    _______,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,      KC_8,     KC_9,     KC_0,  _______,
      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,            KC_LEFT,  KC_DOWN,     KC_UP,  KC_RGHT,  _______,  _______,
      KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,            _______,  _______,   _______,  _______,  _______,  _______,
                                 _______, _______, _______,  _______, _______,  _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_avlo44(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                  _______, _______, _______,  _______, _______,  _______, _______, _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
    // If you want to change the display of OLED, you need to change here
    //oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
    oled_write(read_logo(), false);
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    //set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
