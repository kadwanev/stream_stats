#include <stdint.h>
#include <iso646.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include "rate.h"

int init_rate(uint32_t *periods, uint32_t num_periods, rate *rate) {
  return 0;
}

int destroy_rate(rate *rate) {
  return 0;
}

uint64_t current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    return te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
}

int rate_mark(rate *rate, uint64_t count) {
//struct timeval  tv;
//gettimeofday(&tv, NULL);

  return 0;
}

int rate_mark_complete(rate *rate, uint64_t count) {
  return 0;
}

double rate_query(rate *rate, int period) {
  return 0;
}

double rate_total(rate *rate) {
  return 0;
}

