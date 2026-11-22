#pragma once

class switches;

class IO {
public:
	IO(switches &s): _switches(s) {}
	void begin();

	uint8_t in(uint16_t p);
	void out(uint16_t p, uint8_t b);

private:
	uint8_t _soff, _s0, _s1;
	switches &_switches;
};
