require 'bundler/setup'
require 'rake'
require 'rake/testtask'
require 'rake/clean'
require 'rdoc/task'

task default: :test

NAME = 'stream_stats'

# rule to build the extension: this says
# that the extension should be rebuilt
# after any change to the files in ext
file "lib/#{NAME}/#{NAME}.#{RbConfig::CONFIG['DLEXT']}" =>
         Dir.glob("ext/#{NAME}/*{.rb,.c}") do
  Dir.chdir("ext/#{NAME}") do
    # this does essentially the same thing
    # as what RubyGems does
    ruby "extconf.rb"
    sh "make"
  end
  cp "ext/#{NAME}/#{NAME}.#{RbConfig::CONFIG['DLEXT']}", "lib/#{NAME}"
end


# make the :test task depend on the shared
# object, so it will be built automatically
# before running the tests
task :test => "lib/#{NAME}/#{NAME}.#{RbConfig::CONFIG['DLEXT']}"

# use 'rake clean' and 'rake clobber' to
# easily delete generated files
CLEAN.include("ext/**/*{.o,.log,.#{RbConfig::CONFIG['DLEXT']}}")
CLEAN.include('ext/**/Makefile')
CLEAN.include("lib/#{NAME}/#{NAME}.#{RbConfig::CONFIG['DLEXT']}")
CLOBBER.include("lib/**/*.#{RbConfig::CONFIG['DLEXT']}")

task :build => [:clean] do
  exec 'gem build stream_stats.gemspec'
end

Rake::TestTask.new(:test) do |t|
  t.libs << 'lib'
  t.libs << 'test'
  t.pattern = 'test/**/*_test.rb'
  t.verbose = true
end

desc 'Generate documentation.'
RDoc::Task.new(:rdoc) do |rdoc|
  rdoc.rdoc_dir = 'rdoc'
  rdoc.title    = 'StreamStats'
  rdoc.options << '--line-numbers' << '--inline-source'
  rdoc.rdoc_files.include('README.rdoc')
  rdoc.rdoc_files.include('lib/**/*.rb')
end
