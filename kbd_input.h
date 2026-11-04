#pragma once

#include <cstdint>
#include <ps2_raw_kbd.h>

#include "input_ports.h"

#define P1_START	PS2_KEY_1
#define P2_START	PS2_KEY_2
#define COIN		PS2_KEY_3

#define P1_LEFT		PS2_LCTRL
#define P1_RIGHT	PS2_LALT
#define P1_SHOOT	PS2_RSHIFT

#define P2_LEFT		PS2_RGUI
#define P2_RIGHT	PS2_APPS
#define P2_SHOOT	PS2_LSHIFT

#define PAUSE		PS2_SPACE

class kbd_input: public matrix_keyboard, public input_ports {
public:
	kbd_input() { reset(); }

	void down(uint16_t key) override;
	void up(uint16_t key) override;
	void reset() override { input_ports::reset(); }
};
