#pragma once

#define BYTES_PER_LINE	32
#define DISPLAY_X	224
#define DISPLAY_Y	(BYTES_PER_LINE * 8)
#define	SCREEN_RAM	DISPLAY_X * BYTES_PER_LINE
#define SCREEN_BASE	0x2400

class Screen: public Memory::Device, public Display {
public:
	Screen(): Memory::Device(SCREEN_RAM), Display() {}
	void begin();

	void operator=(uint8_t b) override { if (_buf[_acc] != b) draw(_acc, b); }
	operator uint8_t() override { return _buf[_acc]; }

	void checkpoint(Checkpoint &c) override;
	void restore(Checkpoint &) override;

private:
	void draw(Memory::address a, uint8_t b);

	uint8_t _buf[SCREEN_RAM];
};
