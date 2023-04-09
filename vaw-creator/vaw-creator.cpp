// vaw-creator.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "vaw-creator.h"
#include "vaw-generator.h"
#include "vaw-format.h"

int main()
{
	const std::string file_name = "my_file.wav";
	std::basic_fstream<char>* vaw_fstream = new std::fstream();
	vaw_format* format = new vaw_format(1, 44100, 8);
	vaw_generator generator = vaw_generator(1, 2, vaw_fstream, file_name, format);
	generator.generate();
	if (vaw_fstream->is_open()) {
		std::cout << "Warning: file stream was open. Closing..." << std::endl;
		vaw_fstream->close();
	}
	return 0;
}
