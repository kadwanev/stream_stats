require 'mkmf'

$CFLAGS += ' ' unless $CFLAGS.empty?
$CFLAGS += '-std=c99'

create_makefile('stream_stats/stream_stats')
