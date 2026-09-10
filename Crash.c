#include <math.h>

double InfFunction(int);

int main() {
	while (1) {
		InfFunction(30);
	};

	return 0;
};

double InfFunction(int Time) {
	if (Time) {
		return InfFunction(Time - 1) * 5 * 7 * 8 * log(9) * log(Time) + log10(Time) * log2(Time) * 12 * 8 * 7 * 3;
	} else {
		return 20;
	};
};