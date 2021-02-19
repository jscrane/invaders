/**
 * http://www.emutalk.net/threads/38177-Space-Invaders
 */
#include <stdarg.h>
#include <SPI.h>
#include <r65emu.h>
#include <ports.h>
#include <i8080.h>

#include "io.h"
#include "display.h"
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
i8080 cpu(memory, io);
ram page;
Display display;
vblank vb(cpu);

#if defined(DAC_SOUND)
X9C volume;

#define VOLUME_CS	22
#define VOLUME_INC	21
#define VOLUME_UD	19
#endif

static bool paused = false;

static void reset(void) {
	hardware_reset();
	display.begin();
	io.begin();
	paused = false;

#if defined(DAC_SOUND)
	volume.begin(VOLUME_CS, VOLUME_INC, VOLUME_UD);
#endif
}

void setup(void) {
#if defined(DEBUGGING)
	Serial.begin(115200);
#endif

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
}

void loop(void) {
	if (ps2.available()) {
		unsigned scan = ps2.read2();
		byte key = scan & 0xff;
		if (is_down(scan))
			io.down(scan);
		else
			switch(key) {
			case PS2_F1:
				reset();
				break;
#if defined(DAC_SOUND)
			case PS2_F11:
				volume.trimPot(5, X9C_DOWN);
				break;
			case PS2_F12:
				volume.trimPot(5, X9C_UP);
				break;
#endif
			case PAUSE:
				paused = !paused;
				break;
			default:
				io.up(key);
				break;
			}
	} else if (!paused && !cpu.halted()) {
		cpu.run(1000);
		vb.tick(millis());
	}
}
