#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_extras/keymap_colemak.h"
#include "keymap_extras/sendstring_colemak.h"

#define BASE 0 // default layer
#define QWTY 1
#define SYMB 2 // symbols
#define AIGU 3
#define GRAV 4
#define CIRC 5
#define ALTL 6

// We are NOT using UNICODE.
enum unicode_name {
    a_grave = 0x00e0, // à
    e_grave = 0x00e8, // è
    u_grave = 0x00f9, // ù
    e_aigue = 0x00e9, // é
    c_cedil = 0x00e0 // ç
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  AGRAV,
  ACIRC,
  CEDIL,
  EAIGU,
  EGRAV,
  ECIRC,
  ICIRC,
  OCIRC,
  UGRAV,
  UCIRC,
  GMEET
};



/////////////////////////////////////////////////////////////////////////////////////////////////////
// KEYMAPS DEFINITION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Escape |   1  |   2  |   3  |   4  |   5  |   `  |           |   =  |   6  |   7  |   8  |   9  |   0  | BkSp   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   q  |   w  |   f  |   p  |   g  |  L2  |           |  L2  |   j  |   l  |   u  |   y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab    |   a  |   r  |   s  |   t  |   d  |------|           |------|   h  |   n  |   e  |   i  |   o  |   '    |
 * |--------+------+------+------+------+------|   -  |           |  '   |------+------+------+------+------+--------|
 * | Shift  |   w  |   x  |   c  |   v  |   b  |      |           |      |   k  |   m  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  L2  | Alt  | Aigu | Aigu |                                       | grav | left | Down |  up  | right  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |Print |  {   |       |  }   |   Del  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,       KC_3,       KC_4,       KC_5,     KC_GRV,
        KC_BSPC,        CM_Q,         CM_W,       CM_F,       CM_P,       CM_G,     MO(SYMB),
        KC_TAB,         CM_A,         CM_R,       CM_S,       CM_T,       CM_D,
        KC_LSHIFT,      CM_Z,         CM_X,       CM_C,       CM_V,       CM_B,     KC_MINS,

        KC_RCTL,        MO(SYMB),     KC_LALT,    KC_LALT,    MO(AIGU),

                                                                          KC_PSCR,  KC_LBRACKET,
                                                                                    KC_HOME,
                                                              KC_SPACE,   KC_BSPC,  KC_END,

        // right hand
        KC_EQUAL,       KC_6,         KC_7,       KC_8,       KC_9,       KC_0,     KC_BSPC,
        MO(SYMB),       CM_J,         CM_L,       CM_U,       CM_Y,       CM_SCLN,  KC_BSLS,
                        CM_H,         CM_N,       CM_E,       CM_I,       CM_O,     KC_QUOT,
        KC_QUOT,        CM_K,         CM_M,       KC_COMMA,   KC_DOT,     KC_SLSH,  KC_RSHIFT,

                                      MO(GRAV),   KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,


        KC_RBRACKET,    KC_DEL,
        KC_PGUP,
        KC_PGDN,        KC_LSHIFT,KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         | QWTY |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  | BASE |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * | EEP_RST  |RESET|      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       RGB_TOG,      KC_F1,    KC_F2,     KC_F3,      KC_F4,      KC_F5,    KC_TRNS,
       RGB_MOD,      TG(QWTY), KC_AT,     KC_LCBR,    KC_RCBR,    GMEET,  KC_TRNS,
       KC_TRNS,      KC_HASH,  KC_DLR,    KC_LPRN,    KC_RPRN,    KC_GRV,
       KC_TRNS,      KC_PERC,  KC_CIRC,   TG(BASE),   KC_RBRC,    KC_TILD,  KC_TRNS,
       EEP_RST,      RESET,    KC_TRNS,   KC_TRNS,    KC_TRNS,
                                          RGB_MOD,    KC_TRNS,
                                                      KC_TRNS,
                               RGB_VAD,   RGB_VAI,    KC_TRNS,
       // right hand
       KC_TRNS,      KC_F6,    KC_F7,     KC_F8,      KC_F9,      KC_F10,  KC_F11,
       KC_TRNS,      KC_UP,    KC_7,      KC_8,       KC_9,       KC_ASTR, KC_F12,
                     KC_DOWN,  KC_4,      KC_5,       KC_6,       KC_PLUS, KC_TRNS,
       KC_TRNS,      KC_AMPR,  KC_1,      KC_2,       KC_3,       KC_BSLS, KC_TRNS,
                               KC_TRNS,   KC_DOT,     KC_0,       KC_EQL,  KC_TRNS,
       RGB_TOG,      KC_TRNS,
       KC_TRNS,
       KC_TRNS,      RGB_HUD, RGB_HUI
),
/* Keymap 2: Aecute accents
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   à  |      |      |      |      |------|           |------|      |      |  é   |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  ç   |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | CIRC |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// accents aigus 
[AIGU] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, AGRAV,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, CEDIL,   KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, MO(CIRC),
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, EAIGU,      KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Grave accents
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |  ù   |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   à  |      |      |      |      |------|           |------|      |      |  è   |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  ç   |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | CIRC |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// accents graves
[GRAV] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, AGRAV,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, CEDIL,   KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, MO(CIRC), KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, UGRAV,      KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, EGRAV,      KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 4: circumflexes accents
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |  û   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   â  |      |      |      |      |------|           |------|      |      |  ê   |      |  ô   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  ç   |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// accents circumflexes 
[CIRC] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, ACIRC,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, CEDIL,   KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, UCIRC,      KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, ECIRC,      ICIRC,   OCIRC,   KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 5: Qwerty Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[QWTY] = LAYOUT_ergodox(
        // left hand
        KC_ESC,         KC_1,         KC_2,       KC_3,       KC_4,       KC_5,     KC_GRV,
        KC_BSPC,        KC_Q,         KC_W,       KC_F,       KC_P,       KC_G,     MO(SYMB),
        KC_TAB,         KC_A,         KC_R,       KC_S,       KC_T,       KC_D,
        KC_LSHIFT,      KC_Z,         KC_X,       KC_C,       KC_V,       KC_B,     KC_MINS,

        KC_RCTL,        MO(SYMB),     KC_LALT,    MO(AIGU),   RALT(CM_R),

                                                                          KC_PSCR,  KC_LBRACKET,
                                                                                    KC_HOME,
                                                              KC_SPACE,   KC_BSPC,  KC_END,

        // right hand
        KC_EQUAL,       KC_6,         KC_7,       KC_8,       KC_9,       KC_0,     KC_BSPC,
        MO(SYMB),       KC_J,         KC_L,       KC_U,       KC_Y,       KC_SCLN,  KC_BSLS,
                        KC_H,         KC_N,       KC_E,       KC_I,       KC_O,     KC_QUOT,
        KC_QUOT,        KC_K,         KC_M,       KC_COMMA,   KC_DOT,     KC_SLSH,  KC_RSHIFT,

                                      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT, KC_PAUSE,


        KC_RBRACKET,    KC_DEL,
        KC_PGUP,
        KC_PGDN,        KC_LSHIFT,KC_ENT
    ),
};

// MACROS DEFINITION
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case AGRAV:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("r") "a");
      }
      break;
    case ACIRC:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("x") "a");
      }
      break;
    case CEDIL:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("c"));
      }
      break;
    case EAIGU:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("e"));
      }
      break;
    case EGRAV:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("r") "e");
      }
      break;
    case ECIRC:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("x") "e");
      }
      break;
    case OCIRC:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("x") "o");
      }
      break;
    case UGRAV:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("r") "u");
      }
      break;
    case UCIRC:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("x") "u");
      }
      break;
    case GMEET:
      if (record->event.pressed) {
        SEND_STRING("Meet on : https://meet.google.com/bjm-wixq-xnr \n");
        SEND_STRING(SS_LALT("d") SS_DELAY(300));
        SEND_STRING("i3-msg 'workspace 0; exec /usr/bin/google-chrome --app=https://meet.google.com/bjm-wixq-xnr'\n");
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
// This is for Linux Unicode, but we tend to avoid using it.
void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
};
// This code is only executed at each layer change
void rgb_matrix_indicators_user(void) {
    switch(get_highest_layer(layer_state)) {
      case AIGU:
           rgb_matrix_set_color_all(0, 0, 0);
           rgb_matrix_set_color(12, 0, 255, 0);
           rgb_matrix_set_color(14, 0, 255, 0);
           rgb_matrix_set_color(7, 0, 255, 0);
           rgb_matrix_set_color(38, 0, 255, 0);
           rgb_matrix_set_color(41, 0, 255, 0);
      break;
      case GRAV:
           rgb_matrix_set_color_all(0, 0, 0);
           rgb_matrix_set_color(12, 255, 0, 0);
           rgb_matrix_set_color(14, 255, 0, 0);
           rgb_matrix_set_color(7, 255, 0, 0);
           rgb_matrix_set_color(38, 255, 0, 0);
           rgb_matrix_set_color(41, 255, 0, 0);
      break;
      case CIRC:
           rgb_matrix_set_color_all(0, 0, 0);
           rgb_matrix_set_color(7, 255, 255, 0);
           rgb_matrix_set_color(12, 255, 255, 0);
           rgb_matrix_set_color(14, 255, 255, 0);
           rgb_matrix_set_color(38, 255, 255, 0);
           rgb_matrix_set_color(41, 255, 255, 0);
      break;
      case SYMB:
           rgb_matrix_set_color_all(0, 0, 0);
           rgb_matrix_set_color(0, 255, 0, 0);
           rgb_matrix_set_color(1, 255, 0, 0);
           rgb_matrix_set_color(2, 255, 0, 0);
           rgb_matrix_set_color(3, 255, 0, 0);
           rgb_matrix_set_color(4, 255, 0, 0);
           rgb_matrix_set_color(24, 255, 0, 0);
           rgb_matrix_set_color(25, 255, 0, 0);
           rgb_matrix_set_color(26, 255, 0, 0);
           rgb_matrix_set_color(27, 255, 0, 0);
           rgb_matrix_set_color(28, 255, 0, 0);
           rgb_matrix_set_color(29, 138, 43, 226);
           rgb_matrix_set_color(33, 0, 0, 244);
           rgb_matrix_set_color(47, 255, 0, 0);

      break;
      case ALTL:
           rgb_matrix_set_color_all(0, 0, 0);
           rgb_matrix_set_color(47, 255, 0, 0);
           rgb_matrix_set_color(29, 255, 255, 255);
           rgb_matrix_set_color(33, 0, 0, 244);

      break;
      case QWTY:
            rgb_matrix_set_color_all(0, 0, 244);
      break;

      default:
            rgb_matrix_enable();
      break;
    }
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case SYMB:
            ergodox_right_led_1_off();
            ergodox_right_led_2_on();
            ergodox_right_led_3_off();
            break;
        case QWTY:
//            rgb_matrix_set_color_all(50, 28, 244);
            ergodox_right_led_1_off();
            ergodox_right_led_2_off();
            ergodox_right_led_3_on();
            break;
        default:
            ergodox_right_led_1_off();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();
            ergodox_board_led_off();
            // none
            break;
    }
};
