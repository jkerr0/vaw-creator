#include "vaw-generator.h"
#include <iostream>

vaw_generator::vaw_generator(std::basic_fstream<char>* file_stream, std::string file_name, vaw_format* format, wave_generator* generator) {
	this->file_stream = file_stream;
	this->file_name = file_name;
	this->format = format;
	this->generator = generator;
	this->data_subchunk_size = generator->get_size() * format->get_num_channels();
}

void vaw_generator::generate_file() {
	file_stream->open(file_name, std::ios_base::out | std::ios_base::binary);
	file_stream->imbue(std::locale::classic());
	if (file_stream->is_open())
	{
		std::cout << "File " << file_name << " opened" << std::endl;
		int non_data_size = 36;
		riff_chunk(non_data_size + data_subchunk_size);
		fmt_chunk();
		data_chunk();
	}
	file_stream->close();
}

void vaw_generator::write_short(short s) {
	file_stream->put(s);
	file_stream->put(s >> 8);
}

void vaw_generator::write_int(int i) {
	file_stream->put(i);
	file_stream->put(i >> 8);
	file_stream->put(i >> 16);
	file_stream->put(i >> 24);
}

void vaw_generator::riff_chunk(int chunk_size) {
	std::cout << "Generating riff chunk" << std::endl;
	// ChunkID
	file_stream->write("RIFF", 4);

	// ChunkSize
	write_int(chunk_size);

	// Format
	file_stream->write("WAVE", 4);
}

void vaw_generator::fmt_chunk() {
	std::cout << "Generating fmt chunk" << std::endl;
	// Subchunk1ID
	file_stream->write("fmt ", 4);

	// Subchunk1Size
	unsigned int fmt_chunk_size = 16;
	write_int(fmt_chunk_size);

	write_short(format->get_audio_format());
	write_short(format->get_num_channels());
	write_int(format->get_sample_rate());
	write_int(format->get_byte_rate());
	write_short(format->get_block_align());
	write_short(format->get_bits_per_sample());
}

void vaw_generator::data_chunk() {
	std::cout << "Generating data chunk" << std::endl;
	// Subchunk2ID
	file_stream->write("data", 4);

	// Subchunk2Size
	std::cout << "data sub:" << data_subchunk_size << std::endl;
	write_int(data_subchunk_size);

	// data
	for (int channel = 0; channel < format->get_num_channels(); channel++) {
		std::cout << "Channel " << channel << std::endl;
		std::vector<std::byte> channel_bytes = generator->generate();
		for (std::byte channel_byte : channel_bytes) {
			file_stream->put((unsigned char)channel_byte);
		}
	}
}