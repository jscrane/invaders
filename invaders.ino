/**
 * http://www.emutalk.net/threads/38177-Space-Invaders
 */
#include <stdarg.h>
#include <r65emu.h>
#include <ports.h>
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

ps2_kbd kbd;
IO io;
i8080 cpu(memory, io);
ram<> page;
Screen screen;
vblank vb(cpu);

static void reset(void) {
	hardware_reset();
	kbd.reset();
	screen.begin();
	io.begin();
}

void function_key(uint8_t fn) {
	if (fn == 1)
		reset();
}

void setup(void) {

	hardware_init(cpu);

	memory.put(h, 0x0000);
	memory.put(g, 0x0800);
	memory.put(f, 0x1000);
	memory.put(e, 0x1800);
	
	// 1k of RAM at 0x2000
	memory.put(page, 0x2000);

	// 7k screen RAM at 0x2400
	memory.put(screen, 0x2400);

	kbd.register_fnkey_handler(function_key);

	reset();
}

void loop(void) {

	kbd.poll(io);

	if (!io.is_paused() && hardware_run())
		vb.tick(millis());
}
