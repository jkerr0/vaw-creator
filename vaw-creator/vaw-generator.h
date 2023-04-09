#pragma once

#include "vaw-format.h"
#include <fstream>

class vaw_generator {
private:
	int amplitude;
	int frequency;
	std::basic_fstream<char>* file_stream;
	std::string file_name;
	vaw_format* format;

	const int sample_rate = 44100;
	const int bits_per_sample = 8;

	void riff_chunk(int chunk_size);
	void fmt_chunk();
	void data_chunk();

	void write_int(int);
	void write_short(short);

public:
	vaw_generator(int, int, std::basic_fstream<char>*, std::string, vaw_format*);
	void print();
	void generate();
};