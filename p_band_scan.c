#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "filter.h"
#include "signal.h"
#include "timing.h"
#include <pthread.h>

pthread_mutex_t lock;
#define MAXWIDTH 40
#define THRESHOLD 2.0
#define ALIENS_LOW  50000.0
#define ALIENS_HIGH 150000.0

int wow = 0;
double lbg = -1;
double ubg = -1;
void usage() {
  printf("usage: band_scan text|bin|mmap signal_file Fs filter_order num_bands\n");
}

double avg_power(double* data, int num) {

  double ss = 0;
  for (int i = 0; i < num; i++) {
    ss += data[i] * data[i];
  }

  return ss / num;
}

double max_of(double* data, int num) {

  double m = data[0];
  for (int i = 1; i < num; i++) {
    if (data[i] > m) {
      m = data[i];
    }
  }
  return m;
}

double avg_of(double* data, int num) {

  double s = 0;
  for (int i = 0; i < num; i++) {
    s += data[i];
  }
  return s / num;
}

void remove_dc(double* data, int num) {

  double dc = avg_of(data,num);

  printf("Removing DC component of %lf\n",dc);

  for (int i = 0; i < num; i++) {
    data[i] -= dc;
  }
}

struct t_arg{
  int band;
  int num_bands;
  double bandwidth;
  double* band_power;
  double avg_band_power;
};

void * thread_func(void* args){
    struct t_arg * myargs = (struct t_arg *) args;
    int band = myargs->band;
    int num_bands = myargs->num_bands;
    double bandwidth = myargs->bandwidth;
    double* band_power = myargs->band_power;
    double avg_band_power = myargs->avg_band_power;

    for (int band_i = band; band_i < (band+num_bands); band_i++) {
    double band_low  = band_i * bandwidth + 0.0001;
    double band_high = (band_i + 1) * bandwidth - 0.0001;



    if ((band_low >= ALIENS_LOW && band_low <= ALIENS_HIGH) ||
        (band_high >= ALIENS_LOW && band_high <= ALIENS_HIGH)) {

      // band of interest
      if (band_power[band_i] > THRESHOLD * avg_band_power) {
        pthread_mutex_lock(&lock);
        wow = 1;
        if (lbg < 0 || (band_i * bandwidth + 0.0001) < lbg) {
          lbg = band_i * bandwidth + 0.0001;
        }
        if(ubg < ((band_i + 1) * bandwidth - 0.0001)){
          ubg = (band_i + 1) * bandwidth - 0.0001;
        }
        pthread_mutex_unlock(&lock);

      }
     }

  }

    return NULL;

}

int analyze_signal(signal* sig, int filter_order, int num_bands, int num_threads) {

  pthread_t *thread_array = malloc(num_threads * sizeof(pthread_t));
  struct t_arg *thread_args = malloc(num_threads * sizeof(struct t_arg));
  double Fc        = (sig->Fs) / 2;
  double bandwidth = Fc / num_bands;
  int band_ind = 0;
  int rem_bands = num_bands % num_threads;
  remove_dc(sig->data,sig->num_samples);
  pthread_mutex_init(&lock, NULL);


  double signal_power = avg_power(sig->data,sig->num_samples);

  printf("signal average power:     %lf\n", signal_power);

  resources rstart;
  get_resources(&rstart,THIS_PROCESS);

  double filter_coeffs[filter_order + 1];
  double band_power[num_bands];
  for (int band = 0; band < num_bands; band++) {
    // Make the filter
    generate_band_pass(sig->Fs,
                       band * bandwidth + 0.0001, // keep within limits
                       (band + 1) * bandwidth - 0.0001,
                       filter_order,
                       filter_coeffs);
    hamming_window(filter_order,filter_coeffs);

    // Convolve
    convolve_and_compute_power(sig->num_samples,
                               sig->data,
                               filter_order,
                               filter_coeffs,
                               &(band_power[band]));

  }



  resources rend;
  get_resources(&rend,THIS_PROCESS);

  resources rdiff;
  get_resources_diff(&rstart, &rend, &rdiff);

  double avg_band_power = avg_of(band_power,num_bands);
  for(int i = 0;  i < num_threads; i++){
    thread_args[i].band = band_ind;
    if(rem_bands > 0){
     thread_args[i].num_bands = (num_bands/num_threads) + 1;
     band_ind += (num_bands/num_threads) + 1;
     rem_bands--;
    }else{
     thread_args[i].num_bands = (num_bands/num_threads);
     band_ind += (num_bands/num_threads);

    }
    thread_args[i].bandwidth = bandwidth;
    thread_args[i].band_power = band_power;
    thread_args[i].avg_band_power = avg_band_power;
    pthread_create(&thread_array[i], NULL, thread_func, &thread_args[i]);
  }


  for(int i = 0; i < num_threads; i++){
    pthread_join(thread_array[i], NULL);
  }

  pthread_mutex_destroy(&lock);
  free(thread_array);
  free(thread_args);

  return wow;

}

int main(int argc, char* argv[]) {

  if (argc != 8) {
    usage();
    return -1;
  }

  char sig_type    = toupper(argv[1][0]);
  char* sig_file   = argv[2];
  double Fs        = atof(argv[3]);
  int filter_order = atoi(argv[4]);
  int num_bands    = atoi(argv[5]);
  int num_threads = atoi(argv[6]);
  int num_proc   = atoi(argv[7]);


  if(num_proc < num_threads){
    num_threads = num_proc;
  }
  assert(Fs > 0.0);
  assert(filter_order > 0 && !(filter_order & 0x1));
  assert(num_bands > 0);

  printf("type:     %s\n\
file:     %s\n\
Fs:       %lf Hz\n\
order:    %d\n\
bands:    %d\n",
         sig_type == 'T' ? "Text" : (sig_type == 'B' ? "Binary" : (sig_type == 'M' ? "Mapped Binary" : "UNKNOWN TYPE")),
         sig_file,
         Fs,
         filter_order,
         num_bands);

  printf("Load or map file\n");

  signal* sig;
  switch (sig_type) {
    case 'T':
      sig = load_text_format_signal(sig_file);
      break;

    case 'B':
      sig = load_binary_format_signal(sig_file);
      break;

    case 'M':
      sig = map_binary_format_signal(sig_file);
      break;

    default:
      printf("Unknown signal type\n");
      return -1;
  }

  if (!sig) {
    printf("Unable to load or map file\n");
    return -1;
  }

  sig->Fs = Fs;

  if (analyze_signal(sig, filter_order, num_bands, num_threads)) {
    printf("POSSIBLE ALIENS %lf-%lf HZ (CENTER %lf HZ)\n", lbg, ubg, (ubg + lbg) / 2.0);
  } else {
    printf("no aliens\n");
  }

  free_signal(sig);

  return 0;
}

