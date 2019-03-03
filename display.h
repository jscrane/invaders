#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define BYTES_PER_LINE	32
#define DISPLAY_X	224
#define DISPLAY_Y	(BYTES_PER_LINE * 8)
#define	DISPLAY_RAM	DISPLAY_X * BYTES_PER_LINE

class Display: public Memory::Device, public TFTDisplay {
public:
	Display(): Memory::Device(DISPLAY_RAM) {}
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
	uint8_t _buf[DISPLAY_RAM];
#endif
	uint8_t _xoff, _yoff;
};

#endif
