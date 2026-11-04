#pragma once

class input_ports {
public:
	uint8_t read_port1() const {
		uint8_t p = 0;
		if (_coin)     p |= 0x01;
		if (_p2_start) p |= 0x02;
		if (_p1_start) p |= 0x04;
		if (_p1_shoot) p |= 0x10;
		if (_p1_left)  p |= 0x20;
		if (_p1_right) p |= 0x40;
		return p;
	}

	uint8_t read_port2() const {
		uint8_t p = 0;
		if (_p2_shoot) p |= 0x10;
		if (_p2_left)  p |= 0x20;
		if (_p2_right) p |= 0x40;
		return p;
	}

	bool is_paused() const { return _paused; }
	void pause() { _paused = true; }

	void reset() { clear_ports(); _paused = false; }

protected:
	input_ports() { reset(); }

	void clear_ports() {
		_p1_start = _p1_left = _p1_right = _p1_shoot = false;
		_p2_start = _p2_left = _p2_right = _p2_shoot = false;
		_coin = false;
	}

	bool _p1_start, _p1_left, _p1_right, _p1_shoot;
	bool _p2_start, _p2_left, _p2_right, _p2_shoot;
	bool _coin, _paused;
};
