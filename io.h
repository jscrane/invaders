#ifndef __IO_H__
#define __IO_H__

class IO: public PortDevice<i8080> {
public:
	IO();

	byte in(word p, i8080 *cpu);
	void out(word p, byte b, i8080 *cpu);

	void down(byte key);
	void up(byte key);

private:
	byte _soff, _s0, _s1, _p1, _p2;
};

#endif
