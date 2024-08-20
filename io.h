#ifndef __IO_H__
#define __IO_H__

class ps2_kbd;

class IO: public PortDevice<i8080> {
public:
	IO(ps2_kbd &kbd): _kbd(kbd) { _p1 = _p2 = 0; }
	void begin();

	uint8_t in(uint16_t p, i8080 *cpu);
	void out(uint16_t p, uint8_t b, i8080 *cpu);

private:
	void poll_kbd();
	void down(uint8_t key);
	void up(uint8_t key);

	ps2_kbd &_kbd;
	uint8_t _soff, _s0, _s1, _p1, _p2;
};

#endif
