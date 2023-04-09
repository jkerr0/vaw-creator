// vaw-creator.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "vaw-creator.h"
#include "vaw-generator.h"

using namespace std;

int main()
{
	const string file_name = "my_file.wav";
	basic_fstream<char>* vaw_fstream = new fstream();
	vaw_generator generator = vaw_generator(1, 2, vaw_fstream, file_name);
	generator.generate();
	if (vaw_fstream->is_open()) {
		cout << "Warning: file stream was open. Closing..." << endl;
		vaw_fstream->close();
	}
	return 0;
}
