// Copyright 2022 Yizhen Liu (@edwardslau)
// SPDX-License-Identifier: GPL-2.0
#include QMK_KEYBOARD_H

// Fn shortcuts that need different keys on macOS (Ctrl/GUI swapped with CG_TOGG)
enum custom_keycodes {
    WD_BSPC = SAFE_RANGE, // delete word left
    WD_DEL,               // delete word right
    WD_LEFT,              // jump word left
    WD_RGHT,              // jump word right
    SEL_BOL,              // select to start of line
    SEL_EOL,              // select to end of line
    LN_HOME,              // start of line
    LN_END,               // end of line
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_DEL,  //15
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, //15
        KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGUP, //14
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN, //14
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  //10
    ),
    [1] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_GRV,  _______,
        _______,          WD_BSPC, WD_DEL,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          WD_LEFT, WD_RGHT, _______, KC_PGUP, LN_HOME, LN_END,  KC_PGDN, _______, _______, _______, _______, _______,          _______,
        _______,          SEL_BOL, SEL_EOL, _______, _______, _______, NK_TOGG, CG_TOGG, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    )
};

static uint16_t shortcut_for(uint16_t keycode) {
    bool mac = keymap_config.swap_lctl_lgui;
    switch (keycode) {
        case WD_BSPC: return mac ? LALT(KC_BSPC) : LCTL(KC_BSPC);
        case WD_DEL:  return mac ? LALT(KC_DEL)  : LCTL(KC_DEL);
        case WD_LEFT: return mac ? LALT(KC_LEFT) : LCTL(KC_LEFT);
        case WD_RGHT: return mac ? LALT(KC_RGHT) : LCTL(KC_RGHT);
        case SEL_BOL: return mac ? LSG(KC_LEFT)  : LSFT(KC_HOME);
        case SEL_EOL: return mac ? LSG(KC_RGHT)  : LSFT(KC_END);
        case LN_HOME: return mac ? LGUI(KC_LEFT) : KC_HOME;
        case LN_END:  return mac ? LGUI(KC_RGHT) : KC_END;
    }
    return KC_NO;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // register_code16 sends the mods as given, without the Ctrl/GUI swap
    static uint16_t held[LN_END - WD_BSPC + 1];
    if (keycode < WD_BSPC || keycode > LN_END) {
        return true;
    }
    uint16_t *slot = &held[keycode - WD_BSPC];
    if (record->event.pressed) {
        *slot = shortcut_for(keycode);
        register_code16(*slot);
    } else {
        unregister_code16(*slot);
    }
    return false;
}
