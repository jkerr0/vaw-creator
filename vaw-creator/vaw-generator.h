
#pragma once

#include <fstream>

class vaw_generator {
private:
	int amplitude;
	int frequency;
	std::basic_fstream<char>* file_stream;
	std::string file_name;

	void riff_chunk(int chunk_size);
	void fmt_chunk();
	void data_chunk();
public:
	vaw_generator(int, int, std::basic_fstream<char>*, std::string);
	void print();
	void generate();
};