// vaw-creator.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "vaw-creator.h"
#include <fstream>

using namespace std;

int main()
{
	const string file_name = "file.wav";
	basic_fstream<char> vaw_fstream = fstream();
	vaw_fstream.open(file_name, ios_base::out);
	if (vaw_fstream.is_open())
	{
		cout << "File " << file_name << " opened" << endl;
		vaw_fstream.write("abc", 3);
	}
	vaw_fstream.close();
	return 0;
}
