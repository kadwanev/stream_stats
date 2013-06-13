#include <ruby.h>
#include <stdio.h>

#include "timer.h"

VALUE timer_class;

static void strstat_timer_free(void *ptr) {
  destroy_timer(ptr);
}

static VALUE strstat_timer_init(VALUE self, VALUE rb_eps, VALUE rb_quantiles) {

  timer *i_timer = (timer *) malloc(sizeof(timer));

  double eps = NUM2DBL(rb_eps);
  double *quantiles;
  uint32_t num_quantiles;

  switch (TYPE(rb_quantiles)) {
    case T_ARRAY:
      num_quantiles = RARRAY_LEN(rb_quantiles);
      quantiles = malloc(sizeof(double) * num_quantiles);
      for (int i = 0; i < num_quantiles; i++) {
        quantiles[i] = NUM2DBL(rb_ary_entry(rb_quantiles, i));
      }
      break;
    default:
      /* raise exception */
      rb_raise(rb_eTypeError, "not valid value");
      break;
  }

  init_timer(eps, quantiles, num_quantiles, i_timer);

  VALUE data = Data_Wrap_Struct(timer_class, NULL, strstat_timer_free, i_timer);
  rb_ivar_set(self, rb_intern("timer"), data);

  return Qnil;
}

static VALUE strstat_timer_add_sample(VALUE self, VALUE rb_sample) {

  double sample = NUM2DBL(rb_sample);

  timer *i_timer;

  VALUE data = rb_ivar_get(self, rb_intern("timer"));
  Data_Get_Struct(data, timer, i_timer);

  int returned = timer_add_sample(i_timer, sample);
  if (returned != 0) {
    rb_raise(rb_eRuntimeError, "add sample returned %d", returned);
  }

  return Qnil;
}

static VALUE strstat_timer_count(VALUE self) {
  timer *i_timer;

  VALUE data = rb_ivar_get(self, rb_intern("timer"));
  Data_Get_Struct(data, timer, i_timer);

  return LONG2NUM(timer_count(i_timer));
}

static VALUE strstat_timer_query(VALUE self, VALUE rb_query) {
  double query = NUM2DBL(rb_query);

  timer *i_timer;

  VALUE data = rb_ivar_get(self, rb_intern("timer"));
  Data_Get_Struct(data, timer, i_timer);
  return DBL2NUM(timer_query(i_timer, query));
}

static VALUE strstat_timer_commoncall(VALUE self, double(*func)(timer*)) {
  timer *i_timer;

  VALUE data = rb_ivar_get(self, rb_intern("timer"));
  Data_Get_Struct(data, timer, i_timer);
  return DBL2NUM((*func)(i_timer));
}

static VALUE strstat_timer_min(VALUE self) {
  return strstat_timer_commoncall(self, timer_min);
}
static VALUE strstat_timer_max(VALUE self) {
  return strstat_timer_commoncall(self, timer_max);
}
static VALUE strstat_timer_mean(VALUE self) {
  return strstat_timer_commoncall(self, timer_mean);
}
static VALUE strstat_timer_stddev(VALUE self) {
  return strstat_timer_commoncall(self, timer_stddev);
}
static VALUE strstat_timer_sum(VALUE self) {
  return strstat_timer_commoncall(self, timer_sum);
}
static VALUE strstat_timer_squared_sum(VALUE self) {
  return strstat_timer_commoncall(self, timer_squared_sum);
}

void Init_stream_stats(void) {
  VALUE module = rb_define_module("StreamStats");

  timer_class = rb_define_class_under(module, "Timer", rb_cObject);

  rb_define_method(timer_class, "initialize", strstat_timer_init, 2);
  rb_define_method(timer_class, "add_sample", strstat_timer_add_sample, 1);
  rb_define_method(timer_class, "count", strstat_timer_count, 0);
  rb_define_method(timer_class, "query", strstat_timer_query, 1);
  rb_define_method(timer_class, "min", strstat_timer_min, 0);
  rb_define_method(timer_class, "max", strstat_timer_max, 0);
  rb_define_method(timer_class, "mean", strstat_timer_mean, 0);
  rb_define_method(timer_class, "stddev", strstat_timer_stddev, 0);
  rb_define_method(timer_class, "sum", strstat_timer_sum, 0);
  rb_define_method(timer_class, "squared_sum", strstat_timer_squared_sum, 0);

}
