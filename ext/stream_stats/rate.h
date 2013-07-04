#ifndef RATE_H
#define RATE_H
#include <stdint.h>

typedef struct {
    uint32_t *periods;        // Queryable time periods, array
    uint32_t num_periods;     // Number of time periods
    double *period_rates;     // Rate for time period
    uint64_t first_mark;
    uint64_t last_mark;
    uint64_t end_mark;
    uint64_t first_count;
    uint64_t last_count;
} rate;

/**
 * Initializes the rate struct
 * @arg periods An array of time period values in number of seconds
 * @arg num_periods The number of entries in the periods array
 * @arg rate The rate struct to initialize
 * @return 0 on success.
 */
int init_rate(uint32_t *periods, uint32_t num_periods, rate *rate);

/**
 * Destroy the rate struct.
 * @arg rate The rate to destroy
 * @return 0 on success.
 */
int destroy_rate(rate *rate);

/**
 * Mark current count value
 * @arg rate The rate to mark on
 * @arg count The current count value
 * @return 0 on success.
 */
int rate_mark(rate *rate, uint64_t count);

/**
 * Mark current count value and set completed
 * @arg rate The rate to mark on
 * @arg count The current count value
 * @return 0 on success.
 */
int rate_mark_complete(rate *rate, uint64_t count);

/**
 * Query rate of change for specified time period
 * @arg rate The rate to query
 * @return The number of samples
 */
double rate_query(rate *rate, int period);

/**
 * Query rate of change for the total time
 * @arg rate The rate to query
 * @return The number of samples
 */
double rate_total(rate *rate);


#endif