#pragma once

#include <windows.h>

typedef struct {
	HDC screenDC; /* screen device context */
	int screenWidth; /* screen width */
	int screenHeight; /* screen height */
} METRICS;

/* avoid math.h header */
#define M_PI 3.14159265358979323846
#define radians(degrees) degrees * M_PI / 180

/* compiler "optimizations" add around 50kb. I don't like that. */
volatile double isin(double x) {
	__asm {
		fld x
		fsin
	}
}

volatile double icos(double x) {
	__asm {
		fld x
		fcos
	}
}

volatile double isec(double x) {
	return 1 / icos(x);
}

volatile double icsc(double x) {
	return 1 / isin(x);
}

volatile double itan(double x) {
	return isin(x) / icos(x);
}

volatile double icot(double x) {
	return icos(x) / isin(x);
}

#define sin isin
#define cos icos
#define sec isec
#define csc icsc
#define tan itan
#define cot icot