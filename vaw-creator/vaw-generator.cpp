#include "vaw-generator.h"

class vaw_generator {
private:
	int frequency;
	int amplitude;

public:
	vaw_generator(int frequency, int amplitude) {
		this->frequency = frequency;
		this->amplitude = amplitude;
	}
};