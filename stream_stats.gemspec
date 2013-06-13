# -*- encoding: utf-8 -*-
require 'rake'
require File.expand_path('../lib/stream_stats/version', __FILE__)

Gem::Specification.new do |s|
  s.name        = 'stream_stats'
  s.version     = '0.0.1'
  s.summary     = "Stream Statistics"
  s.description = "Compute statistics on stream data"
  s.version     = StreamStats::VERSION
  s.authors     = ["Neville Kadwa"]
  s.email       = ["neville@kadwa.com"]
  s.files       = FileList['lib/**/*.rb', 'ext/**/*', 'bin/*', '[A-Z]*'].to_a
  s.test_files  = FileList['test/**/*'].to_a
  s.executables = FileList['bin/**/*'].to_a
  s.homepage    = 'http://github.com/kadwanev/stream_stats'
  s.extensions  = ['ext/stream_stats/extconf.rb']
  s.add_development_dependency('rdoc')
end