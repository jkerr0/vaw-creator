#include <vector>

class wave_generator {
private:
	int seconds_duration;
	double frequency_herz;
	int sample_rate;
	short bits_per_sample;
	short bytes_per_sample;
	int max_amplitude;
	int rest_point;

protected:
	std::vector<std::byte> get_sample(int sample_index);
	double get_sample_double_value(double time_seconds);
public:
	wave_generator(int seconds_duration, int sample_rate, short bits_per_sample, double frequency_herz);
	std::vector<std::byte> generate();
	int get_size();
};