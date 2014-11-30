#ifndef __KBD_H__
#define __KBD_H__

class IO: public PortDevice {
public:
	IO();

	byte in(byte p, i8080 *cpu);
	void out(byte p, byte b, i8080 *cpu);

	void down(unsigned key);
	void up(unsigned key);

private:
	byte _soff, _s0, _s1, _p1, _p2;
};

#endif
