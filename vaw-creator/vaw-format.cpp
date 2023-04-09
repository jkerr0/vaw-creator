
#include "vaw-format.h"

vaw_format::vaw_format(short num_channels, short sample_rate, short bits_per_sample) {
	this->num_channels = num_channels;
	this->sample_rate = sample_rate;
	this->bits_per_sample = bits_per_sample;

	if (bits_per_sample % 8 != 0) {
		throw 1;
	}
	if (num_channels < 0 || num_channels > 2) {
		throw 2;
	}
}