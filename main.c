// global includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <portaudio.h>

// macro and structure defs
#define SAMPLE_RATE 44100 // constant as audio quality does not matter much here
#define CONST_PI 3.14159265358979323846

typedef struct { // for using user data in PortAudio callback
    bool h_flag;
    float freq_hz;
    int duration_ms;
    float phase;
} sine_wave_data;

// defining functions before use in main()
int audio_sine_callback(const void *input_buffer, void *output_buffer, unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags status_flags, void *user_data);
void cleanup(bool pa_been_init, bool stream_been_init, PaStream *p_stream);
void print_help_menu();

int main(int argc, char *argv[]) {
    // init necessary variables
    bool pa_been_init = false;
    bool stream_been_init = false;

    sine_wave_data user_sine_data = { // struct to store user input
        .h_flag = false,
        .freq_hz = -1.0, // -1.0 means user has not entered this info
        .duration_ms = -1, // -1.0 means user has not entered this info
        .phase = 0.0, // DEFAULT
    };

    // printing options if no arguments are provided
    if (argc < 2) {
        fprintf(stderr, "ERROR: %s\n", "not enough arguments");
        print_help_menu();
        cleanup(pa_been_init, stream_been_init, NULL);
        return -1;
    }

    // iterating over all parsed arguments, collecting necessary flags
    for (int i=0; i < argc; i++) { // also includes i==0 (program name)
        const char *curr_arg = argv[i];
        
        // use a list of all possible flags --> compare within this list
        if ( strcmp(curr_arg, "-h") == 0 ) {
            user_sine_data.h_flag = true;
        } else if ( strcmp(curr_arg, "-f") == 0 ) {
            // checking if a valid argument is availabel after the flag --> out-of-bounds check
            if (i+1 < argc) {
                // attempting to convert the argument to a float64 (receive as int an typecast)
                char *p_f_val_str = argv[i+1];
                int conv_int_val = atoi(p_f_val_str);
                double conv_f64_val = (double)conv_int_val;
                if (conv_f64_val == 0.0) {
                    fprintf(stderr, "ERROR: %s\n", "failed frequency char* conversion");
                    cleanup(pa_been_init, stream_been_init, NULL);
                    return -1;
                }
                user_sine_data.freq_hz = conv_f64_val;
            }
        } else if ( strcmp(curr_arg, "-d") == 0 ) {
            // checking if a valid argument is availabel after the flag --> out-of-bounds check
            if (i+1 < argc) {
                // attempting to convert the argument to a float64
                char *p_d_val_str = argv[i+1];
                int conv_int_val = atoi(p_d_val_str);
                if (conv_int_val == 0) {
                    fprintf(stderr, "ERROR: %s\n", "failed duration char* conversion");
                    cleanup(pa_been_init, stream_been_init, NULL);
                    return -1;
                }
                user_sine_data.duration_ms = conv_int_val;
            }
        } else { // move past the current argument
            continue;
        }
    }

    // printing help menu and quiting if flag mentioned
    if (user_sine_data.h_flag) {
        print_help_menu();
        cleanup(pa_been_init, stream_been_init, NULL);
        return 0;
    }

    // check that both freq and duration have been set successfully
    if (user_sine_data.freq_hz <= 0 || user_sine_data.duration_ms <= 0) {
        fprintf(stderr, "ERROR: %s\n", "either freq or duration was not correctly configured");
        cleanup(pa_been_init, stream_been_init, NULL);
        return -1;
    }

    // init PortAudio
    PaError pa_err = Pa_Initialize();
    if (pa_err != paNoError) { // if failure during init
        fprintf(stderr, "ERROR: Failed to initialize PortAudio (%s)\n", Pa_GetErrorText(pa_err));
        cleanup(pa_been_init, stream_been_init, NULL);
        return -1;
    }
    pa_been_init = true; // flag for cleanup

    // open an audio stream
    PaStream *p_stream;
    pa_err = Pa_OpenDefaultStream(&p_stream, 0, 1, paFloat32, SAMPLE_RATE, 256, audio_sine_callback, &user_sine_data);
    if (pa_err != paNoError) {
        fprintf(stderr, "ERROR: Failed to open audio stream (%s)\n", Pa_GetErrorText(pa_err));
        cleanup(pa_been_init, stream_been_init, NULL);
        return -1;
    }
    stream_been_init = true; // flag for cleanup

    // start the audio stream
    pa_err = Pa_StartStream(p_stream);
    if (pa_err != paNoError) {
        fprintf(stderr, "ERROR: Failed to start audio stream (%s)\n", Pa_GetErrorText(pa_err));
        cleanup(pa_been_init, stream_been_init, p_stream);
        return -1;
    }

    // play the sound for the specified duration
    Pa_Sleep(user_sine_data.duration_ms); // sleep the computer until the sound has played entirely

    // stop the audio stream after the specified time
    pa_err = Pa_StopStream(p_stream);
    if (pa_err != paNoError) {
        fprintf(stderr, "ERROR: failed to stop audio stream (%s)\n", Pa_GetErrorText(pa_err));
        cleanup(pa_been_init, stream_been_init, p_stream);
        return -1;
    }

    // cleaning up all allocated memory
    cleanup(pa_been_init, stream_been_init, p_stream); 
    return 0;
}

// called when playing audio
int audio_sine_callback(const void *input_buffer, void *output_buffer, unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags status_flags, void *user_data) {
    sine_wave_data *data = (sine_wave_data *)user_data;
    float *output = (float *)output_buffer;
    (void)input_buffer; // Prevent unused variable warning

    for (unsigned long i = 0; i < frames_per_buffer; i++) {
        *output++ = (float)sin(data->phase); // Generate sine wave sample
        data->phase += (2.0 * CONST_PI * data->freq_hz) / (double)SAMPLE_RATE;
        if (data->phase >= 2.0 * CONST_PI) {
            data->phase -= 2.0 * CONST_PI; // keep phase within bounds
        }
    }
    return paContinue;
}

void cleanup(bool pa_been_init, bool stream_been_init, PaStream *p_stream) {
    // freeing all memory used by PortAudio (if alloc'd)
    if (pa_been_init) {
        Pa_Terminate();
    }

    // freeing memory used by PortAudio for stream obj
    if (stream_been_init) {
        Pa_CloseStream(p_stream);
    }
}

// simplistic way of writing out the possible program options
void print_help_menu() {
    printf("%s", "USAGE: ./ToneGen <args/options>\n\n");
    printf("%s", "### OPTIONS ###\n");
    printf("%s", "-h = Show Help Menu\n");
    printf("%s", "-f = Define Frequency - follow by freq argument (in Hz)\n");
    printf("%s", "-d = Define Duration - follow by duration argument (in ms)\n");
}