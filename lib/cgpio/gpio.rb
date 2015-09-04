class Cgpio::Gpio
    attr_reader :nr

    def initialize(nr, options)
        @options = {
            direction: :out,
            value: false
        }.merge(options)

        @nr = nr
    end
end

require 'cgpio/real_gpio'
require 'cgpio/virtual_gpio'
