### WAV file creator

This CLI program generates .wav file containing a generated sine wave. User can specify following parameters of a generated file.
- `--sample-rate` - sample rate of file [Hz] (default 44100)
- `--bits` - number of bits per sample (8 or 16, default: 16)
- `--freq` - frequency [Hz] of sine wave (default: 440)
- `--duration` - duration in whole seconds (default: 2)
- `--channels` - number of channels (1 - mono or 2 - stereo, default: 2)
- `--name` - name of result file (default: generated_file.wav)

Example usage:
```
$ ./wav_generator --sample-rate 44100 --bits 8 --freq 220 --duration 2 --channels 1 --name my_file.wav
```

Program was created using WAVE PCM file structure description: https://ccrma.stanford.edu/courses/422-winter-2014/projects/WaveFormat/ 