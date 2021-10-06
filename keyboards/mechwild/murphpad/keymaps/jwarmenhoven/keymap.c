/* Copyright 2021 Kyle McCreery
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
 *
 * >>> Jordi Warmenhoven
 * Minor change from default:
 * - Layer FN1: Swapped mode cycling keycodes (RGB_RMOD, RGB_MOD) and
 *              RGB saturation keycodes (RGB_SAD, RGB_SAI)
 *              
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap

enum layer_names {
  _BASE,
  _FN1,
	_FN2,
	_FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                 LCTL(KC_PGUP),  LCTL(KC_PGDN), KC_F11, KC_F,
				          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_MUTE,  KC_P4,   KC_P5,   KC_P6,   _______,
        TT(_FN1), KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_BSPC,  KC_P0,   _______, KC_PDOT, _______,

                  KC_F5,   KC_F6,   KC_F7

    ),
    [_FN1] = LAYOUT(
                 LCTL(KC_PGUP),  LCTL(KC_PGDN), KC_F11, KC_F,
                 LCTL(KC_R), _______, _______, LCTL(LALT(KC_R)),
                 RGB_HUD,  RGB_SPI, RGB_HUI, _______,
        _______, RGB_SAD,  RGB_TOG, RGB_SAI, _______,
        _______, RGB_VAD,  RGB_SPD, RGB_VAI, _______,
        _______, RGB_RMOD, _______, RGB_MOD, _______,

                 _______, _______, _______

    ),
	  [_FN2] = LAYOUT(
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,

                  _______, _______, _______

    ),
	  [_FN3] = LAYOUT(
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
                  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,

                  _______, _______, _______

    )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
		case 1:
            if (clockwise) {
                tap_code(KC_MS_WH_UP);
            } else {
                tap_code(KC_MS_WH_DOWN);
            }
        break;
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;       // flips the display 270 degrees
	}

	static void render_logo(void) {     // Render MechWild "MW" Logo
		static const char PROGMEM logo_1[] = {0x8A, 0x8B, 0x8C, 0x8D, 0x00};
		static const char PROGMEM logo_2[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x00};
		static const char PROGMEM logo_3[] = {0xCA, 0xCB, 0xCC, 0xCD, 0x00};
		static const char PROGMEM logo_4[] = {0x20, 0x8E, 0x8F, 0x90, 0x00};
		oled_set_cursor(0,0);
		oled_write_P(logo_1, false);
		oled_set_cursor(0,1);
		oled_write_P(logo_2, false);
		oled_set_cursor(0,2);
		oled_write_P(logo_3, false);
		oled_set_cursor(0,3);
		oled_write_P(logo_4, false);
	}

	void oled_task_user(void) {
		render_logo();
		oled_set_cursor(0,6);

		oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _FN1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case _FN2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case _FN3:
            oled_write_ln_P(PSTR("FN 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
	oled_write_ln_P(PSTR(""), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	}
#endif


