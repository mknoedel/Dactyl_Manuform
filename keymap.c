// Documentation -- https://docs.qmk.fm/#/newbs_building_firmware?id=customize-the-layout-to-your-liking

// I left the matrix configuration as is, modified this file only.
// (actually I had to specify ROW2COL since in my CrocoDox I put them in the opposit direction.

#include "lets_split_dactyl_manuform.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_steno.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY 0
#define _SYMBOLS 1
#define _RIGHTNAV 2
#define _LEFTNAV 3
#define _FUNCTIONS 4
#define _EXTRARIGHT 5
#define _STENO 6
#define _PLOVER 7
#define _STENO_TXBOLT 8
#define _STENO_TXBOLT2 9
//  these two layers are transparent ones intentionally.
//  When their respective switches are held together - the extra right will be initiated.
#define _DUMMY1 10
#define _DUMMY2 11


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LEFT_NAV = LT(_LEFTNAV,KC_M),
  RIGHT_NAV = LT(_RIGHTNAV,KC_V),
  FUNCTIONS_LEFT = LT(_FUNCTIONS,KC_B),
  FUNCTIONS_RIGHT = LT(_FUNCTIONS,KC_N),
  STENO_TOGG = LT(_STENO, KC_ESC),

  PLOVER,
  EXT_PLV,
  STENO_TXBOLT,
  STENO_TXBOLT2,
  EXT_PLV2,

// These  pairs when held together - will turn on the EXTRA RIGHT layer,
// But will do nothing when held down by themselves.
// The single hit will still be their regular key.
  // E_RT = LT(_DUMMY1, KC_E),
  // R_RT = LT(_DUMMY2, KC_R)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
  ,____________________________________________________________________________________,
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |  Esc |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   ;  | BSpc |
  | STENO|      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |  Tab |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   P  | Enter|
  |  Sft |  Sft | Ctrl |  Cmd |  Alt |      ||      |  Alt |  Cmd | Ctrl |  Sft |  Sft |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |LArrow|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |RArrow|
  | Ctrl |      |      |      |  NAV |  FUN ||  FUN |  NAV |      |      |      | RCtrl|
  |______|______+------+------+______|______||______|______+------+------+______|______|
  		          |      |      |                            |      |      |
		            | LCmd | Space|                            | BSpc | RCmd |
                |______|______|                            |______|______|
                        ,_____________,            ,_____________,
                        |      |      |            |      |      |
Single hit:		          |   '  | BSpc |            | Space|   1  |
Hold:  		              |      |  Sft |            |  Sft |      |
                        |______|______|___,    ,___|______|______|
                            |      |      |    |      |      |
          	                |UArrow|SMBOLS|    |NMBERS|UArrow|
                            |      |      |    |      |      |
		                        +------+------+    +------+------+
                            |      |      |    |      |      |
 	                          |DArrow|RArrow|    |LArrow|DArrow|
                            |______|______|    |______|______|
*/
[_QWERTY] = KEYMAP( \
  STENO_TOGG,      KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                     KC_Y,            KC_U,         KC_I,         KC_O,         KC_SCLN,      KC_BSPC,          \
  LSFT_T(KC_TAB),  LSFT_T(KC_A), LCTL_T(KC_S), LCMD_T(KC_D), LALT_T(KC_F), KC_G,                     KC_H,            RALT_T(KC_J), RCMD_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_P), RSFT_T(KC_ENT),   \
  LCTL_T(KC_LEFT), KC_Z,         KC_X,         KC_C,         RIGHT_NAV,    FUNCTIONS_LEFT,           FUNCTIONS_RIGHT, LEFT_NAV,     KC_COMM,      KC_DOT,       KC_SLSH,      RCTL_T(KC_RIGHT), \
  _______,         _______,      KC_LCMD,      KC_SPC,       KC_QUOTE,     LSFT_T(KC_BSPC),          RSFT_T(KC_SPC),  KC_1,         KC_BSPC,      KC_RCMD,      _______,      _______,          \
  KC_DOWN,         KC_RIGHT,     _______,      _______,      KC_UP,        MO(_SYMBOLS),             MO(_SYMBOLS),    KC_UP,        _______,      _______,      KC_LEFT,      KC_DOWN           \
),


/*
Layers below are used on top of QWERTY layer defined above.
(Except the PLOVER/STENO layers.)
                                           +------+
The keys which are shown empty, like this: |       |, represent a transparent key,
                                           +------+
meaning the key from the underlaying layer (i.e. QWERTY) will be used.
In the keymaps those keys are defined as "_______".

                                           +------+         +------+
The keys which are shown solid, like this: | XXXX | or this |  ...  |, represent an opaque/blocking key�
                                           +------+         +------+
Such key is not doing anything in that layer nor allowing the key from the underlaying layer
to be invoked.
In the keymaps those keys are defined as "XXXXXXX".

Most of the modifiers are the same in all layers.
So in most layers they are defined as transparent keys,
letting the keys from QWERTY layer to do the work.

With that idea all the layers below leave the unmodified keys as transparent keys.
In the same time - the layers block the keys that have no sense to be used
in that given layer. For instance in the cursor control layers
some of the keys are not used in the layer, but they are blocked to avoid
alpha-keys from QWERTY layer to appear.

For the same reason the keymaps below are shown simplified,
without separate thumbcluster.
*/


/* SYMBOLS and NUMPAD
   ,____________________________________________________________________________________,
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |   <  |   >  |   {  |   }  |   ^  ||   +  |   3  |   6  |   9  |   *  |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |   \  |   [  |   ]  |   (  |   )  |   &  ||   -  |   2  |   5  |   8  |   0  |   =  |
  |      |  Sft | Ctrl |      |      |      ||      |  Alt |  Cmd | Ctrl |  Sft |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |   %  |   #  |   @  |   $  |   |  ||   .  |   1  |   4  |   7  |   /  |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |______|______+------+------+______|______||______|______+------+------+______|______|
  		          |      |      |                            |      |      |
		            | XXXX |   `  |                            |   ~  | XXXX |
                |______|______|                            |______|______|
                        ,_____________,            ,_____________,
                        |      |      |            |      |      |
           		          |   =  |   =  |            |   _  |   _  |
                        |______|______|___,    ,___|______|______|
                            |      |      |    |      |      |
          	                |   `  |   `  |    |   ~  |   ~  |
                            |      |      |    |      |      |
		                        |______|______|    |______|______|
*/
[_SYMBOLS] = KEYMAP( \
  _______,   KC_LT,           KC_GT,           KC_LCBR,  KC_RCBR,  KC_CIRC,          KC_PLUS,  KC_3,         KC_6,         KC_9,         KC_ASTR,      _______, \
  KC_BSLASH, LSFT_T(KC_LBRC), LCTL_T(KC_RBRC), KC_LPRN,  KC_RPRN,  KC_AMPR,          KC_MINUS, RALT_T(KC_2), RCMD_T(KC_5), RCTL_T(KC_8), RSFT_T(KC_0), KC_EQL,  \
  _______,   KC_PERC,         KC_HASH,         KC_AT,    KC_DLR,   KC_PIPE,          KC_DOT,   KC_1,         KC_4,         KC_7,         KC_SLASH,     _______, \
  _______,   _______,         XXXXXXX,         KC_GRAVE, KC_EQL,   KC_EQL,           KC_UNDS,  KC_UNDS,      KC_TILDE,     XXXXXXX,      _______,      _______, \
  _______,   _______,         _______,         _______,  KC_GRAVE, KC_GRAVE,         KC_TILDE, KC_TILDE,     _______,      _______,      _______,      _______  \
),


/* RIGHT NAVIGATION
   ,____________________________________________________________________________________,
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |      |      |      |      |      ||      | PgUp |UArrow| Home |      |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |      |      |      |      |      ||      |LArrow|DArrow|RArrow|      |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |      |      |      |      |      ||      | PgDn |DArrow|  End |      |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |______|______+------+------+______|______||______|______+------+------+______|______|
  		          |      |      |                            |      |      |
		            |      |      |                            |      |      |
                |______|______|                            |______|______|
*/
[_RIGHTNAV] = KEYMAP( \
  _______, _______, _______, _______, _______, _______,             _______, KC_PGUP,   KC_UP,   KC_HOME, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, KC_LEFT,   KC_DOWN, KC_RGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, KC_PGDOWN, KC_DOWN, KC_END,  _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______,   _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______,   _______, _______, _______, _______  \
),


/* LEFT NAVIGATION
   ,____________________________________________________________________________________,
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |      | PgUp |UArrow| Home |      ||      |      |      |      |      |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |      |LArrow|DArrow|RArrow|      ||      |      |      |      |      |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |      | PgDn |DArrow|  End |      ||      |      |      |      |      |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |______|______+------+------+______|______||______|______+------+------+______|______|
  		          |      |      |                            |      |      |
		            |      |      |                            |      |      |
                |______|______|                            |______|______|
*/
[_LEFTNAV] = KEYMAP( \
  _______, _______, KC_PGUP,   KC_UP,   KC_HOME, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_LEFT,   KC_DOWN, KC_RGHT, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_PGDOWN, KC_DOWN, KC_END,  _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,   _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,   _______, _______, _______,             _______, _______, _______, _______, _______, _______  \
),


/* LEFT NAVIGATION
   ,____________________________________________________________________________________,
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |  F1  |  F2  |  F3  |  F4  |      ||      |  F1  |  F2  |  F3  |  F4  |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |  F5  |  F6  |  F7  |  F8  |      ||      |  F5  |  F6  |  F7  |  F8  |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |      |  F9  |  F10 |  F11 |  F12 |      ||      |  F9  |  F10 |  F11 |  F12 |      |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |______|______+------+------+______|______||______|______+------+------+______|______|
  		          |      |      |                            |      |      |
		            |      |      |                            |      |      |
                |______|______|                            |______|______|
*/
[_FUNCTIONS] = KEYMAP( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, \
  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,             _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, \
  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,             _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______  \
),


/* STENOGROPHY TOGGLE
                        ,_____________,            ,_____________,
                        |      |      |            |      |      |
          		          | CAPS | INSRT|            | INSRT| CAPS |
      		              |      |      |            |      |      |
                        |______|______|___,    ,___|______|______|
                            |      |      |    |      |      |
          	                |PLOVER|PLOVER|    | RESET| RESET|
                            |      |      |    |      |      |
		                        +------+------+    +------+------+
                            |      |      |    |      |      |
 	                          |STENO1|STENO2|    | RESET| RESET|
                            |______|______|    |______|______|
*/
[_STENO] = KEYMAP( \
  _______,      _______,       _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______,      _______,       _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______,      _______,       _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______,      _______,       _______, _______, KC_LCAP, KC_INS,              KC_INS,  KC_LCAP, _______, _______, _______, _______, \
  STENO_TXBOLT, STENO_TXBOLT2, _______, _______, PLOVER,  PLOVER,              RESET,   RESET,   _______, _______, RESET,   RESET    \
),


/* Plover layer (http://opensteno.org)
This layer remains on until EXIT key is pressed or the keyboard is reconnected.
No other layers/modifiers to be used with it - it is self-sufficient.
All other STENO/PLOVER layers defind below implement the same map with minor variances:
	- TX Bolt protocol over COM port is used instead of acting as a regular keyboard.
        - NumBar keys are moved below the alpha-keys.
  ,____________________________________________________________________________________,
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |   #  |   #  |   #  |   #  |   #  |   #  ||   #  |   #  |   #  |   #  |   #  |   #  |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  | xxxx |   S  |   T  |   P  |   H  |   *  ||   *  |   F  |   P  |   L  |   T  |   D  |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |------+------+------+------+------+------||------+------+------+------+------+------|
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  | xxxx |   S  |   K  |   W  |   R  |   *  ||   *  |   R  |   B  |   G  |   S  |   Z  |
  |      |      |      |      |      |      ||      |      |      |      |      |      |
  |______+------+------+______|______|______||______|______+------+------+______|______|
  		   |      |      |                                   |      |      |
		     | xxxx | xxxx |                                   | xxxx | xxxx |
         |______|______|                                   |______|______|
                    ,_____________,             ,_____________,
                    |      |      |             |      |      |
          		      |   A  |   O  |             |   E  |   U  |
                    |______|______|___,     ,___|______|______|
                        |      |      |     |      |      |
          	            | xxxx | xxxx |     | xxxx | xxxx |
                        |      |      |     |      |      |
		                    +------+------+     +------+------+
                        |      |      |     |      |      |
 	                      | xxxx | EXIT |     | EXIT | xxxx |
                        |______|______|     |______|______|
*/

[_PLOVER] = KEYMAP( \
  KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   , \
  XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, \
  XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_C,    KC_V,    KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, EXT_PLV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_PLV, XXXXXXX \
),

/* Plover Layer via TX Bolt interface.
   The layout is the same as for Plover above, just different key codes
*/

[_STENO_TXBOLT] = KEYMAP( \
   STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM,    STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, \
   STN_SL,  STN_SL,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,    STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR, \
   STN_SL,  STN_SL,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,    STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,      STN_E,   STN_U,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   XXXXXXX, EXT_PLV2,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_PLV2, XXXXXXX \
 ),

/*  TX Bolt with the alpha rows moved up, numbar below them.
*/
[_STENO_TXBOLT2] = KEYMAP( \
   STN_SL,  STN_SL,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,    STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR, \
   STN_SL,  STN_SL,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,    STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR, \
   STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM,    STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, \
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,      STN_E,   STN_U,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   XXXXXXX, EXT_PLV2,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_PLV2, XXXXXXX \
 ),


/* Dummy layers, both transparent, used to implement the extra right layer switch: E+R both held down.
*/
[_DUMMY1] = KEYMAP( \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______  \
),
[_DUMMY2] = KEYMAP( \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______  \
)

};


void matrix_init_user() {
  steno_set_mode(STENO_MODE_BOLT); // or STENO_MODE_BOLT
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    // Config for Multi-press layer switching
  //  case E_RT:
  //     if (record->event.pressed) {
  //       layer_on(_DUMMY1);
  //       update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
  //     } else {
  //       layer_off(_DUMMY1);
  //       update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
  //      }
  //     return true;// false;
  //     break;
  //  case R_RT:
  //     if (record->event.pressed) {
  //       layer_on(_DUMMY2);
  //       update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
  //     } else {
  //       layer_off(_DUMMY2);
  //       update_tri_layer(_DUMMY1, _DUMMY2, _EXTRARIGHT);
  //      }
  //     return true;// false;
  //     break;

    // Config for Stenogrophy
    case PLOVER:
      if (record->event.pressed) {
        layer_on(_PLOVER);
       if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
     case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
        layer_on(_QWERTY);
      }
      return false;
      break;
    case STENO_TXBOLT:
      if (record->event.pressed) {
        layer_on(_STENO_TXBOLT);
       if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case STENO_TXBOLT2:
      if (record->event.pressed) {
        layer_on(_STENO_TXBOLT2);
       if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
     case EXT_PLV2:
      if (record->event.pressed) {
        layer_off(_STENO_TXBOLT);
        layer_off(_STENO_TXBOLT2);
        layer_on(_QWERTY);
      }
      return false;
      break;
 }
  return true;
}

