#include <Arduino.h>

#include <machine.h>
#include <memory.h>
#include <display.h>
#include <hardware.h>

#include "config.h"
#include "screen.h"

void Screen::begin() {
	Display::begin(BLACK, WHITE, ORIENTATION, DISPLAY_X, DISPLAY_Y);
	clear();
}

void Screen::draw(Memory::address a, uint8_t b) {

	int16_t y = DISPLAY_Y - (a % BYTES_PER_LINE) * 8;
	int16_t x = (a / BYTES_PER_LINE);

	uint8_t d = _buf[a] ^ b;
	for (unsigned i = 0, bit = 0x01; i < 8; i++, bit *= 2)
		if (d & bit) {
			uint16_t fg = WHITE, yi = y - i;
			if (yi > 32 && yi <= 64)
				fg = RED;
			else if (yi > 184 && yi <= 240)
				fg = GREEN;
			else if (yi > 240 && x >=16 && x < 134)
				fg = GREEN;
			drawPixel(x, yi, (b & bit)? fg: BLACK);
		}
	_buf[a] = b;
}
