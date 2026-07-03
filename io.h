#pragma once

class IO: public matrix_keyboard {
public:
	IO() { _p1 = _p2 = 0; }
	void begin();

	uint8_t in(uint16_t p);
	void out(uint16_t p, uint8_t b);

	void down(uint8_t key) override;
	void up(uint8_t key) override;

	bool is_paused() const { return _paused; }
	void pause() { _paused = true; }

private:
	uint8_t _soff, _s0, _s1, _p1, _p2;
	bool _paused;
};
