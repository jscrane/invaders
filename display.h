#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define BYTES_PER_LINE	32
#define DISPLAY_X	224
#define DISPLAY_Y	(BYTES_PER_LINE * 8)
#define	DISPLAY_RAM	DISPLAY_X * BYTES_PER_LINE

class Display: public Memory::Device, public UTFTDisplay {
public:
	Display(): Memory::Device(sizeof(_buf)) {}
	void begin();

	void checkpoint(Stream &s);
	void restore(Stream &s);

	void operator=(byte b) { if (_buf[_acc] != b) draw(_acc, b); }
	operator byte() { return _buf[_acc]; }

private:
	void draw(Memory::address a, byte b);

	byte _buf[DISPLAY_RAM];
	unsigned _xoff, _yoff;
};

#endif
