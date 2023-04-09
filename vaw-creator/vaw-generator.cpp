#include "vaw-generator.h"
#include <iostream>

vaw_generator::vaw_generator(int frequency, int amplitude, std::basic_fstream<char>* file_stream, std::string file_name) {
	this->frequency = frequency;
	this->amplitude = amplitude;
	this->file_stream = file_stream;
	this->file_name = file_name;
}

void vaw_generator::print() {
	std::cout << frequency << " " << amplitude << std::endl;
}

void vaw_generator::generate() {
	file_stream->open(file_name, std::ios_base::out | std::ios_base::binary);
	file_stream->imbue(std::locale::classic());
	if (file_stream->is_open())
	{
		std::cout << "File " << file_name << " opened" << std::endl;
		riff_chunk(32);
		fmt_chunk();
		data_chunk();
	}
	file_stream->close();
}

void vaw_generator::riff_chunk(int chunk_size) {
	std::cout << "Generating riff chunk" << std::endl;
	file_stream->write("RIFF", 4);

	file_stream->put(chunk_size);
	file_stream->put(chunk_size >> 8);
	file_stream->put(chunk_size >> 16);
	file_stream->put(chunk_size >> 32);

	file_stream->write("WAVE", 4);
}

void vaw_generator::fmt_chunk() {
	std::cout << "Generating fmt chunk" << std::endl;
}

void vaw_generator::data_chunk() {
	std::cout << "Generating data chunk" << std::endl;
}