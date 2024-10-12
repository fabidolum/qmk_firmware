/* Copyright 2020 Shulin Huang <mumu@x-bows.com>
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
#include "keymap_extras/keymap_bepo.h"


#define LR_VANILLA 0 // orginal qwerty layer
#define LR_RGB     8 // function layer for RGB
#define LR_ERGOL_BASE 1 // base layer for ergol

// key overrides definitions
const key_override_t euro      = ko_make_with_layers(MOD_MASK_SHIFT, KC_1, BP_EURO,    1 << LR_ERGOL_BASE);

const key_override_t *key_overrides[] = {
    &euro
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap VANILLA: (Base Layer) Default Layer
   *
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Esc |  F1  |  F2  |  F3  |  F4  |      F5  |  F6  |  F7  |  F8  |      F9  |  F10 |  F11 |  F12 |   Delete   |    Prtsc    |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |  ~  |     1   |   2   |   3   |   4   |    5      |       6    |    7    |    8   |   9  |   0  |   -  |  =  |  Backspace  |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Tab |   Q    |    W   |   E  |   R  |   T  |            |    Y   |    U   |    I  |   O  |   P  |   [  |  ]  |   \  | PgUp |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Ctl |   A   |   S   |   D  |   F  |   G  |      Bksp      |    H  |    J   |   K  |   L  |   ;  |  '"  |    Enter   | PgDn |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Shift|   Z  |   X  |   C  |   V  |   B  |       Enter       |    N  |    M   |  ,  |   .  |  /?  | Shift|      |  Up |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Ctrl | GUI |     Alter   |    Space   |   Ctrl   |   Shift   |     Space     |    Alter   |  FN  | Ctrl | Lft  |  Dn |  Rig |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   */
  [LR_VANILLA] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2, KC_F3,  KC_F4,  KC_F5,   KC_F6,   KC_F7, KC_F8,  KC_F9,   KC_F10, KC_F11,  KC_F12,  KC_DEL,  TG(LR_ERGOL_BASE),
		KC_GRV,  KC_1,    KC_2,  KC_3,   KC_4,   KC_5,             KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,  KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,  KC_I,   KC_O,    KC_P,   KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
		KC_CAPS, KC_A,    KC_S,  KC_D,   KC_F,   KC_G,    KC_BSPC, KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,
		KC_LSFT, KC_Z,    KC_X,  KC_C,   KC_V,   KC_B,    KC_ENT,  KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC, KC_LCTL, KC_LSFT, KC_SPC,        KC_RALT, MO(LR_RGB),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
  [LR_RGB] = LAYOUT(
    QK_BOOT,   _______, _______, _______,  _______,  _______,   _______,  _______,  _______,  KC_CALC,   KC_MYCM,  KC_MSEL,   KC_MAIL,   NK_TOGG,   EE_CLR,
    _______,   _______, _______, _______,  _______,  _______,             _______,  _______,  _______,   _______,  _______,   _______,   _______,   KC_NUM,
    RGB_TOG,   RGB_MOD, RGB_VAI, RGB_HUI,  _______,  _______,   _______,  _______,  _______,  _______,   _______,  _______,   _______,   _______,   KC_HOME,
    _______,   RGB_SPD, RGB_VAD, RGB_SPI,  _______,  _______,   _______,  _______,  _______,  _______,   _______,  _______,   _______,   _______,   KC_END,
    _______,   _______, _______, _______,  _______,  _______,   _______,  _______,  _______,  _______,   _______,  _______,   KC_MUTE,   KC_VOLU,
    _______,   _______, _______,           _______,  _______,   _______,  _______,            _______,   _______,  KC_MPLY,   KC_MPRV,   KC_VOLD,   KC_MNXT),
/* changes:
* MO(1) => MO(LR_RGB)
* PrtScr => toggle ergol layer on/off
*/
 [LR_ERGOL_BASE] = LAYOUT(
    _______,   _______, _______, _______,  _______,  _______,   _______,  _______,  _______,  _______,   _______,  _______,   _______,   _______,   _______,
    _______,   KC_1,    KC_2,    KC_3,     KC_4,     KC_5,                KC_6,     KC_7,     KC_8,     KC_9,      KC_0,      _______,   _______,   _______,
    _______,   KC_Q,    KC_C,    KC_O   ,  KC_P,     KC_W,      KC_J,     KC_M,     KC_D,     _______,   KC_Y,     _______,   _______,   _______,   _______,
    _______,   KC_A,    KC_S,    KC_E,     KC_N,     KC_F,      _______,  KC_L,     KC_R,     KC_T,      KC_I,     KC_U,      _______,   _______,   _______,
    _______,   KC_Z,    KC_X,    _______,  KC_V,     KC_B,      _______,  _______,  _______,  _______,   _______,  KC_K,      _______,   _______,
    _______,   _______, _______,           _______,  _______,   _______,  _______,            _______,   _______,  _______,   _______,   _______,   _______)
};
