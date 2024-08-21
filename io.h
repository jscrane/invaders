#ifndef __IO_H__
#define __IO_H__

class IO: public PortDevice<i8080>, public matrix_keyboard {
public:
	IO() { _p1 = _p2 = 0; }
	void begin();

	uint8_t in(uint16_t p, i8080 *cpu);
	void out(uint16_t p, uint8_t b, i8080 *cpu);

	void down(uint8_t key);
	void up(uint8_t key);

	bool is_paused() { return _paused; }
private:
	uint8_t _soff, _s0, _s1, _p1, _p2;
	bool _paused;
};

#endif
