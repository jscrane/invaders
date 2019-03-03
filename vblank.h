#ifndef __VBLANK_H__
#define __VBLANK_H__

class vblank {
public:
	vblank(CPU &cpu): _cpu(cpu), _last_int(0), _interrupt(1) {}

	void tick(uint32_t now) {
		uint32_t dt = now - _last_int;
		if (dt >= interval) {
			_cpu.raise(_interrupt);
			_interrupt = _interrupt == 1? 2: 1;
			_last_int = now;
		}
	}

	static const int interval = 1000 / 60 / 2;
private:
	CPU &_cpu;
	uint32_t _last_int;
	uint8_t _interrupt;
};

#endif
