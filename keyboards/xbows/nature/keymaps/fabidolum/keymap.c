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

/* purpose:
 * US keyboard on OS side => send the key corresponding to the keycap etching
 * Bepo on OS side: toggle to the layer LR_BEPO and get the custom bépo layout 
 *
 * Toggling : use the PrintScreen key (who uses it?)
 * Color indicator (leds) depending on QWERTY or BEPO
 *
 * Keep the original (X-bows nature) Fn layer.
 */


#define LR_BASE 0      // almost original layer: qwerty. BLUE led indicator
#define LR_BEPO 1      // modified bepo. GREEN led indicator
#define LR_BASE_FN 8   // original fn layer. RED led


// https://github.com/JonasGessner/qmk_firmware/blob/key-overrides/docs/feature_key_overrides.md

const key_override_t lowerthan      = ko_make_with_layers(MOD_MASK_SHIFT, BP_LABK, BP_2,    1 << LR_BEPO);
const key_override_t greaterthan    = ko_make_with_layers(MOD_MASK_SHIFT, BP_RABK, BP_3,    1 << LR_BEPO);
const key_override_t bptil_override = ko_make_with_layers(MOD_MASK_SHIFT, BP_GRV,  BP_TILD, 1 << LR_BEPO);
const key_override_t bsls_override  = ko_make_with_layers(MOD_MASK_SHIFT, BP_BSLS, BP_PIPE, 1 << LR_BEPO);
const key_override_t bperc_override = ko_make_with_layers(MOD_MASK_SHIFT, BP_PERC, BP_AMPR, 1 << LR_BEPO);
const key_override_t lacco          = ko_make_with_layers(MOD_BIT(KC_RALT), BP_DCIR, BP_RCBR, 1 << LR_BEPO);
const key_override_t racco          = ko_make_with_layers(MOD_BIT(KC_RALT), BP_Z, BP_LCBR, 1 << LR_BEPO);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &lowerthan,
    &greaterthan,
    &bptil_override,
    &bsls_override,
    &bperc_override,
    &lacco,
    &racco,
    NULL
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
  [LR_BASE] = LAYOUT(
	KC_ESC,  KC_F1,   KC_F2, KC_F3,  KC_F4,  KC_F5,   KC_F6,   KC_F7, KC_F8,  KC_F9,   KC_F10, KC_F11,  KC_F12,  KC_DEL,  TG(LR_BEPO),
	KC_GRV,  KC_1,    KC_2,  KC_3,   KC_4,   KC_5,             KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
	KC_TAB,  KC_Q,    KC_W,  KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,  KC_I,   KC_O,    KC_P,   KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
	KC_CAPS, KC_A,    KC_S,  KC_D,   KC_F,   KC_G,    KC_BSPC, KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,
	KC_LSFT, KC_Z,    KC_X,  KC_C,   KC_V,   KC_B,    KC_ENT,  KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
	KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC, KC_LCTL, KC_RSFT, KC_SPC,        KC_RALT, MO(LR_BASE_FN),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
  /* changes:
   * MO(1) => MO(LR_BASE_FN)
   * PrtScr => toggle bepo layer on/off
   * middle shift from KC_LSFT to KC_RSFT
   */
  [LR_BASE_FN] = LAYOUT(
    QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_CALC,   KC_MYCM,  KC_MSEL,   KC_MAIL,   NK_TOGG,   EE_CLR,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NUM,
    RGB_TOG,   RGB_MOD, RGB_VAI, RGB_HUI,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_HOME,
    KC_TRNS,   RGB_SPD, RGB_VAD, RGB_SPI,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_END,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_MUTE,   KC_VOLU,
    KC_TRNS,   KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,   KC_TRNS,  KC_MPLY,   KC_MPRV,   KC_VOLD,   KC_MNXT),
  /* changes:
    
  */

/* Original bépo (keymap_bepo.h)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ $ │ " │ « │ » │ ( │ ) │ @ │ + │ - │ / │ * │ = │ % │       │* │ ` │ " │ < │ > │ ( │ ) │       │ @ │ + │ - │ / │ * │ = │ $ │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │ B │ É │ P │ O │ È │ ^ │ V │ D │ L │ J │ Z │ W │     │* │tab│ b │ é │ p │ o │ è │       │ w │ v │ d │ l │ j │ z │ ^ │ \ │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │ A │ U │ I │ E │ , │ C │ T │ S │ R │ N │ M │ Ç │    │* │clk│ a │ u │ i │ e │ , │   %   │ c │ t │ s │ r │ n │ m │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │ Ê │ À │ Y │ X │ . │ K │ ' │ Q │ G │ H │ F │          │* │sft│ à │ y │ x │ . │ k │ enter │ ' │ q │ g │ h │ f │ ç │   │ ↑ │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤* ├───┼───┼───┴───┼───┴───┼───┬───┼───┴───┼───┴───┼───┼───┼───┼───┼───┤
 * │    │    │    │                        │    │    │    │    │* │ctr│gui│  alt  │  spc  │ctr│sft│  spc  │  alt  │ fn│ctr│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘* └───┴───┴───────┴───────┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
 */
 /*
   * removed from bépo : ê
   * changed from bépo : 
   *    « »  replaced by < >
   *    ' is single quote (not typographic) 
   *    w and ^ are swapped
   *    ç moved (replacing the right shift , keeping only the one which is available under the thumb )
   *    ` and $, %
   * added to bépo : \
 */

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ ` │       │* │ ~ │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ # │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │   │   │   │   │   │ ! │   │   │   │   │   │   │     │* │tab│ B │ É │ P │ O │ È │       │ W │ V │ D │ L │ J │ Z │ ! │ | │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │   │   │   │   │ ; │   │   │   │   │   │   │   │    │* │clk│ A │ U │ I │ E │ ; │   &   │ C │ T │ S │ R │ N │ M │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │   │   │   │   │ : │   │ ? │   │   │   │   │          │* │sft│ À │ Y │ X │ : │ K │       │ ? │ Q │ G │ H │ F │ Ç │   │ ↑ │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤* ├───┼───┼───┴───┼───┴───┼───┬───┼───┴───┼───┴───┼───┼───┼───┼───┼───┤
 * │    │    │    │                        │    │    │    │    │* │ctr│gui│  alt  │  spc  │ctr│sft│  spc  │  alt  │ fn│ctr│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘* └───┴───┴───────┴───────┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
 */

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ – │ — │ < │ > │ [ │ ] │ ^ │ ± │ − │ ÷ │ × │ ≠ │ ‰ │       │* │ ″ │ — │ « │ » │ [ │ ] │       │ ^ │ ± │ − │ ÷ │ × │ ≠ │ – │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │ | │ ´ │ & │ Œ │ ` │ ¡ │ ˇ │ Ð │ / │ Ĳ │ Ə │ ˘ │     │* │tab│ | │ ´ │ & │ œ │ ` │       │ ˘ │ ˇ │ ð │  ̵ │   | { │ } │ \ │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │ Æ │ Ù │ ¨ │ € │   │ © │ Þ │ ẞ │ ® │ ~ │ ¯ │ ¸ │    │* │clk│ æ │ ù │ ¨ │ € │ ’ │       │ © │ þ │ ß │   │   │ µ │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │   │ \ │ { │ } │ … │ ~ │ ¿ │ ° │   │ † │ ˛ │          │* │sft│ \ │ { │ } │ … │ ~ │       │ ¿ │ ° │ μ │ † │ ˛ │ ˛ │ ¸ │ ↑ │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤* ├───┼───┼───┴───┼───┴───┼───┬───┼───┴───┼───┴───┼───┼───┼───┼───┼───┤
 * │    │    │    │           _            │    │    │    │    │* │ctr│gui│  alt  │   _   │ctr│sft│   _   │  alt  │ fn│ctr│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘* └───┴───┴───────┴───────┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
 */

/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¶ │ „ │ “ │ ” │ ≤ │ ≥ │   │ ¬ │ ¼ │ ½ │ ¾ │ ′ │ ″ │       │* │ ~ │ „ │ “ │ ” │ ≤ │ ≥ │       │   │ ¬ │ ¼ │ ½ │ ¾ │ ′ │ ¶ │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │ ¦ │ ˝ │ § │   │   │   │   │   │   │   │   │   │     │* │tab│ ¦ │ ˝ │ § │ Œ │ ` │       │   │   │ Ð │   │ Ĳ │ ‘ │ ’ │ | │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │   │   │ ˙ │ ¤ │ ̛  │ ſ │   │   │ ™ │   │ º │ , │    │* │clk│ Æ │ Ù │ ˙ │ ¤ │  ̛ │   &   │ ſ │ Þ │ ẞ │ ™ │   │ º │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │   │   │ ‘ │ ’ │ · │   │ ̉  │ ̣  │   │ ‡ │ ª │          │* │sft│   │ ‘ │ ’ │ · │   │       │ ˀ │ . │   │ ‡ │ ª │ , │   │ ↑ │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤* ├───┼───┼───┴───┼───┴───┼───┬───┼───┴───┼───┴───┼───┼───┼───┼───┼───┤
 * │    │    │    │                        │    │    │    │    │* │ctr│gui│  alt  │       │ctr│sft│       │  alt  │ fn│ctr│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘* └───┴───┴───────┴───────┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
 */


  [LR_BEPO] = LAYOUT(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,       _______,        TO(LR_BASE),
     BP_GRV,  BP_DQUO, BP_LABK, BP_RABK, BP_LPRN, BP_RPRN,                     BP_AT, BP_PLUS,  BP_MINS, BP_SLSH, BP_ASTR,  BP_EQL, BP_DLR,     _______,
    _______,     BP_B, BP_EACU,    BP_P,    BP_O, BP_EGRV,                      BP_W,     BP_V,    BP_D,    BP_L,    BP_J,   BP_Z, BP_DCIR, BP_BSLS, _______,
    _______,     BP_A,    BP_U,    BP_I,    BP_E, BP_COMM,      BP_PERC,        BP_C,     BP_T,    BP_S,    BP_R,    BP_N,   BP_M,     _______,      _______,
    _______,  BP_AGRV,    BP_Y,    BP_X,  BP_DOT,    BP_K,      _______,     BP_QUOT,     BP_Q,    BP_G,    BP_H,    BP_F, BP_CCED,           _______,
    _______,  _______,      _______,       _______,          _______, _______,      _______,         _______,     _______, _______, _______, _______, _______)
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = 13; i <= 14; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case LR_BEPO:
                rgb_matrix_set_color(i, 0, 130, 0);
                break;
            case LR_BASE:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            default:
                break;
        }
    }
    return false;
}
