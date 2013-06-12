#include <ruby.h>
#include "cm_quantile.h"

static VALUE stream_stats_add_sample(VALUE self) {
  return rb_str_new2("stream stats!");
}

void Init_stream_stats(void) {
  VALUE klass = rb_define_class("CMQuantile", rb_cObject);

  rb_define_singleton_method(klass, "add_sample", stream_stats_add_sample, 0);
}
