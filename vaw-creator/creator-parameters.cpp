#include "creator-parameters.h"
#include <iostream>

std::string creator_parameters::parse_argument(std::string arg_name) {
	if (argc <= 1) {
		return NOT_FOUND;
	}

	int argi;
	for (argi = 0; argi < argc && arg_name.compare(argv[argi]) != 0; argi++);

	if (argi == argc || argi + 1 == argc) {
		return NOT_FOUND;
	}

	return std::string(argv[argi + 1]);
}

int creator_parameters::parse_int_argument(std::string arg_name) {
	std::string arg = parse_argument(arg_name);
	return arg.compare(NOT_FOUND) == 0 ? NOT_FOUND_INT : std::stoi(arg);
}

creator_parameters::creator_parameters(int argc, char** argv)
{
	this->argc = argc;
	this->argv = argv;

	std::string sample_rate_arg = "--sample-rate";
	std::string bits_per_sample_arg = "--bits";
	std::string frequency_herz_arg = "--freq";
	std::string duration_seconds_arg = "--duration";
	std::string num_channels_arg = "--channels";
	std::string file_name_arg = "--name";

	int sample_rate = parse_int_argument(sample_rate_arg);
	if (sample_rate != NOT_FOUND_INT) {
		this->sample_rate = sample_rate;
	}
	int bits_per_sample = parse_int_argument(bits_per_sample_arg);
	if (bits_per_sample != NOT_FOUND_INT) {
		this->bits_per_sample = bits_per_sample;
	}
	int frequency_herz = parse_int_argument(frequency_herz_arg);
	if (frequency_herz != NOT_FOUND_INT) {
		this->frequency_herz = frequency_herz;
	}
	int duration_seconds = parse_int_argument(duration_seconds_arg);
	if (duration_seconds != NOT_FOUND_INT) {
		this->duration_seconds = duration_seconds;
	}
	int num_channels = parse_int_argument(num_channels_arg);
	if (num_channels != NOT_FOUND_INT) {
		this->num_channels = num_channels;
	}
	std::string file_name = parse_argument(file_name_arg);
	if (file_name.compare(NOT_FOUND) != 0) {
		this->file_name = file_name;
	}
}

void creator_parameters::print() {
	std::cout << "Sample rate: " << sample_rate << std::endl;
	std::cout << "Bits per sample: " << bits_per_sample << std::endl;
	std::cout << "Frequency (Hz): " << frequency_herz << std::endl;
	std::cout << "Duration (s): " << duration_seconds << std::endl;
	std::cout << "Number of channels: " << num_channels << std::endl;
	std::cout << "File name: " << file_name << std::endl;
	std::cout << std::endl;
}
