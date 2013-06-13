#include <ruby.h>
#include <stdio.h>

#include "cm_quantile.h"

VALUE quantile_class;

static void strstat_quantile_free(void *ptr) {
  destroy_cm_quantile(ptr);
}

static VALUE strstat_quantile_init(self, rb_eps, rb_quantiles)
  VALUE self, rb_eps, rb_quantiles; {

  cm_quantile *newQuantile = (cm_quantile *) malloc(sizeof(cm_quantile));

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

  init_cm_quantile(eps, quantiles, num_quantiles, newQuantile);

  VALUE data = Data_Wrap_Struct(quantile_class, NULL, strstat_quantile_free, newQuantile);
  rb_ivar_set(self, rb_intern("quantile"), data);

  return Qnil;
}

static VALUE strstat_quantile_add_sample(VALUE self, VALUE rb_sample) {

  double sample = NUM2DBL(rb_sample);

  cm_quantile *quantile;

  VALUE data = rb_ivar_get(self, rb_intern("quantile"));
  Data_Get_Struct(data, cm_quantile, quantile);

  int returned = cm_add_sample(quantile, sample);
  if (returned != 0) {
    rb_raise(rb_eRuntimeError, "add sample returned %d", returned);
  }

  return Qnil;
}

static VALUE strstat_quantile_flush(VALUE self) {
  cm_quantile *quantile;

  VALUE data = rb_ivar_get(self, rb_intern("quantile"));
  Data_Get_Struct(data, cm_quantile, quantile);
  int returned = cm_flush(quantile);
  if (returned != 0) {
    rb_raise(rb_eRuntimeError, "flush returned %d", returned);
  }

  return Qnil;
}

static VALUE strstat_quantile_query(VALUE self, VALUE rb_query) {
  double query = NUM2DBL(rb_query);

  cm_quantile *quantile;

  VALUE data = rb_ivar_get(self, rb_intern("quantile"));
  Data_Get_Struct(data, cm_quantile, quantile);
  return DBL2NUM(cm_query(quantile, query));
}

void Init_stream_stats(void) {
  VALUE module = rb_define_module("StreamStats");

  quantile_class = rb_define_class_under(module, "CMQuantile", rb_cObject);

  rb_define_method(quantile_class, "initialize", strstat_quantile_init, 2);
  rb_define_method(quantile_class, "add_sample", strstat_quantile_add_sample, 1);
  rb_define_method(quantile_class, "flush", strstat_quantile_flush, 0);
  rb_define_method(quantile_class, "query", strstat_quantile_query, 1);
}
