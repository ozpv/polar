#include "polar.h"

inline void toXY(double r, double theta, int *x, int *y) {
	/* x = rcos(theta) */
	/* y = rsin(theta) */

	*x = (int)(r * cos(theta));
	*y = (int)(r * sin(theta));
}

inline void getR(double a, double b, double c, double *r, double theta, volatile double (*func)(double)) {
	/* r = a * func(b * theta) + c */
	/* func is a function pointer to a trigonometric function. */
	/* transformations: */
	/* a: [1, DBL_MAX] */
	/* b: [1, DBL_MAX] */
	/* c: [0, DBL_MAX] */

	*r = a * (*func)(b * (theta)) + c;
}

int main(void) {
	METRICS metrics;
	metrics.screenDC = GetDC(NULL);

	metrics.screenWidth = GetSystemMetrics(SM_CXSCREEN);
	metrics.screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int x;
	int y;
	double r;
	/* theta is i converted to radians */

	double k = 0;
	while (TRUE) {
		for (double i = 0.0; i < 360.0; i++) {
			/* nested for loop. could convert to a while loop also for read-ability. */
			for (double j = 0.0; j < 200.0; j++) {
				getR(j, 6.0, k, &r, radians(i), sin);
				toXY(r, radians(i), &x, &y);
				DrawIcon(metrics.screenDC, (metrics.screenWidth / 2) + x - 16, (metrics.screenHeight / 2) + y - 16, LoadIcon(NULL, IDI_WARNING));
			}
		}
		k += 50;
	}
	return 0;
}