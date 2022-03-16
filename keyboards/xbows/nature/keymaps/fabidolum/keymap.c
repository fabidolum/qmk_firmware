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
//#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "keymap_extras/keymap_canadian_multilingual.h"

/* purpose:
 * US keyboard on OS side => send the key corresponding to the keycap etching
 * Canadian Multilangual on OS side: toggle to the layer LR8ASC_BEPO and get a custom bépo layout
 *
 * Toggling : use the PrintScreen key (who uses it?)
 * Color indicator (leds) depending on QWERTY or BEPO(ASC)
 *
 * Keep the original (X-bows nature) Fn layer, except the F1 key to toggle between layouts
 */

#define LR_BASE 0         // almost original layer: qwerty
#define LR_CA_BEPO 1      // same as bépo but using Canadian Multilanguage (CA)
#define LR_CA_BEPO_SFT 2  // shifted
#define LR_CA_BEPO_AGR 3  // alt-gr
#define LR_CA_BEPO_AGR_SFT 4
#define LR_BASE_FN 5   // original fn layer

/* note : massively inspired from:
  https://github.com/DidierLoiseau/qmk_firmware/blob/bepo_csa-update/layouts/community/ergodox/bepo_csa/keymap.c
*/

enum macros {
    // Characters that do not exist in CSA and must be implemented based on CP1252 support
    // Note: these are intentionally declared first to be used as indexes in cp1252_chars below
    CP_NDSH, // –
    CP_MDSH, // —
    CP_ELPS, // …
    END_UC, // indicates the last unicode character macro
    M_CA_SFT, // toggle Shift on LR_CA_BEPO
    M_1,
    M_2,
    M_3,
    M_4,
    M_5,
    M_6,
    M_7,
    M_8,
    M_9,
    M_0,
    M_DEGR,
    M_SCLN,
    M_PIPE,
    M_TILD,
};

// call CA macro
#define CA(name)   M(M_CA_##name)  

const uint16_t cp1252_chars[] = {
        [CP_NDSH] = 0x96,
        [CP_MDSH] = 0x97,
        [CP_ELPS] = 0x85,
};

/* shortcut for CP1252 character macros */
#define MCP(name)   M(CP_##name)    // calls a unicode macro


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
	KC_ESC,  KC_F1,   KC_F2, KC_F3,  KC_F4,  KC_F5,   KC_F6,   KC_F7, KC_F8,  KC_F9,   KC_F10, KC_F11,  KC_F12,  KC_DEL,  TG(LR_CA_BEPO),
	KC_GRV,  KC_1,    KC_2,  KC_3,   KC_4,   KC_5,             KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
	KC_TAB,  KC_Q,    KC_W,  KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,  KC_I,   KC_O,    KC_P,   KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
	KC_CAPS, KC_A,    KC_S,  KC_D,   KC_F,   KC_G,    KC_BSPC, KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,
	KC_LSFT, KC_Z,    KC_X,  KC_C,   KC_V,   KC_B,    KC_ENT,  KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
	KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC, KC_LCTL, KC_LSFT, KC_SPC,        KC_RALT, MO(LR_BASE_FN),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
  /* changes:
   * MO(1) => MO(LR_BASE_FN)
   * PrtScr => toggle bepo layer on/off
   */
  [LR_BASE_FN] = LAYOUT(
    RESET,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_CALC,   KC_MYCM,  KC_MSEL,   KC_MAIL,   NK_TOGG,   EEP_RST,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NLCK,
    RGB_TOG,   RGB_MOD, RGB_VAI, RGB_HUI,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_HOME,
    KC_TRNS,   RGB_SPD, RGB_VAD, RGB_SPI,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_END,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_MUTE,   KC_VOLU,
    KC_TRNS,   KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,   KC_TRNS,  KC_MPLY,   KC_MPRV,   KC_VOLD,   KC_MNXT),
  /* changes:
    F1 (TRS) : TG(LR_BEPO)
  */

/* Original bépo (keymap_bepo.h)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ $ │ " │ « │ » │ ( │ ) │ @ │ + │ - │ / │ * │ = │ % │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ B │ É │ P │ O │ È │ ^ │ V │ D │ L │ J │ Z │ W │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ U │ I │ E │ , │ C │ T │ S │ R │ N │ M │ Ç │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ Ê │ À │ Y │ X │ . │ K │ ' │ Q │ G │ H │ F │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │ ! │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │ ; │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │ : │   │ ? │   │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ – │ — │ < │ > │ [ │ ] │ ^ │ ± │ − │ ÷ │ × │ ≠ │ ‰ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ | │ ´ │ & │ Œ │ ` │ ¡ │ ˇ │ Ð │ / │ Ĳ │ Ə │ ˘ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Æ │ Ù │ ¨ │ € │   │ © │ Þ │ ẞ │ ® │ ~ │ ¯ │ ¸ │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │ \ │ { │ } │ … │ ~ │ ¿ │ ° │   │ † │ ˛ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │           _            │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¶ │ „ │ “ │ ” │ ≤ │ ≥ │   │ ¬ │ ¼ │ ½ │ ¾ │ ′ │ ″ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ ¦ │ ˝ │ § │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │ ˙ │ ¤ │ ̛  │ ſ │   │   │ ™ │   │ º │ , │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │ ‘ │ ’ │ · │ ⌨ │ ̉  │ ̣  │   │ ‡ │ ª │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
  /* Keymap fabidolum: (Base Layer) Bépo Layer
   *
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Esc |  F1  |  F2  |  F3  |  F4  |      F5  |  F6  |  F7  |  F8  |      F9  |  F10 |  F11 |  F12 |   Delete   |    Toggle BEPO    |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |  `  |     "   |   <   |   >   |   (   |    )      |       @    |    +    |    -   |   /  |   *  |   =  |  $  |  Backspace  |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Tab |   B    |    É   |   P  |   O  |   È  |            |    W   |    V   |    D  |   L  |   J  |   Z  |  ^  |   \  | PgUp |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Ctl |   A   |   U   |   I  |   E  |   ,  |      Bksp      |    C  |    T   |   S  |   R  |   N  |  M  |    Enter   | PgDn |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Shift|   À  |   Y  |   X  |   .  |   K  |       Enter       |    '  |    Q   |  G  |   H  |  F  |   Ç  |      |  Up |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Ctrl | GUI |     Alter   |    Space   |   Ctrl   |   Shift   |     Space     |    Alter   |  FN  | Ctrl | Lft  |  Dn |  Rig |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * removed from bépo : ê, %
   * changed from bépo : 
   *    « »  replaced by < >
   *    ' is single quote (not typographic) 
   *    w and ^ are swapped
   *    ç moved (replacing the right shift , keeping only the one which is available under the thumb )
   *    ` and $
   * added to bépo : \
   */
  /* Keymap fabidolum: (Base Layer) Bépo Layer / shifted
   *
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Esc |  F1  |  F2  |  F3  |  F4  |      F5  |  F6  |  F7  |  F8  |      F9  |  F10 |  F11 |  F12 |   Delete   |    Toggle BEPO    |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |  ~  |     1   |   2   |   3   |   4   |    5      |       6    |    7    |    8   |   9  |   0  |   °  |  #  |  Backspace  |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Tab |        |        |      |      |      |            |        |        |       |      |      |      |  !  |   |  | PgUp |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Ctl |       |       |      |      |   ,  |      Bksp      |       |        |      |      |      |     |    Enter   | PgDn |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Shift|      |      |      |   :  |      |       Enter       |    ?  |        |     |      |     |      |      |  Up |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Ctrl | GUI |     Alter   |    Space   |   Ctrl   |   Shift   |     Space     |    Alter   |  FN  | Ctrl | Lft  |  Dn |  Rig |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * changed from bépo : 
   *    ~ and #
   * added to bépo : |
   */
  /* Keymap fabidolum: (Base Layer) Bépo Layer AltGr
   *
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Esc |  F1  |  F2  |  F3  |  F4  |      F5  |  F6  |  F7  |  F8  |      F9  |  F10 |  F11 |  F12 |   Delete   |    Toggle BEPO    |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |     |         |       |       |       |           |      {     |     }   |    [  |   ]  |      |      |     |  Backspace  |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Tab |        |     |   &  |   Œ  |      |       |            |        |        |       |      |      |      |     |      | PgUp |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * | Ctl |   Æ   |   ù  |      |   €   |      |      Bksp      |       |        |      |      |      |     |    Enter   | PgDn |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Shift|      |      |      |   …  |      |       Enter       |       |        |     |      |     |      |      |  Up |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * |Ctrl | GUI |     Alter   |      _     |   Ctrl   |   Shift   |               |    Alter   |  FN  | Ctrl | Lft  |  Dn |  Rig |
   * |---------------------------------------------------------------------------------------------------------------------------------|
   * removed from bépo : 
   * changed from bépo : 
   * added to bépo : backslash
   */

  [LR_CA_BEPO] = LAYOUT(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,          _______,
     CA_GRV,  CA_DQUO, CA_LABK, CA_RABK, CA_LPRN, CA_RPRN,                     CA_AT, CA_PLUS, CA_MINS, CA_SLSH, CA_ASTR,   CA_EQL, KC_DLR,      KC_BSPC,
    _______,     KC_B, CA_EACU,    KC_P,    KC_O, CA_EGRV,                      KC_W,    KC_V,    KC_D,    KC_L,    KC_J,     KC_Z, CA_CIRC, CA_BSLS, _______,
    _______,     KC_A,    KC_U,    KC_I,    CA_E, KC_COMM,       _______,       KC_C,    KC_T,    KC_S,    KC_R,    KC_N,     KC_M,      KC_ENT,      KC_PGDN,
    CA(SFT),  CA_AGRV,    KC_Y,    KC_X,  KC_DOT,    KC_K,       _______,     CA_QUOT,    KC_Q,    KC_G,    KC_H,    KC_F,  CA_CCED,            KC_UP,
    _______,  _______,       _______,          _______,    _______, CA(SFT),  _______,        MO(LR_CA_BEPO_AGR),     _______, _______, _______, _______, _______),
    //
  [LR_CA_BEPO_SFT] = LAYOUT(
    _______,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,       _______,            _______,
    M(M_TILD),  M(M_1),  M(M_2),  M(M_3),  M(M_4),    M(M_5),                    M(M_6),  M(M_7),  M(M_8),  M(M_9),  M(M_0), M(M_DEGR), KC_HASH,       _______,
    _______,   _______, _______, _______, _______,   _______,                   _______, _______, _______, _______, _______,   _______, KC_EXLM, M(M_PIPE), _______,
    _______,   _______, _______, _______, _______, M(M_SCLN),      _______,     _______, _______, _______, _______, _______,   _______,      _______,       _______,
    _______,   _______, _______, _______, KC_COLN,   _______,      _______,     CA_QUES, _______, _______, _______, _______,   _______,              _______,
    _______,   _______,      _______,          _______,       _______, _______,      _______,           _______,    _______,   _______, _______,   _______, _______),
    //
  [LR_CA_BEPO_AGR] = LAYOUT(
    _______,  _______, _______, _______,   _______, _______, _______, _______, _______,  _______, _______, _______, _______,       _______,        _______,
    _______,  _______, CA_LCBR,  CA_RCBR, CA_LBRC, CA_RBRC,                    _______, _______,  _______, _______, _______, _______, _______,     _______,
    _______,  _______, _______, KC_AMPR,     CA_OE, _______,                   _______,  _______, _______, _______, _______, _______, _______, _______, _______,
    _______,    CA_AE, CA_UGRV, _______,   _______, _______,      _______,     _______,  _______, _______, _______, _______, _______,     _______,      _______,
    _______,  _______, _______, _______, MCP(ELPS), _______,      _______,     _______,  _______, _______, _______, _______, _______,          _______,
    _______,  _______,      _______,       KC_UNDS,          _______, _______,      KC_UNDS,           _______,     _______, _______, _______, _______, _______)
};

void hold_shift(void) {
    register_code(KC_LSHIFT);
}

void release_shift(void) {
    unregister_code(KC_LSHIFT);
}

void sync_shift_with_csa_layer(void) {
    if (IS_LAYER_ON(LR_CA_BEPO_SFT) && !IS_LAYER_ON(LR_CA_BEPO_AGR_SFT)) {
        hold_shift();
    } else {
        release_shift();
    }
}


uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_P0;
    } else if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

void send_cp1252(uint16_t cp1252)
{
    // For more info on how this works, see first method of http://www.georgehernandez.com/h/xComputers/CharacterSets/Shortcuts.asp#windows
    // Pressing ALT followed by 0 and the CP1252 decimal code point.
    register_code(KC_LALT);

    uint16_t remainder = cp1252;
    // voluntarily starting with i > 256 so that we start with a 0
    for (int i = 1000; i > 0; i /= 10) {
        int hex = remainder / i;
        remainder = remainder % i;
        register_code(hextokeycode(hex));
        unregister_code(hextokeycode(hex));
    }

    unregister_code(KC_LALT);
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
        case 0 ... END_UC:
            if (record->event.pressed) {
                send_cp1252(cp1252_chars[id]);
            }
            break;
        case M_CA_SFT:
            // BÉPO over CA: toggle shift layer
            layer_invert(LR_CA_BEPO_SFT);
            sync_shift_with_csa_layer();
            break;
        case M_1 ... M_0:
        case M_DEGR:
        case M_SCLN:
        case M_PIPE:
        case M_TILD:
            // macros of the shift layer that require to release shift
            if (record->event.pressed) {
                release_shift();
                switch (id) {
                    case M_1 ... M_0:
                        register_code(KC_1 + (id - M_1));
                        break;
                    case M_DEGR:
                        return MACRO(DOWN(KC_ALGR), D(SCLN), END);
                    case M_SCLN:
                        return MACRO(D(SCLN), END);
                    case M_PIPE:
                        return MACRO(DOWN(KC_ALGR), D(GRV), END);
                    case M_TILD:
                        return MACRO(DOWN(KC_ALGR), D(RBRC), END);
                }
            } else {
                sync_shift_with_csa_layer();
                switch (id) {
                    case M_1 ... M_0:
                        unregister_code(KC_1 + (id - M_1));
                        break;
                    case M_DEGR:
                        return MACRO(UP(KC_ALGR), U(SCLN), END);
                    case M_SCLN:
                        return MACRO(U(SCLN), END);
                    case M_PIPE:
                        return MACRO(UP(KC_ALGR), U(GRV), END);
                    case M_TILD:
                        return MACRO(UP(KC_ALGR), U(RBRC), END);
                } 
            }
            break;
    }
     return MACRO_NONE;
};


layer_state_t layer_state_set_user(layer_state_t state) {
    //switch (get_highest_layer(state)) {
    switch (biton32(state)){
    case LR_CA_BEPO:
    case LR_CA_BEPO_SFT:
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_TEAL);
        //rgb_matrix_sethsv_noeeprom(0xF0, 0xF0, 0xF0);
        break;
    case LR_BASE_FN:
        //rgb_matrix_set_color_all (0xFF,  0x00, 0x00);
        break;
    default: //  for any other layers, or the default layer
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_GOLD);
        break;
    }
  return state;
}
