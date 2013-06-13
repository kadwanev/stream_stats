require 'mkmf'

have_header('ruby.h') or missing('ruby.h')
$CFLAGS += ' ' unless $CFLAGS.empty?
$CFLAGS += '-std=c99'

create_makefile('stream_stats/stream_stats')
