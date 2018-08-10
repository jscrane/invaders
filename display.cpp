#include <Arduino.h>
#include <UTFT.h>

#include <memory.h>
#include <utftdisplay.h>
#include <hardware.h>

#include "display.h"

void Display::begin() {
	UTFTDisplay::begin(VGA_BLACK, VGA_WHITE, portrait);
	clear();
	_xoff = (_dx - DISPLAY_X) / 2;
	_yoff = (_dy - DISPLAY_Y) / 2;
}

void Display::draw(Memory::address a, byte b) {
	unsigned y = DISPLAY_Y - (a % BYTES_PER_LINE) * 8;
	unsigned x = (a / BYTES_PER_LINE);

	byte d = _buf[a] ^ b;
	for (unsigned i = 0, bit = 0x01; i < 8; i++, bit *= 2)
		if (d & bit) {
			unsigned fg = VGA_WHITE, yi = y - i;
			if (yi > 32 && yi <= 64)
				fg = VGA_RED;
			else if (yi > 184 && yi <= 240)
				fg = VGA_LIME;
			else if (yi > 240 && x >=16 && x < 134)
				fg = VGA_LIME;
			utft.setColor((b & bit)? fg: VGA_BLACK);
			utft.drawPixel(x + _xoff, yi + _yoff);
		}

	_buf[a] = b;
}

void Display::checkpoint(Stream &s) {
	s.write(_buf, sizeof(_buf));
}

void Display::restore(Stream &s) {
	byte b[256];
	for (Memory::address a = 0; a < sizeof(_buf); a += sizeof(b)) {
		s.readBytes((char *)b, sizeof(b));
		for (unsigned i = 0; i < sizeof(b); i++)
			draw(a+i, b[i]);
	}
}
