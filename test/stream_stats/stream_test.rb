require 'test_helper'

module StreamStats
  class StreamTest < MiniTest::Spec

    def test_basic
      stream = StreamStats::Stream.new(0.001, [0.50, 0.90])

      (0..20).each do |i|
        stream << i
      end

      assert_equal 21, stream.count
      assert_equal 210.0, stream.sum
      assert_equal 0.0, stream.min
      assert_equal 20.0, stream.max
      assert_equal 10.0, stream.mean
      assert_in_delta 6.2048368229, stream.stddev, 0.0000000001
      assert_equal 10.0, stream.quantile(0.50)
      assert_equal 10.0, stream.percentile(50)
      assert_equal 18.0, stream.quantile(0.90)
      assert_equal 18.0, stream.percentile(90)
      assert_equal Hash[0.50 => 10.0, 0.9 => 18.0], stream.get_quantiles

      assert stream.inspect =~ /#<StreamStats::Stream:0x.*> {count: 21, sum: 210.0, min: 0.0, max: 20.0, mean: 10.0, stddev: 6.2048368229954285, quantiles: {0.5=>10.0, 0.9=>18.0}}/
    end

  end
end
