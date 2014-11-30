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

	void operator=(byte);
	operator byte() { return _buf[_acc]; }

private:
	byte _buf[DISPLAY_RAM];
	unsigned _xoff, _yoff;
};

#endif
