/**
 * http://www.emutalk.net/threads/38177-Space-Invaders
 */
#include <stdarg.h>
#include <r65emu.h>
#include <i8080.h>

#include "io.h"
#include "screen.h"
#include "vblank.h"
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
vblank vb(cpu);

void setup(void) {

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
	memory.put(screen, 0x2400);

	kbd.register_fnkey_handler([](uint8_t fn) {
		if (fn == 1)
			machine.reset();
	});
	machine.register_pollable(kbd);

	machine.register_reset_handler([](bool) {
		kbd.reset();
		screen.begin();
		io.begin();
	});
	machine.reset();
}

void loop(void) {

	machine.run();

	if (!io.is_paused() && !cpu.halted())
		vb.tick(millis());
}
