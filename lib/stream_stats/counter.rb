module StreamStats
  class Counter

    def inspect
      attr_list = [:count, :sum, :min, :max, :mean, :stddev].map do |method|
        "#{method.to_s}: #{self.send(method)}"
      end * ', '
      "#{self.to_s} {#{attr_list}}"
    end
  end
end