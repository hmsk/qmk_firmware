#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NAV 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NAV,
  MY_EMAIL,
  MY_NPM,
  MY_YARN
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

//Tap Dance Declarations
enum {
  TD_LANG = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Space, twice for Cmd+Space
 [TD_LANG] = ACTION_TAP_DANCE_DOUBLE (KC_SPC, LGUI(KC_SPC)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             .-----------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   -  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |   "  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------..-----+------+------+------+------+------+------|
   * | NAV  |RGBTOG| Ctrl |  Alt | LGUI |Space |Backsp||Space| Enter|   [  |   ]  |   =  | PGUP |  NAV |
   * `------------------------------------------------''-----------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,                      KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_MINUS, \
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                      KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                      KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                      KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,  \
    MO(_NAV), RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_BSPC, TD(TD_LANG),  KC_ENT,   KC_LBRC,  KC_RBRC, KC_EQL,  KC_PGUP, MO(_NAV) \
  ),

  /* NAV
   * ,-----------------------------------------.             .-----------------------------------------.
   * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |RGBSAI|RGBSAD|      | RESET|      |             | PgUp |      |      |      |Insert| Home |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |RGBHUI|RGBVAI| PgDn |      |      |             | Left | Down |  Up  | Right|Delete| End  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Shift |RGBHUD|RGBVAD|      |      |      |             | NKRO |      |      | Pause| Back | Next |
   * |------+------+------+------+------+------+------..-----+------+------+------+------+------+------|
   * |      | GUI  | Alt  |      |      |RGBRMD|RGBMOD||RGB T|RGB P | VOLUP| VOLDN| Mute |      |      |
   * `------------------------------------------------''-----------------------------------------------'
   */
  [_NAV] = LAYOUT( \
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    _______, RGB_SAI, RGB_SAD, _______, RESET,   _______,                   MY_YARN,  KC_PGUP,  _______, _______, KC_INS,  KC_HOME, \
    _______, RGB_HUI, RGB_VAI, KC_PGDN, _______, _______,                   KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, KC_DEL,  KC_END,  \
    KC_LSFT, RGB_HUD, RGB_VAD, _______, _______, _______,                   MY_NPM,   MY_EMAIL, _______, KC_MPLY, KC_MPRV, KC_MNXT, \
    _______, KC_LGUI, KC_LALT, _______, _______, RGB_RMOD, RGB_MOD, RGB_M_T, RGB_M_P, KC_VOLD,  KC_VOLD, KC_MUTE, _______, _______ \
  ),

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case MY_EMAIL:
      if (record->event.pressed) {
        SEND_STRING("k.hamasaki@gmail.com");
      }
      return false;
      break;
    case MY_NPM:
      if (record->event.pressed) {
        SEND_STRING("npm run ");
      }
      return false;
      break;
    case MY_YARN:
      if (record->event.pressed) {
        SEND_STRING("yarn run ");
      }
      return false;
      break;

    //case COLEMAK:
      //if (record->event.pressed) {
        //#ifdef AUDIO_ENABLE
          //PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        //#endif
        //persistant_default_layer_set(1UL<<_COLEMAK);
      //}
      //return false;
      //break;
  }
  return true;
}
