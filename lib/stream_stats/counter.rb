module StreamStats
  class Counter

    ATTRIBUTE_LIST = [:count, :sum, :min, :max, :mean, :stddev]

    def inspect
      attr_list = ATTRIBUTE_LIST.map do |method|
        "#{method.to_s}: #{self.send(method)}"
      end * ', '
      "#{self.to_s} {#{attr_list}}"
    end
  end
end