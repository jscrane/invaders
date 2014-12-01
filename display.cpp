#include <Energia.h>
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

void Display::operator=(byte b) {
	byte d = _buf[_acc];
	if (d == b)
		return;
	
	unsigned y = DISPLAY_Y - (_acc % BYTES_PER_LINE) * 8;
	unsigned x = (_acc / BYTES_PER_LINE);

	for (unsigned i = 0, bit = 0x01; i < 8; i++, bit *= 2)
		if ((d & bit) != (b & bit)) {
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

	_buf[_acc] = b;
}

void Display::checkpoint(Stream &s) {
	s.write(_buf, sizeof(_buf));
}

void Display::restore(Stream &s) {
	s.readBytes((char *)_buf, sizeof(_buf));
}
