
#include "ESP32_RMT_Driver.h"

uint32_t   GetRGB(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

/*
uint32_t   GetPercRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t Perc) {
	uint8_t rP, gP, bP;
	rP = (uint8_t)r * 100 / Perc;
	gP = (uint8_t)g * 100 / Perc;
	bP = (uint8_t)b * 100 / Perc;
	return ((uint32_t)rP << 16) | ((uint32_t)gP << 8) | bP;
}
*/

uint32_t   GetPercRGB(uint32_t RGB, uint32_t Perc) {
	return ((RGB & 0x0000FF) * Perc / 100)
		| ((((RGB & 0x00FF00) >> 8) * Perc / 100) << 8)
		| ((((RGB & 0xFF0000) >> 16) * Perc / 100) << 16);
}

void AnimBuilInLed() {
	int cpt;

	cpt++;

	if (cpt > 100) {

	};

	digitalWrite(12, HIGH);

}
