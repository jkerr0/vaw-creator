#pragma once

class vaw_format {
private:
	const short audio_format = 1; // 1 = PCM, other - compressed
	short num_channels;
	short sample_rate;
	short bits_per_sample;

public:
	vaw_format(short num_channels, short sample_rate, short bits_per_sample);

	short get_audio_format() { return audio_format; }
	short get_num_channels() { return num_channels; }
	int get_sample_rate() { return sample_rate; }
	int get_byte_rate() {
		return sample_rate * get_block_align();
	}
	short get_block_align() { return num_channels * bits_per_sample / 8; }
	short get_bits_per_sample() {
		return bits_per_sample;
	}
};