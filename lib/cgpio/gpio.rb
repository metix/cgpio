class Cgpio::Gpio

    attr_reader :nr

    def initialize(nr, options={})
        options = {
            direction: :out
        }.merge(options)

        @nr = nr

        # this will export the pin
        setup @nr

        # set the initial direction
        self.direction = options[:direction]
    end

    def direction=(direction)
        if direction == :out
            # direction values defined in ext/cgpio/gpio.h
            set_direction(0x01)
        elsif direction == :in
            set_direction(0x02)
        else
            raise "unsupported gpio direction. use :out or :in"
        end
    end

    def direction
        if (get_direction == 0x01)
            :out
        elsif (get_direction == 0x02)
            :in
        else
            raise "unknown gpio direction"
        end
    end

    def on
        self.value = true
    end

    def off
        self.value = false
    end

    def on?
        self.value
    end

    def off?
        !self.value
    end
end
