#include "wave-generator.h"
#include <math.h>
#include <iostream>

wave_generator::wave_generator(int seconds_duration, int sample_rate, short bits_per_sample, double frequency_herz) {
	this->sample_rate = sample_rate;
	this->seconds_duration = seconds_duration;
	this->bits_per_sample = bits_per_sample;
	this->bytes_per_sample = bits_per_sample / 8;
	this->frequency_herz = frequency_herz;
	this->max_amplitude = ((1 << bits_per_sample) - 1)/2;
	this->rest_point = bits_per_sample == 8 ? 127 : 0;
}

void push_sample_back(std::vector<std::byte>* all_samples, std::vector<std::byte>* new_samples) {
	for (int i = 0; i < new_samples->size(); i++) {
		all_samples->push_back(new_samples->at(i));
	}
}

std::vector<std::byte> wave_generator::generate()
{
	std::vector<std::byte> result = std::vector<std::byte>();
	int sample_count = sample_rate * seconds_duration;
	std::cout << "Sample rate: " << sample_rate << std::endl;
	std::cout << "Sample count: " << sample_count << std::endl;
	for (int sample_index = 0; sample_index < sample_count; sample_index++) {
		std::vector<std::byte> sample = get_sample(sample_index);
		push_sample_back(&result, &sample);
	}
	return result;
}

std::vector<std::byte> wave_generator::get_sample(int sample_index) {
	std::vector result = std::vector<std::byte>();
	double time_seconds = (double) sample_index / sample_rate;
	double sample_double = get_sample_double_value(time_seconds);
	if (bits_per_sample == 8) {
		unsigned char sample_value = (unsigned char)sample_double;
		std::byte sample_byte = (std::byte)sample_value;
		result.push_back(sample_byte);
	}
	else if (bits_per_sample == 16) {
		short sample_value = (short)sample_double;
		for (int byte_index = 0; byte_index < bytes_per_sample; byte_index++) {
			unsigned char current_byte = sample_value >> (8 * byte_index);
			std::byte sample_byte = (std::byte)current_byte;
			result.push_back(sample_byte);
		}
	}
	return result;
}

double wave_generator::get_sample_double_value(double time_seconds) {
	double pi = 3.1415;
	double omega = 2 * pi * frequency_herz;
	return max_amplitude * sin(omega * time_seconds) + rest_point;
}

int wave_generator::get_sample_count() {
	return sample_rate * seconds_duration;
}

int wave_generator::get_size() {
	return get_sample_count() * bytes_per_sample;
}

