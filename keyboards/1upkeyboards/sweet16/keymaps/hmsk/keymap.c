#include "sweet16.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_4x4(
        KC_PGUP,          KC_PGDN,          KC_N,             LSFT(KC_N),
        LALT(LGUI(KC_L)), LALT(LGUI(KC_T)), LALT(LGUI(KC_R)), LALT(LGUI(KC_J)),
        LALT(KC_LT),      LALT(KC_GT),      LALT(KC_COMMA),   LALT(KC_DOT),
        LGUI(KC_B),       LGUI(KC_I),       LGUI(KC_U),       KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
