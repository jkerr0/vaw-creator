// vaw-creator.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "vaw-creator.h"

int main(int argc, char** argv)
{
	creator_parameters parameters = creator_parameters(argc, argv);
	parameters.print();

	std::basic_fstream<char>* vaw_fstream = new std::fstream();
	vaw_format* format = new vaw_format(parameters.get_num_channels(), parameters.get_sample_rate(), parameters.get_bits_per_sample());
	wave_generator* w_generator = new wave_generator(
		parameters.get_duration_seconds(),
		parameters.get_sample_rate(),
		parameters.get_bits_per_sample(),
		parameters.get_frequency_herz()
	);

	vaw_writer writer = vaw_writer(
		vaw_fstream,
		parameters.get_file_name(),
		format,
		w_generator
	);

	writer.write_file();
	if (vaw_fstream->is_open()) {
		std::cout << "Warning: file stream was open. Closing..." << std::endl;
		vaw_fstream->close();
	}
	return 0;
}
