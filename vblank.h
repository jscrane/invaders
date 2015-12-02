#ifndef __VBLANK_H__
#define __VBLANK_H__

class vblank: public Checkpointable {
public:
	vblank(CPU &cpu): _cpu(cpu), _last_int(0), _interrupt(1) {}

	void tick(unsigned long now) {
		unsigned long dt = now - _last_int;
		if (dt >= interval) {
			_cpu.raise(_interrupt);
			_interrupt = _interrupt == 1? 2: 1;
			_last_int = now;
		}
	}

	void checkpoint(Stream &s) {
		// FIXME
	}

	void restore(Stream &s) {
		// FIXME
	}

	static const int interval = 1000 / 60 / 2;
private:
	CPU &_cpu;
	unsigned long _last_int;
	unsigned _interrupt;
};

#endif
