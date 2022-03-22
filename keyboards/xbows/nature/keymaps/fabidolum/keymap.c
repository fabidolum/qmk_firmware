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
//#include "action_layer.h"
//#include "action_util.h"
#include "keymap_extras/keymap_bepo.h"
#include "keymap_extras/keymap_canadian_multilingual.h"
//#include "keymap_extras/keymap_french_afnor.h"

/* purpose:
 * US keyboard on OS side => send the key corresponding to the keycap etching
 * Canadian Multilingual on OS side: toggle to the layer LR_ASC_BEPO and get a custom bépo layout
 * Bepo on OS side: toggle to the layer LR_FR_BEPO and get the same custom bépo layout plus the missing char from canandian (euro sign, ...)
 *
 * Toggling : use the PrintScreen key (who uses it?)
 * Color indicator (leds) depending on QWERTY or BEPO(ASC)
 *
 * Keep the original (X-bows nature) Fn layer.
 */

/* note: based on : 
https://github.com/qmk/qmk_firmware/blob/master/layouts/community/ergodox/bepo_csa/keymap.c
*/

/*enum layers {
    LR_BASE,     // almost original layer: qwerty
    LR_CA_BEPO,  // custom bépo using Canadian Multilanguage (CA)
    LR_CA_BEPO_SFT,       // shifted
    LR_CA_BEPO_AGR,       // alt-gr
    LR_CA_BEPO_AGR_SFT,
    LR_BASE_FN,          // original fn layer
};
*/

#define LR_BASE 0         // almost original layer: qwerty
#define LR_CA_BEPO 1      // same as bépo but using Canadian Multilanguage (CA)
#define LR_FR_BEPO 2
#define LR_CA_BEPO_SFT 3  // shifted
#define LR_CA_BEPO_AGR 4  // alt-gr
#define LR_CA_BEPO_AGR_SFT 5
#define LR_FR_BEPO_SFT 6
#define LR_BASE_FN 8   // original fn layer

enum custom_keycodes {
    CSA_SFT = SAFE_RANGE,
    BPI_SFT,
//    IDO_EURO,
//    CSA_AGR_SFT,
//    CSA_SFT_AGR,
};

// https://github.com/JonasGessner/qmk_firmware/blob/key-overrides/docs/feature_key_overrides.md

//CA_GRV,  
const key_override_t keytil_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_GRV,  CA_TILD, LR_CA_BEPO_SFT);
//CA_DQUO,
const key_override_t keyone_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_DQUO, CA_1,    LR_CA_BEPO_SFT);
//CA_LABK, 
const key_override_t keytwo_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_LABK, CA_2,    LR_CA_BEPO_SFT);
//CA_RABK, 
const key_override_t keythr_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_RABK, CA_3,    LR_CA_BEPO_SFT);
//CA_LPRN, 
const key_override_t keyfou_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_LPRN, CA_4,    LR_CA_BEPO_SFT);
//CA_RPRN, 
const key_override_t keyfiv_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_RPRN, CA_5,    LR_CA_BEPO_SFT);
//CA_AT
const key_override_t keysix_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_AT,   CA_6,    LR_CA_BEPO_SFT);
//CA_PLUS
const key_override_t keysev_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_PLUS, CA_7,    LR_CA_BEPO_SFT);
//CA_MINS
const key_override_t keyhei_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_MINS, CA_8,    LR_CA_BEPO_SFT);
//CA_SLSH
const key_override_t keynin_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_SLSH, CA_9,    LR_CA_BEPO_SFT);
//CA_ASTR
const key_override_t keyzer_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_ASTR, CA_0,    LR_CA_BEPO_SFT);
//CA_EQL
const key_override_t keydeg_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_EQL,  CA_DEG,  LR_CA_BEPO_SFT);
//CA_DLR
const key_override_t keyhas_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_DLR,  CA_HASH, LR_CA_BEPO_SFT);
//CA_BSLS
const key_override_t keypip_override = ko_make_with_layers(MOD_MASK_SHIFT, CA_BSLS, CA_PIPE, LR_CA_BEPO_SFT);
//KC_COMM
const key_override_t keyscl_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, CA_SCLN, LR_CA_BEPO_SFT);

// BP_GRV
//const key_override_t keybptil_override = ko_make_with_layers(MOD_MASK_SHIFT, BP_GRV, BP_TILD, LR_FR_BEPO_SFT);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&keyone_override,
    &keytil_override,
    &keytwo_override,
    &keythr_override,
    &keyfiv_override,
    &keyfou_override,
    &keysix_override,
    &keysev_override,
    &keyhei_override,
    &keynin_override,
    &keyzer_override,
    &keydeg_override,
    &keyhas_override,
    &keypip_override,
    &keyscl_override,
//    &keybptil_override,
	NULL // Null terminate the array of overrides!
};

//void matrix_init_user(void) {
//    set_unicode_input_mode(UC_LNX);
//};


/*enum macros {
    // Characters that do not exist in CSA and must be implemented based on unicode support
    // Note: these are intentionally declared first to be used as indexes in spec_chars below
    UC_NDSH, // –
    UC_MDSH, // —
    UC_ELPS, // …
    END_UC, // indicates the last unicode character macro
    // other macros
    M_CSA_SFT, // toggle shift on CSA
    M_CSA_AGR_SFT, // toggle shift on LR_CSA_AGR (goes to LR_CSA_AGR_SFT)
    M_CSA_SFT_AGR, // toggle AltGr on LR_CSA_SFT (goes to LR_CSA_AGR_SFT)
    // macros for characters that need to be un-shifted in LR_CA_MULT_SHIFT
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
    M_GRV,
    M_NBSP,
    // macros for characters that don't have a simple key combination in LR_CA_MULT_ALTGR
    M_CRC,
    // other layer macros
    M_DBL0, // double 0
    M_FNLR, // fn layer
    M_NMAL, // num+alt
};
*/
/*enum macros {
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
*/
/*
#define CSA(name)   M(M_CSA_##name)     // calls a CSA macro

const uint16_t unicode_chars[] = {
        [UC_NDSH] = L'–',
        [UC_MDSH] = L'—',
        [UC_ELPS] = L'…',
};
*/
// call CA macro
//#define CA(name)   M(M_CA_##name)  

/*const uint16_t cp1252_chars[] = {
        [CP_NDSH] = 0x96,
        [CP_MDSH] = 0x97,
        [CP_ELPS] = 0x85,
};
*/
/* shortcut for CP1252 character macros */
//#define MCP(name)   M(CP_##name)    // calls a unicode macro

/* shortcut for unicode character macros */
// #define MUC(name)   M(UC_##name)    // calls a unicode macro

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
    
  */

/* Original bépo (keymap_bepo.h)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ $ │ " │ « │ » │ ( │ ) │ @ │ + │ - │ / │ * │ = │ % │       │* │ ` │ " │ < │ > │ ( │ ) │       │ @ │ + │ - │ / │ * │ = │ $ │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │ B │ É │ P │ O │ È │ ^ │ V │ D │ L │ J │ Z │ W │     │* │tab│ b │ é │ p │ o │ è │       │ w │ v │ d │ l │ j │ z │ ^ │ \ │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │ A │ U │ I │ E │ , │ C │ T │ S │ R │ N │ M │ Ç │    │* │clk│ a │ u │ i │ e │ , │   %   │ c │ t │ s │ r │ n │ m │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │ Ê │ À │ Y │ X │ . │ K │ ' │ Q │ G │ H │ F │          │* │sft│ à │ y │ x │ . │ k │       │ ' │ q │ g │ h │ f │ ç │   │ ↑ │   │
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
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ ` │       │* │ ~ │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │ = │ # │  bksp │
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
 /*
 `1“”4567890-#
 BÉPOÈWVDLJZ! 
 AUIE;`CTSRNM
 ÀYX:K ?QnHFÇ
 
 */
/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ – │ — │ < │ > │ [ │ ] │ ^ │ ± │ − │ ÷ │ × │ ≠ │ ‰ │       │* │   │   │ « │ » │ [ │ ] │       │ { │ } │   │   │   │   │   │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │ | │ ´ │ & │ Œ │ ` │ ¡ │ ˇ │ Ð │ / │ Ĳ │ Ə │ ˘ │     │* │tab│   │   │   │ œ │   │       │   │   │   │   │   │   │   │   │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │ Æ │ Ù │ ¨ │ € │   │ © │ Þ │ ẞ │ ® │ ~ │ ¯ │ ¸ │    │* │clk│ æ │ ù │   │ € │   │       │   │   │   │   │   │ µ │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │   │ \ │ { │ } │ … │ ~ │ ¿ │ ° │   │ † │ ˛ │          │* │sft│   │   │   │   │   │       │   │   │   │   │   │   │   │ ↑ │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤* ├───┼───┼───┴───┼───┴───┼───┬───┼───┴───┼───┴───┼───┼───┼───┼───┼───┤
 * │    │    │    │           _            │    │    │    │    │* │ctr│gui│  alt  │   _   │ctr│sft│   _   │  alt  │ fn│ctr│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘* └───┴───┴───────┴───────┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
 */
 // the € is not available with CA(intl).
/* Shift+AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐* ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¶ │ „ │ “ │ ” │ ≤ │ ≥ │   │ ¬ │ ¼ │ ½ │ ¾ │ ′ │ ″ │       │* │   │   │   │   │   │   │       │   │   │   │   │   │   │   │  bksp │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤* ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┼───┼───┬───┤
 * │     │ ¦ │ ˝ │ § │   │   │   │   │   │   │   │   │   │     │* │tab│   │   │   │ Œ │   │       │   │   │   │   │   │   │   │   │pgu│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │      │   │   │ ˙ │ ¤ │ ̛ │ ſ │   │   │ ™ │   │ º │ , │    │* │clk│ Æ │ Ù │   │   │   │       │   │   │   │   │   │   │ enter │pgd│
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤* ├───┼───┼───┼───┼───┼───┼───────┼───┼───┼───┼───┼───┼───┼───┬───┼───┤
 * │    │   │   │ ‘ │ ’ │ · │ ⌨ │ ̉  │ ̣  │   │ ‡ │ ª │          │* │sft│   │   │   │   │   │       │   │   │   │   │   │   │   │ ↑ │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤* ├───┼───┼───┴───┼───┴───┼───┬───┼───┴───┼───┴───┼───┼───┼───┼───┼───┤
 * │    │    │    │                        │    │    │    │    │* │ctr│gui│  alt  │       │ctr│sft│       │  alt  │ fn│ctr│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘* └───┴───┴───────┴───────┴───┴───┴───────┴───────┴───┴───┴───┴───┴───┘
 */


  [LR_CA_BEPO] = LAYOUT(
    _______,  _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,      _______,          TO(LR_FR_BEPO),
     CA_GRV,  CA_DQUO, CA_LABK, CA_RABK, CA_LPRN,  CA_RPRN,                     CA_AT, CA_PLUS, CA_MINS, CA_SLSH, CA_ASTR,   CA_EQL, CA_DLR,      KC_BSPC,
    _______,     KC_B, CA_EACU,    KC_P,    KC_O,  CA_EGRV,                         KC_W,    KC_V,    KC_D,    KC_L,    KC_J,     KC_Z, CA_CIRC, CA_BSLS, _______,
    _______,     KC_A,    KC_U,    KC_I,    CA_E,  KC_COMM,       CA_PERC,          KC_C,    KC_T,    KC_S,    KC_R,    KC_N,     KC_M,      KC_ENT,      KC_PGDN,
    CSA_SFT,  CA_AGRV,    KC_Y,    KC_X,  KC_DOT,     KC_K,       _______,      CA_QUOT,    KC_Q,    KC_G,    KC_H,    KC_F,  CA_CCED,            KC_UP,
    _______,  _______,       _______,          _______,    _______,   CSA_SFT,     _______,   MO(LR_CA_BEPO_AGR), _______, _______, _______, _______, _______),
    //
  [LR_CA_BEPO_SFT] = LAYOUT(
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,            _______,
    _______,   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______,
    _______,   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, CA_1, _______, _______,
    _______,   _______, _______, _______, _______, _______,        CA_7,      _______, _______, _______, _______, _______, _______,      _______,       _______,
    _______,   _______, _______, _______, CA_SCLN, _______,      _______,     CA_QUES, _______, _______, _______, _______, _______,              _______,
    _______,   _______,      _______,          _______,     _______, _______,      _______,           _______,    _______, _______, _______,   _______, _______),
    //
  [LR_CA_BEPO_AGR] = LAYOUT(
    _______,  _______, _______, _______,   _______, _______, _______, _______, _______,  _______, _______, _______, _______,       _______,        _______,
    _______,  _______, CA_LDAQ,  CA_RDAQ, CA_LBRC, CA_RBRC,                    CA_LCBR, CA_RCBR,  _______, _______, _______, _______, _______,     _______,
    _______,  _______, _______, _______,     CA_OE, _______,                   _______,  _______, _______, _______, _______, _______, _______, _______, _______,
    _______,    CA_AE, CA_UGRV, _______,   _______, _______,      _______,     _______,  _______, _______, _______, _______, CA_MICR,     _______,      _______,
    _______,  _______, _______, _______, _______, _______,      _______,     _______,  _______, _______, _______, _______, _______,          _______,
    _______,  _______,      _______,       KC_UNDS,          _______, _______,      KC_UNDS,           _______,     _______, _______, _______, _______, _______),
//
  [LR_FR_BEPO] = LAYOUT(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,       _______,        TO(LR_BASE),
     BP_GRV,  _______, BP_LABK, BP_RABK, _______, _______,                    _______, _______,  _______, _______, _______, _______, BP_DLR,     _______,
    _______,  _______, _______, _______, _______, _______,                      BP_W,  _______, _______, _______, _______, _______, BP_DCIR, BP_BSLS, _______,
    _______,  _______, _______, _______, _______, _______,      BP_PERC,     _______,  _______, _______, _______, _______, _______,     _______,      _______,
    BPI_SFT,  _______, _______, _______, _______, _______,      _______,     _______,  _______, _______, _______, _______, BP_CCED,           _______,
    _______,  _______,      _______,       _______,          _______, BPI_SFT,      _______,         _______,     _______, _______, _______, _______, _______),

 [LR_FR_BEPO_SFT] = LAYOUT(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,       _______,        TO(LR_BASE),
    BP_TILD,  _______, BP_LABK, BP_RABK, _______, _______,                    _______, _______,  _______, _______, _______, _______, BP_DLR,     _______,
    _______,  _______, _______, _______, _______, _______,                      BP_W,  _______, _______, _______, _______, _______, BP_DCIR, BP_BSLS, _______,
    _______,  _______, _______, _______, _______, _______,      BP_PERC,     _______,  _______, _______, _______, _______, _______,     _______,      _______,
    _______,  _______, _______, _______, _______, _______,      _______,     _______,  _______, _______, _______, _______, BP_CCED,           _______,
    _______,  _______,      _______,       _______,          _______, _______,      _______,         _______,     _______, _______, _______, _______, _______)

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

/*
uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_P0;
    } else if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}
*/
/*
void send_unicode(uint16_t unicode)
{
    // For more info on how this works per OS, see here: https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input
    // Implemented for Windows:
    // Pressing ALT followed by + followed by the unicode code point in hex.
    // Requires registry key HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad set to String 1
    register_code(KC_LALT);
    register_code(KC_PPLS);
    unregister_code(KC_PPLS);

    for (int i = 12; i >= 0; i -= 4) {
        register_code(hextokeycode((unicode >> i) & 0xF));
        unregister_code(hextokeycode((unicode >> i) & 0xF));
    }

    unregister_code(KC_LALT);
}
*/
/*void send_cp1252(uint16_t cp1252)
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
*/

/*
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
*/

/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
        case 0 ... END_UC:
            if (record->event.pressed) {
                send_unicode(unicode_chars[id]);
            }
            break;
        case M_CSA_SFT:
            // BÉPO over CSA: toggle shift layer
            layer_invert(LR_CSA_SFT);
            if (record->event.pressed) {
                hold_shift();
            } else {
                release_shift();
            }
            break;
        case M_CSA_SFT_AGR:
            // BÉPO over CSA: from shift layer, momentary altgr+shift layer
            layer_invert(LR_CSA_AGR);
            layer_invert(LR_CSA_AGR_SFT);
            if (record->event.pressed) {
                // shift not needed for LR_CSA_AGR_SFT
                release_shift();
            } else {
                // back to shift layer
                hold_shift();
            }
            break;
        case M_CSA_AGR_SFT:
            // BÉPO over CSA: from altgr layer, momentary altgr+shift layer
            layer_invert(LR_CSA_SFT);
            layer_invert(LR_CSA_AGR_SFT);
            break;
        case M_1 ... M_0:
        case M_DEGR:
        case M_SCLN:
        case M_GRV:
        case M_NBSP:
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
                    case M_GRV:
                        return MACRO(I(75), DOWN(KC_ALGR), TYPE(CA_CIRC), UP(KC_ALGR), T(SPACE), END);
                    case M_NBSP:
                        // use weak mod such that pressing another key will not be affected
                        add_weak_mods(MOD_BIT(KC_ALGR));
                        return MACRO(D(SPACE), END);
                }
            } else {
                hold_shift();
                switch (id) {
                    case M_1 ... M_0:
                        unregister_code(KC_1 + (id - M_1));
                        break;
                    case M_DEGR:
                        return MACRO(UP(KC_ALGR), U(SCLN), END);
                    case M_SCLN:
                        return MACRO(U(SCLN), END);
                    case M_NBSP:
                        del_weak_mods(MOD_BIT(KC_ALGR));
                        return MACRO(U(SPACE), END);
                }
            }
            break;
        case M_CRC:
            if (record->event.pressed) {
                return MACRO(I(75), TYPE(CA_CIRC), T(SPACE), END);
            }
            break;
        case M_DBL0:
            if (record->event.pressed) {
                return MACRO( I(25), T(P0), T(P0), END );
            }
        break;
        case M_FNLR:
            layer_invert(LR_NUMR);
            layer_invert(LR_FN);
            break;
        case M_NMAL:
            layer_invert(LR_NUMR);
            if (record->event.pressed) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
            break;
    }
    return MACRO_NONE;
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CSA_SFT:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            //layer_invert(LR_CA_BEPO_SFT);
            //sync_shift_with_csa_layer();
            hold_shift();
            layer_on(LR_CA_BEPO_SFT);
        } else {
            // when keycode QMKBEST is released
            layer_off(LR_CA_BEPO_SFT);
            release_shift();
        }
        break;
    case BPI_SFT:
        if (record->event.pressed) {
            hold_shift();
            layer_on(LR_FR_BEPO_SFT);
        } else {
            layer_off(LR_FR_BEPO_SFT);
            release_shift();
        }
        break;
//    case IDO_EURO: 
//        if (record->event.pressed) {
//            SEND_STRING("blq. €"); // REPLACE with what you want your macro to be
//        }
//        break;


/*    case CSA_SFT_AGR:
        // BÉPO over CSA: from shift layer, momentary altgr+shift layer
        layer_invert(LR_CA_BEPO_AGR);
        layer_invert(LR_CA_BEPO_AGR_SFT);
        if (record->event.pressed) {
            // shift not needed for LR_CSA_AGR_SFT
            release_shift();
        } else {
            // back to shift layer
            hold_shift();
        }
        break;

    case CSA_AGR_SFT:
        // BÉPO over CSA: from altgr layer, momentary altgr+shift layer
        layer_invert(LR_CA_BEPO_SFT);
        layer_invert(LR_CA_BEPO_AGR_SFT);
        break;
        */
    }
    return true;
};


//void rgb_matrix_indicators_user(void) {
//    if (layer_state_cmp(state, 1))
//    if (host_keyboard_led_state().caps_lock) {
//        rgb_matrix_set_color(14, 0xFF, 0xFF, 0xFF);
//    }
//}
layer_state_t layer_state_set_user(layer_state_t state) {
    //switch (get_highest_layer(state)) {
    switch (biton32(state)){
        case LR_FR_BEPO:
        case LR_FR_BEPO_SFT:
 //       rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_RED);
 //       rgb_matrix_set_color_all(0x88, 0X00, 0X00);
//        rgb_matrix_set_color(14, 0x00, 0x00, 0xFF);
        break;
    case LR_CA_BEPO:
    case LR_CA_BEPO_SFT:
 //       rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_TEAL);
//        rgb_matrix_set_color(14, 0xFF, 0x00, 0x00);
//        //rgb_matrix_sethsv_noeeprom(0xF0, 0xF0, 0xF0);
        break;
    case LR_BASE_FN:
        //rgb_matrix_set_color_all (0xFF,  0x00, 0x00);
//        rgb_matrix_set_color(14, 0x00, 0x0FF, 0x00);
        rgb_matrix_sethsv_noeeprom(HSV_AZURE);
        break;
    default: //  for any other layers, or the default layer
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_GOLD);
//        rgb_matrix_set_color(14, 0xFF, 0xFF, 0xFF);
        break;
    }
  return state;
}

