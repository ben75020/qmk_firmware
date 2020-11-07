#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_extras/keymap_colemak.h"
#include "keymap_extras/sendstring_colemak.h"

#define BASE 0 // default layer
#define QWTY 1
#define SYMB 2 // symbols
#define AIGU 3
#define GRAV 4
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
  CEDIL,
  EAIGU,
  EGRAV,
  OGRAV,
  UGRAV
};

extern rgblight_config_t rgblight_config;

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, RGB_CYAN}
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer    // Default layer
);

//Set the appropriate layer color
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
  	layer_state_set_user(layer_state);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

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
 *   | Ctrl |  L2  | Alt  | Aigu | Grav |                                       | left | Down |  up  |right | PAUSE  |
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

        KC_RCTL,        MO(SYMB),     KC_LALT,    MO(AIGU),   RALT(CM_R),

                                                                          KC_PSCR,  KC_LBRACKET,
                                                                                    KC_HOME,
                                                              KC_SPACE,   KC_BSPC,  KC_END,

        // right hand
        KC_EQUAL,       KC_6,         KC_7,       KC_8,       KC_9,       KC_0,     KC_BSPC,
        MO(SYMB),       CM_J,         CM_L,       CM_U,       CM_Y,       CM_SCLN,  KC_BSLS,
                        CM_H,         CM_N,       CM_E,       CM_I,       CM_O,     KC_QUOT,
        KC_QUOT,        CM_K,         CM_M,       KC_COMMA,   KC_DOT,     KC_SLSH,  KC_RSHIFT,

                                      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT, KC_PAUSE,


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
       RGB_MOD,      TG(QWTY), KC_AT,     KC_LCBR,    KC_RCBR,    KC_PIPE,  KC_TRNS,
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
// accents aigus 
[AIGU] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, AGRAV,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, CEDIL,   KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
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
// accents graves
[GRAV] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, AGRAV,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, CEDIL,   KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, UGRAV,      KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, EAIGU,      KC_TRNS, KC_TRNS, KC_TRNS,
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
      return false;
      break;
  // Test macro 1
    case AGRAV:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("r") "a");
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
    case OGRAV:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("r") "o");
      }
      break;
    case UGRAV:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("r") "u");
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
// This is for Linux Unicode, but we tend to avoid using it.
void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
  rgblight_enable();
  rgblight_sethsv_cyan();
  rgblight_mode(1);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case BASE:
            ergodox_right_led_1_off();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();
            break;
        case SYMB:
            ergodox_right_led_1_off();
            ergodox_right_led_2_on();
            ergodox_right_led_3_off();
            break;
        case QWTY:
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
