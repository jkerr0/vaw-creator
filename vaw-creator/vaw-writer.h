#pragma once

#include "vaw-format.h"
#include "wave-generator.h"
#include <fstream>

class vaw_writer {
private:
	std::basic_fstream<char>* file_stream;
	std::string file_name;
	vaw_format* format;
	wave_generator* generator;
	int data_subchunk_size;

	void riff_chunk(int chunk_size);
	void fmt_chunk();
	void data_chunk();

	void write_int(int);
	void write_short(short);

public:
	vaw_writer(std::basic_fstream<char>* file_stream, std::string file_name, vaw_format* format, wave_generator* generator);
	void write_file();
};