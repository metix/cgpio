class Cgpio::RealGpio < Cgpio::Gpio

    def initialize(nr, options)
        super(nr, options)

        setup nr

        # set the initial direction and value
        self.direction = @options[:direction]
        if direction == :out
            self.value = @options[:value]
        end
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
