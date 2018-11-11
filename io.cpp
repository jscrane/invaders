#include <Arduino.h>
#include <r65emu.h>
#include <ports.h>
#include <i8080.h>
#include <hardware.h>
#include <sound_dac.h>

#include "io.h"
#include "config.h"

#if defined(DAC_SOUND)
#include "sounds.h"
#endif

uint8_t IO::in(uint16_t port, i8080 *cpu) {
	uint16_t w;
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

#if defined(DEBUGGING)
static const char debug[] PROGMEM = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', '0', '1', '2', '3', '4', '5',
	'6', '7', '8', '9', '<', '>', ' ', '=',
	'*', '^', '_', '_', '_', '_', '_', '_',
	'Y', '%', '_', '_', '_', '_', 'Y', '&',
	'?', '_', '_', '_', '_', '_', '_', '-',
};
#endif

void IO::out(uint16_t port, uint8_t b, i8080 *cpu) {
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
#if defined(DAC_SOUND)
	case 3:
		if (b & 1)
			_playing = _sound->play(ufo, sizeof(ufo));

		if (_playing != shot && (b & 2))
			_playing = _sound->play(shot, sizeof(shot));

		if (_playing != basehit && (b & 4))
			_playing = _sound->play(basehit, sizeof(basehit));

		if (_playing != invhit && (b & 8))
			_playing = _sound->play(invhit, sizeof(invhit));

		if (_playing != extend && (b & 16))
			_playing = _sound->play(extend, sizeof(extend));
		break;
	case 5:
		if (_playing != walk1 && (b & 1))
			_playing = _sound->play(walk1, sizeof(walk1));

		if (_playing != walk2 && (b & 2))
			_playing = _sound->play(walk2, sizeof(walk2));

		if (_playing != walk3 && (b & 4))
			_playing = _sound->play(walk3, sizeof(walk3));

		if (_playing != walk4 && (b & 8))
			_playing = _sound->play(walk4, sizeof(walk4));

		if (_playing != ufohit && (b & 16))
			_playing = _sound->play(ufohit, sizeof(ufohit));
		break;
#endif
#if defined(DEBUG)
	case 6:
		Serial.print(pgm_read_byte(debug+b));
		break;
#endif
	}
}

void IO::down(uint8_t key) {
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

void IO::up(uint8_t key) {
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
	default:
		_p1 = _p2 = 0;
		break;
	}
}
