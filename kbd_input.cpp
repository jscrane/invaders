#include <cstdint>
#include <ps2_keyboard.h>

#include "kbd_input.h"

void kbd_input::down(uint16_t key) {
	switch (key) {
	case P1_START:
		_p1 |= 0x04;
		break;
	case P1_LEFT:
		_p1 |= 0x20;
		break;
	case P1_RIGHT:
		_p1 |= 0x40;
		break;
	case P1_SHOOT:
		_p1 |= 0x10;
		break;
	case P2_START:
		_p1 |= 0x02;
		break;
	case P2_LEFT:
		_p2 |= 0x20;
		break;
	case P2_RIGHT:
		_p2 |= 0x40;
		break;
	case P2_SHOOT:
		_p2 |= 0x10;
		break;
	case COIN:
		_p1 |= 0x01;
		break;
	default:
		_p1 = _p2 = 0;
		break;
	}
}

void kbd_input::up(uint16_t key) {
	switch (key) {
	case P1_START:
		_p1 &= ~0x04;
		break;
	case P1_LEFT:
		_p1 &= ~0x20;
		break;
	case P1_RIGHT:
		_p1 &= ~0x40;
		break;
	case P1_SHOOT:
		_p1 &= ~0x10;
		break;
	case P2_START:
		_p1 &= ~0x02;
		break;
	case P2_LEFT:
		_p2 &= ~0x20;
		break;
	case P2_RIGHT:
		_p2 &= ~0x40;
		break;
	case P2_SHOOT:
		_p2 &= ~0x10;
		break;
	case COIN:
		_p1 &= ~0x01;
		break;
	case PAUSE:
		_paused = !_paused;
		break;
	default:
		_p1 = _p2 = 0;
		break;
	}
}
