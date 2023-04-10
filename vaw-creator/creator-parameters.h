#pragma once
#include <string>

class creator_parameters {
private:
	int argc;
	char** argv;

	int sample_rate = 44100;
	int bits_per_sample = 16;
	int frequency_herz = 440;
	int duration_seconds = 2;
	int num_channels = 2;
	std::string file_name = "generated_file.wav";

	std::string parse_argument(std::string arg_name);
	int parse_int_argument(std::string arg_name);

	const std::string NOT_FOUND = "";
	const int NOT_FOUND_INT = -1;

public:
	int get_sample_rate() { return sample_rate; }
	int get_bits_per_sample() { return bits_per_sample; }
	int get_frequency_herz() { return frequency_herz; }
	int get_duration_seconds() { return duration_seconds; }
	int get_num_channels() { return num_channels;  }
	std::string get_file_name() { return file_name; }

	creator_parameters(int argc, char** argv);
	void print();
};