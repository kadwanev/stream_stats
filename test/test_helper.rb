if ENV['COVERAGE']
  require 'simplecov'
  SimpleCov.start
end

require 'rubygems'
require 'bundler/setup'
require 'minitest/autorun'
Bundler.require :default
