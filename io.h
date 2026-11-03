#pragma once

class input_ports;

class IO {
public:
	IO(input_ports &in): _input(in) {}
	void begin();

	uint8_t in(uint16_t p);
	void out(uint16_t p, uint8_t b);

private:
	uint8_t _soff, _s0, _s1;
	input_ports &_input;
};
