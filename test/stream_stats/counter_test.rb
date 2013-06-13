require 'test_helper'

module StreamStats
  class CounterTest < MiniTest::Spec

    def test_basic
      counter = StreamStats::Counter.new

      (0..20).each do |i|
        counter << i
      end

      assert_equal 21, counter.count
      assert_equal 210.0, counter.sum
      assert_equal 0.0, counter.min
      assert_equal 20.0, counter.max
      assert_equal 10.0, counter.mean
      assert_in_delta 6.2048368229, counter.stddev, 0.0000000001

      assert counter.inspect =~ /#<StreamStats::Counter:0x.*> {count: 21, sum: 210.0, min: 0.0, max: 20.0, mean: 10.0, stddev: 6.2048368229954285}/
    end

  end
end
