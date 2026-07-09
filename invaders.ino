/**
 * http://www.emutalk.net/threads/38177-Space-Invaders
 */
#include <stdarg.h>
#include <r65emu.h>
#include <i8080.h>
#include <serial_checkpoint.h>

#include "io.h"
#include "screen.h"
#include "config.h"

#include "rome.h"
#include "romf.h"
#include "romg.h"
#include "romh.h"

prom e(rome, sizeof(rome));
prom f(romf, sizeof(romf));
prom g(romg, sizeof(romg));
prom h(romh, sizeof(romh));

IO io;
ps2_raw_kbd kbd(io);
Memory memory;
i8080 cpu(memory);
Arduino machine(cpu);
ram<> page;
Screen screen;

const uint32_t vblank = 1000000 / 60 / 2;

void setup(void) {

#if DEBUGGING == DEBUG_NONE
	Serial.begin(TERMINAL_SPEED);
#endif

	cpu.set_port_out_handler([](uint16_t port, uint8_t b) { io.out(port, b); });
	cpu.set_port_in_handler([](uint16_t port) { return io.in(port); });

	machine.begin();

	memory.put(h, 0x0000);
	memory.put(g, 0x0800);
	memory.put(f, 0x1000);
	memory.put(e, 0x1800);
	
	// 1k of RAM at 0x2000
	memory.put(page, 0x2000);

	// 7k screen RAM at 0x2400
	memory.put(screen, SCREEN_BASE);

	kbd.register_fnkey_handler([](uint8_t fn) {
		switch(fn) {
		case 1:
			machine.reset();
			break;
		case 6:
			serial_checkpoint(Serial);
			break;
		case 7:
			serial_restore(Serial);
			io.pause();
			break;
		}
	});
	machine.register_pollable(kbd);

	machine.interval_timer(vblank, [interrupt = 1] () mutable {
		cpu.raise(interrupt);
		interrupt = interrupt == 1? 2: 1;
	});

	machine.register_reset_handler([](bool) {
		kbd.reset();
		screen.begin();
		io.begin();
	});
	machine.reset();
}

void loop(void) {

	machine.run(io.is_paused()? CLK_STOPPED: CLK_2MHZ);
}
