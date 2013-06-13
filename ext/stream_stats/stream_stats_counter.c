#include <ruby.h>
#include <stdio.h>

#include "counter.h"

VALUE counter_class;

static VALUE strstat_counter_init(VALUE self) {
  counter *i_counter;
  VALUE data;

  i_counter = (counter *) malloc(sizeof(counter));

  init_counter(i_counter);

  data = Data_Wrap_Struct(counter_class, NULL, free, i_counter);
  rb_ivar_set(self, rb_intern("internal_struct"), data);

  return Qnil;
}

static void *strstat_get_struct(VALUE self) {
  void *ptr;
  VALUE data;

  data = rb_ivar_get(self, rb_intern("internal_struct"));
  Data_Get_Struct(data, counter, ptr);
  return ptr;
}

static VALUE strstat_counter_add_sample(VALUE self, VALUE rb_sample) {
  double sample;
  counter *i_counter;
  int returned;

  sample = NUM2DBL(rb_sample);

  i_counter = (counter*) strstat_get_struct(self);

  returned = counter_add_sample(i_counter, sample);
  if (returned != 0) {
    rb_raise(rb_eRuntimeError, "add sample returned %d", returned);
  }

  return Qnil;
}

static VALUE strstat_counter_count(VALUE self) {
  counter *i_counter;

  i_counter = (counter*) strstat_get_struct(self);

  return LONG2NUM(counter_count(i_counter));
}

static VALUE strstat_counter_commoncall(VALUE self, double(*func)(counter*)) {
  counter *i_counter;

  i_counter = (counter*) strstat_get_struct(self);
  return DBL2NUM((*func)(i_counter));
}

static VALUE strstat_counter_min(VALUE self) {
  return strstat_counter_commoncall(self, counter_min);
}
static VALUE strstat_counter_max(VALUE self) {
  return strstat_counter_commoncall(self, counter_max);
}
static VALUE strstat_counter_mean(VALUE self) {
  return strstat_counter_commoncall(self, counter_mean);
}
static VALUE strstat_counter_stddev(VALUE self) {
  return strstat_counter_commoncall(self, counter_stddev);
}
static VALUE strstat_counter_sum(VALUE self) {
  return strstat_counter_commoncall(self, counter_sum);
}
static VALUE strstat_counter_squared_sum(VALUE self) {
  return strstat_counter_commoncall(self, counter_squared_sum);
}

void Init_stream_stats_counter(void) {
  VALUE module;

  module = rb_define_module("StreamStats");

  counter_class = rb_define_class_under(module, "Counter", rb_cObject);

  rb_define_method(counter_class, "initialize", strstat_counter_init, 0);
  rb_define_method(counter_class, "<<", strstat_counter_add_sample, 1);
  rb_define_method(counter_class, "count", strstat_counter_count, 0);
  rb_define_method(counter_class, "min", strstat_counter_min, 0);
  rb_define_method(counter_class, "max", strstat_counter_max, 0);
  rb_define_method(counter_class, "mean", strstat_counter_mean, 0);
  rb_define_method(counter_class, "stddev", strstat_counter_stddev, 0);
  rb_define_method(counter_class, "sum", strstat_counter_sum, 0);
  rb_define_method(counter_class, "squared_sum", strstat_counter_squared_sum, 0);

}
