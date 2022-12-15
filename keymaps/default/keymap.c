/* Copyright 2022 HiryKun (@HiryKun)
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

#include "animation1.h"
// #include "animation2.h"

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_anim :1; //在EEPROM定义变量，记录RGB开关状态
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user(); //从EEPROM读取状态
}

void eeconfig_init_user(void) {  
  user_config.raw = 0;
  user_config.rgb_anim = 1;     //清除EEPROM，默认状态
  eeconfig_update_user(user_config.raw); 
}

enum my_keycodes {
  RGB_BTO = SAFE_RANGE,  //自定义一个键码
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_BTO:
      if (record->event.pressed) {  //如果按下
        user_config.rgb_anim ^= 1; //改变状态
        eeconfig_update_user(user_config.raw);  //更新状态
      } else { //如果松开
      }
      return true;
    default:
      return true;
    }   
}

void rgb_matrix_indicators_kb(void) { //RGB矩阵回调函数
    if(user_config.rgb_anim == 0) rgb_matrix_set_color_all(0, 0, 0); //RGB关闭
    if(host_keyboard_led_state().caps_lock) rgb_matrix_set_color(52, 0xFF, 0, 0);
    if(keymap_config.no_gui) rgb_matrix_set_color(80, 0xFF, 0, 0); //若锁WIN键，设置80号灯
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 默认层 */
  [0] = LAYOUT(
 		KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL , TO(1)  ,
		KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_HOME,
		KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PSCR,
		KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,
		KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  ,
		KC_LCTL, KC_LWIN, KC_LALT,                   KC_SPC ,                            KC_RALT, MO(1)  , KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
  
  /* Fn层 */
  [1] = LAYOUT(
    QK_BOOT, EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(0)  ,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR ,          RGB_SPI,
		XXXXXXX, GUI_TOG, XXXXXXX,                   XXXXXXX,                            XXXXXXX, KC_TRNS, RGB_BTO, RGB_MOD, RGB_SPD, RGB_MOD
    )
};

/*编码器功能*/
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [1] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif

/*RGB矩阵*/
led_config_t g_led_config = { {
	{15, 14, 13, 12,     11,     10, 9 ,     8 ,     7 ,     6 , 5 , 4 , 3 ,     2 ,     1},
	{17, 18, 19, 21,     22,     23, 25,     26,     27,     28, 30, 31, 32,     34,     36},
	{51, 50, 49, 48,     47,     46, 45,     44,     43,     42, 41, 40, 39,     38,     37},
	{52, 53, 54, 55,     56,     57, 58,     59,     60,     61, 62, 63, 64,     NO_LED, NO_LED},
	{77, 76, 75, 74,     73,     72, 71,     70,     69,     68, 67, 66, NO_LED, 65,     NO_LED},
	{79, 80, 82, NO_LED, NO_LED, 84, NO_LED, NO_LED, NO_LED, 86, 87, 88, 90,     91,     92}
}, {
    {224, 6}, {216, 0}, {202, 0}, {184, 0}, {169, 0}, {155, 0}, {140, 0}, {123, 0}, {108, 0}, {94, 0}, {79, 0}, {61, 0}, {47, 0 }, {36, 0 }, {18, 0 }, {0, 0},
	{0, 0}, {0, 13}, {14, 13}, {29, 13}, {36, 0}, {43, 13}, {58, 13}, {72, 13}, {79, 0}, {87, 13}, {101, 13}, {115, 13}, {130, 13}, {137, 0}, {145, 13}, {159, 13}, {173, 13}, {188, 0}, {195, 13}, {224, 0}, {224, 13},
	{224, 26}, {199, 26}, {181, 26}, {166, 26}, {152, 26}, {137, 26}, {123, 26}, {108, 26}, {94, 26}, {79, 26}, {65, 26}, {51, 26}, {36, 26}, {22, 26}, {4, 26},
	{4, 38}, {25, 38}, {40, 38}, {54, 38}, {69, 38}, {83, 38}, {98, 38}, {112, 38}, {126, 38}, {141, 38}, {155, 38}, {170, 38}, {191, 38},
	{206, 51}, {184, 51}, {163, 51}, {148, 51}, {134, 51}, {119, 51}, {105, 51}, {90, 51}, {76, 51}, {61, 51}, {47, 51}, {33, 51}, {11, 51},
	{0, 64}, {0, 64}, {20, 64}, {29, 64}, {40, 64}, {79, 64}, {90, 64}, {134, 64}, {145, 64}, {156, 64}, {173, 64}, {185, 64}, {191, 64}, {206, 64}, {220, 64}, {224, 64}
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	2, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 2, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
	2, 4, 4, 2, 4, 2, 4, 2, 4, 4, 4, 2, 4, 4, 4, 2
} };

/*OLED*/

/*If include "animation2.h", delete these*/
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_90; //将屏幕旋转90度
}
/*If include "animation2.h", delete these*/

bool oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case 0: //如果在默认层
			render_anime1(); //显示图形一
			break;
        case 1: //如果在Fn层
			render_anime2(); //显示图形二
			break;
        case 2: //如果在Fn层
			render_anime3(); //显示图形二
			break;
    }
   return false;
}