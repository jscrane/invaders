#pragma once

class input_ports {
public:
	virtual uint8_t read_port1() const = 0;
	virtual uint8_t read_port2() const = 0;
	virtual bool is_paused() const = 0;
	virtual void pause() = 0;
	virtual void reset() = 0;
};
