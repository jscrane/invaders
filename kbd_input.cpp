#include "kbd_input.h"

void kbd_input::down(uint16_t scan) {
	switch (scan) {
	case P1_START:
		_p1_start = true;
		break;
	case P1_LEFT:
		_p1_left = true;
		break;
	case P1_RIGHT:
		_p1_right = true;
		break;
	case P1_SHOOT:
		_p1_shoot = true;
		break;
	case P2_START:
		_p2_start = true;
		break;
	case P2_LEFT:
		_p2_left = true;
		break;
	case P2_RIGHT:
		_p2_right = true;
		break;
	case P2_SHOOT:
		_p2_shoot = true;
		break;
	case COIN:
		_coin = true;
		break;
	default:
		clear_ports();
		break;
	}
}

void kbd_input::up(uint16_t scan) {
	switch (scan) {
	case P1_START:
		_p1_start = false;
		break;
	case P1_LEFT:
		_p1_left = false;
		break;
	case P1_RIGHT:
		_p1_right = false;
		break;
	case P1_SHOOT:
		_p1_shoot = false;
		break;
	case P2_START:
		_p2_start = false;
		break;
	case P2_LEFT:
		_p2_left = false;
		break;
	case P2_RIGHT:
		_p2_right = false;
		break;
	case P2_SHOOT:
		_p2_shoot = false;
		break;
	case COIN:
		_coin = false;
		break;
	case PAUSE:
		_paused = !_paused;
		break;
	default:
		clear_ports();
		break;
	}
}
