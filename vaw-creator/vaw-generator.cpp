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

// little endian
void vaw_generator::write_short(short s) {
	for (int byte_index = 0; byte_index < 2; byte_index++) {
		file_stream->put(s >> (8 * byte_index));
	}
}

// little endian
void vaw_generator::write_int(int i) {
	for (int byte_index = 0; byte_index < 4; byte_index++) {
		file_stream->put(i >> (8 * byte_index));
	}
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
	std::vector<std::byte> left_channel_bytes = generator->generate(); // default for mono
	std::vector<std::byte> right_channel_bytes = generator->generate();
	for (int sample_index = 0; sample_index < generator->get_sample_count(); sample_index++) {
		for (int channel = 0; channel < format->get_num_channels(); channel++) {
			std::vector<std::byte> channel_bytes = channel == 0 ? left_channel_bytes : right_channel_bytes;
			int bytes_per_sample = format->get_bits_per_sample() / 8;
			int start_byte_index = sample_index * bytes_per_sample;
			int end_byte_index = start_byte_index + bytes_per_sample;
			for (int byte_index = start_byte_index; byte_index < end_byte_index; byte_index++) {
				unsigned char channel_byte = (unsigned char)channel_bytes.at(byte_index);
				file_stream->put(channel_byte);
			}
		}
	}
}