#include <Arduino.h>
#include <memory.h>
#include <hardware.h>
#include <tftdisplay.h>

#include "config.h"
#include "display.h"

void Display::begin() {
	TFTDisplay::begin(BLACK, WHITE, ORIENTATION);
	clear();
	_xoff = (_dx - DISPLAY_X) / 2;
	_yoff = (_dy - DISPLAY_Y) / 2;
}

void Display::draw(Memory::address a, uint8_t b) {
	unsigned y = DISPLAY_Y - (a % BYTES_PER_LINE) * 8;
	unsigned x = (a / BYTES_PER_LINE);

	uint8_t d = _buf[a] ^ b;
	for (unsigned i = 0, bit = 0x01; i < 8; i++, bit *= 2)
		if (d & bit) {
			unsigned fg = WHITE, yi = y - i;
			if (yi > 32 && yi <= 64)
				fg = RED;
			else if (yi > 184 && yi <= 240)
				fg = GREEN;
			else if (yi > 240 && x >=16 && x < 134)
				fg = GREEN;
			drawPixel(x + _xoff, yi + _yoff, (b & bit)? fg: BLACK);
		}

	_buf[a] = b;
}
