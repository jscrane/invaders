#include <Energia.h>

#include "ports.h"
#include "io.h"

#define P1_START	0x16	// 1
#define P1_LEFT		0x12	// l-shift
#define P1_RIGHT	0x14	// l-ctrl
#define P1_SHOOT	0x11	// l-alt

#define P2_START	0x1e	// 2
#define P2_LEFT		0x27	// r-gui
#define P2_RIGHT	0x2f	// apps
#define P2_SHOOT	0x59	// r-shift

#define COIN		0x26	// 3

IO::IO() {
	_p1 = _p2 = 0;
}

byte IO::in(byte port, i8080 *cpu) {
	word w;
	switch (port) {
	case 0:
		return 0x0f;
	case 1:
		return _p1;
	case 2:
		return _p2;
	case 3:
		w = (_s1 << 8) + _s0;
		return (w >> (8 - _soff)) & 0xff;
	}
	return 0x00;
}

void IO::out(byte port, byte b, i8080 *cpu) {
	switch (port) {
	case 1:
		_p1 = b;
		break;
	case 2:
		_soff = b & 0x07;
		break;
	case 4:
		_s0 = _s1;
		_s1 = b;
		break;
	}
}

void IO::down(unsigned key) {
Serial.print("down ");
Serial.println(key, 16);
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
	}
}

void IO::up(unsigned key) {
Serial.print("up ");
Serial.println(key, 16);
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
	}
}
