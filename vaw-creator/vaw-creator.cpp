// vaw-creator.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "vaw-creator.h"
#include "vaw-generator.h"
#include "vaw-format.h"

int main()
{
	const int sample_rate = 44100;
	const int bits_per_sample = 16;
	const int frequency_herz = 440;
	const int duration_seconds = 2;
	const int num_channels = 1;

	const std::string file_name = "generated_file.wav";
	std::basic_fstream<char>* vaw_fstream = new std::fstream();
	vaw_format* format = new vaw_format(num_channels, sample_rate, bits_per_sample);
	wave_generator* w_generator = new wave_generator(duration_seconds, sample_rate, bits_per_sample, frequency_herz);
	vaw_generator generator = vaw_generator(vaw_fstream, file_name, format, w_generator);
	generator.generate_file();
	if (vaw_fstream->is_open()) {
		std::cout << "Warning: file stream was open. Closing..." << std::endl;
		vaw_fstream->close();
	}
	return 0;
}
