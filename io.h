#ifndef __IO_H__
#define __IO_H__

class IO: public PortDevice<z80> {
public:
	IO();

	byte in(word p, z80 *cpu);
	void out(word p, byte b, z80 *cpu);

	void down(byte key);
	void up(byte key);

private:
	byte _soff, _s0, _s1, _p1, _p2;
};

#endif
