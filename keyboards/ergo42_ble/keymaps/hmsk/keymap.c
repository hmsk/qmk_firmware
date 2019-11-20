/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "app_ble_func.h"
#include <print.h>

#define _QWERTY 0
#define _META 1
#define _SYMB 2
#define _CONF 3

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    QWERTY,
    META,
    SYMB,
    CONF,
    KANA,
    EMOJI,
    SCREEN
};

void tap_code16(uint16_t code) {
  register_code16(code);
  wait_ms(10);
  unregister_code16(code);
}

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY
   * ,---------------------------------------------------.   ,------------------------------------------------.
   * | Esc     |   Q  |   W  |   E  |   R  |   T  |  Y   |   |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |---------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Tab/Ctrl|   A  |   S  |   D  |   F  |   G  |SCREEN|   | EMOJI|   H  |   J  |   K  |   L  |   ;  |  '   |
   * |---------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Shift   |   Z  |   X  |   C  |   V  |   B  | KANA |   | KANA |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |---------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | META    | CONF |  Alt |  Alt |  Cmd | Space|BSpace|   | SYMB | Enter|   [  |   ]  |VolDwn| VolUp| META |
   * '---------------------------------------------------'   '------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,         KC_Q, KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_T,  KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    LCTL_T(KC_TAB), KC_A, KC_S,    KC_D,    KC_F,    KC_G,   SCREEN,  EMOJI, KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT,        KC_Z, KC_X,    KC_C,    KC_V,    KC_B,   KANA,    KANA,  KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_RO), \
    META,           CONF, KC_LALT, KC_LALT, KC_LGUI, KC_SPC, KC_BSPC, SYMB,  KC_ENTER, KC_LBRC, KC_RBRC, KC_VOLD, KC_VOLU, META \
  ),

  /* META
   * ,---------------------------------------------------.   ,------------------------------------------------.
   * |   `     |   1  |   2  |   3  |   4  |   5  |  6   |   |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |---------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * | Tab/Ctrl|      |      |      |      |      |      |   |      | Left | Down |  Up  |Right |      |  =   |
   * |---------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Shift   |      |      |      |      |      |      |   |      |      |      |      |      |   ?  |Shift |
   * |---------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |         |      |      |      |      |  Cmd |BSpace|   |      | Enter|      |      |PgDown| PgUp |      |
   * '---------------------------------------------------'   '------------------------------------------------'
   */
  [_META] = LAYOUT( \
    KC_GRV,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    LCTL(KC_TAB), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_EQL, \
    KC_LSFT,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_QUES, KC_RSFT, \
    _______,      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, KC_BSPC, _______, KC_ENTER, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, _______ \
  ),

  /* SYMB
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |  ^   |   |   %  |   ^  |   &  |   *  |   (  |   )  |  _   |
   * |------+------+------+------+------+------+------|   |-------------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |   :  |  "   |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |   <  |   >  |   ?  |  \   |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_SYMB] = LAYOUT( \
    S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_5), S(KC_6), S(KC_7), S(KC_8),    S(KC_9),   S(KC_0),    S(KC_BSLS), \
    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   S(KC_SCLN), S(KC_QUOT), \
    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_COMM), S(KC_DOT), S(KC_SLSH), KC_RSFT, \
    _______,   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX,    _______ \
  ),

  /* CONF
   * ,--------------------------------------------------------.  ,-------------------------------------------------.
   * |ADV WO WL|ADV ID1|ADV ID2|ADV ID3|ADV ID4| SLEEP | DFU  |  |      |      |      |      |      |ADV ID0|      |
   * |---------+-------+-------+-------+-------+-------+------|  |------+------+------+------+------+-------+------|
   * |         |       |       |       |       |USB OFF|USB ON|  |      |      |      |      |      |       |      |
   * |---------+-------+-------+-------+-------+-------+------|  |------+------+------+------+------+-------+------|
   * | BATTERY |DEL ID1|DEL ID2|DEL ID3|DEL ID4|BLE OFF|BLE ON|  |      |      |      |      |      |DEL ID0|      |
   * |---------+-------+-------+-------+-------+-------+------|  |------+------+------+------+------+-------+------|
   * |         |       |       |       |       |       |      |  |      |      |      |      |      |       |      |
   * `--------------------------------------------------------'  `-------------------------------------------------'
   */
  [_CONF] = LAYOUT ( \
   AD_WO_L, ADV_ID1, ADV_ID2, ADV_ID3,  ADV_ID4, ENT_SLP,  ENT_DFU,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, ADV_ID0,  XXXXXXX, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, USB_DIS,  USB_EN,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, \
   BATT_LV, DEL_ID1, DEL_ID2, DEL_ID3,  DEL_ID4, BLE_DIS,  BLE_EN,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, DEL_ID0,  XXXXXXX, \
   _______, _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,      _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  _______  \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  char str[16];

  switch (keycode) {
    case META:
      if (record->event.pressed) {
        layer_on(_META);
        update_tri_layer(_META, _SYMB, _CONF);
      } else {
        layer_off(_META);
        update_tri_layer(_META, _SYMB, _CONF);
      }
      return false;
      break;
    case CONF:
      if (record->event.pressed) {
        layer_on(_CONF);
      } else {
        layer_off(_CONF);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
        layer_on(_SYMB);
        update_tri_layer(_META, _SYMB, _CONF);
      } else {
        layer_off(_SYMB);
        update_tri_layer(_META, _SYMB, _CONF);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        tap_code16(LGUI(KC_SPC));
      }
      return false;
      break;
    case EMOJI:
      if (record->event.pressed) {
        tap_code16(LCTL(LGUI(KC_SPC)));
      }
      return false;
      break;
    case SCREEN:
      if (record->event.pressed) {
        tap_code16(LCTL(LGUI(S(KC_4))));
      }
      return false;
      break;
  }

  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }
  }
  return true;
}
;
