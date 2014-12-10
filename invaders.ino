/**
 * http://www.emutalk.net/threads/38177-Space-Invaders
 * http://www.darkpact.com/proj/siemu/is/report2.html
 */
#include <stdarg.h>
#include <UTFT.h>
#include <SPI.h>
#include <SpiRAM.h>
#include <SD.h>
#include <r65emu.h>
#include <i8080.h>

#include "io.h"
#include "display.h"
#include "config.h"

#include "roms/rome.h"
#include "roms/romf.h"
#include "roms/romg.h"
#include "roms/romh.h"

prom e(rome, sizeof(rome));
prom f(romf, sizeof(romf));
prom g(romg, sizeof(romg));
prom h(romh, sizeof(romh));

void status(const char *fmt, ...) {
	char tmp[256];  
	va_list args;
	va_start(args, fmt);
	vsnprintf(tmp, sizeof(tmp), fmt, args);
	Serial.println(tmp);
	va_end(args);
}

IO io;
jmp_buf ex;
i8080 cpu(memory, ex, status, io);
bool halted = false;
ram page;
Display display;

static unsigned long next_int;
static unsigned interrupt;
static bool paused = false;

void reset(void) {
	bool sd = hardware_reset();
	display.begin();
	paused = false;
	halted = (setjmp(ex) != 0);
}

void setup(void) {
	hardware_init(cpu);

	memory.put(h, 0x0000);
	memory.put(g, 0x0800);
	memory.put(f, 0x1000);
	memory.put(e, 0x1800);
	
	// 1k of RAM at 0x2000
	memory.put(page, 0x2000);

	// 7k display RAM at 0x2400
	memory.put(display, 0x2400);

	reset();

	next_int = (1000 / 60);
	interrupt = 1;
}

void loop(void) {
	if (ps2.available()) {
		unsigned key = ps2.read();
		if (ps2.isbreak())
			switch(key) {
			case PS2_F1:
				reset();
				break;
			case PS2_F8:
				cpu.debug();
				break;
			case PAUSE:
				paused = !paused;
				break;
			default:
				io.up(key);
				break;
			}
		else
			io.down(key);
	} else if (paused) {
		// do nothing
	} else if (!halted) {
		cpu.run(1000);
		unsigned long now = millis();
		if (now > next_int) {
			cpu.raise(interrupt);
			interrupt = interrupt == 1? 2: 1;
			next_int = now + 1000 / 60 / 2;
		}
	}
}
