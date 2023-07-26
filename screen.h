#ifndef __SCREEN_H__
#define __SCREEN_H__

#define BYTES_PER_LINE	32
#define DISPLAY_X	224
#define DISPLAY_Y	(BYTES_PER_LINE * 8)
#define	SCREEN_RAM	DISPLAY_X * BYTES_PER_LINE

class Screen: public Memory::Device, public Display {
public:
	Screen(): Memory::Device(SCREEN_RAM) {}
	void begin();

#if defined(NO_DISPLAY_BUFFER)
	void operator=(uint8_t b) { draw(_acc, b); }
	operator uint8_t() { return 0;  }
#else
	void operator=(uint8_t b) { if (_buf[_acc] != b) draw(_acc, b); }
	operator uint8_t() { return _buf[_acc]; }
#endif

private:
	void draw(Memory::address a, uint8_t b);

#if !defined(NO_DISPLAY_BUFFER)
	uint8_t _buf[SCREEN_RAM];
#endif
	uint8_t _xoff, _yoff;
};

#endif
