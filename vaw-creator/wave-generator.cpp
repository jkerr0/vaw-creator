#include "wave-generator.h"
#include <math.h>
#include <iostream>

wave_generator::wave_generator(int seconds_duration, int sample_rate, short bits_per_sample, double frequency_herz) {
	this->sample_rate = sample_rate;
	this->seconds_duration = seconds_duration;
	this->bits_per_sample = bits_per_sample;
	this->bytes_per_sample = bits_per_sample / 8;
	this->frequency_herz = frequency_herz;
	int safety_limit = 2000;
	this->max_amplitude = ((1 << bits_per_sample) - 1)/2;
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
		std::cout << "sample: " << sample_index << std::endl;
		push_sample_back(&result, &sample);
	}
	return result;
}

std::vector<std::byte> wave_generator::get_sample(int sample_index) {
	std::vector result = std::vector<std::byte>();
	double time_seconds = (double) sample_index / sample_rate;
	int sample_int = (int)get_sample_value(time_seconds);
	for (int byte_index = 0; byte_index < bytes_per_sample; byte_index++) {
		std::byte sample_byte = (std::byte)sample_int << (8 * byte_index);
		result.push_back(sample_byte);
	}
	return result;
}

double wave_generator::get_sample_value(double time_seconds) {
	double pi = 3.1415;
	double omega = 2 * pi * frequency_herz;
	return max_amplitude * sin(omega * time_seconds);
}

int wave_generator::get_size() {
	return (sample_rate * seconds_duration) * (bits_per_sample / 8);
}

