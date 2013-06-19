module StreamStats
  class Stream

    ATTRIBUTE_LIST = [:count, :sum, :min, :max, :mean, :stddev]

    def get_quantiles
      Hash[@quantiles.map do |q|
        [q, quantile(q)]
      end]
    end

    def inspect
      attr_list = ATTRIBUTE_LIST.map do |method|
        "#{method.to_s}: #{self.send(method)}"
      end * ', '
      "#{self.to_s} {#{attr_list}, quantiles: #{get_quantiles.to_s}}"
    end
  end
end