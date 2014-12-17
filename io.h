#ifndef __IO_H__
#define __IO_H__

class IO: public i8080::Ports {
public:
	IO();

	byte in(byte p, i8080 *cpu);
	void out(byte p, byte b, i8080 *cpu);

	void down(byte key);
	void up(byte key);

private:
	byte _soff, _s0, _s1, _p1, _p2;
};

#endif
