class Cgpio::VirtualGpio < Cgpio::Gpio

    def initialize(nr, options)
        super(nr, options)

        @value = false

        # set the initial direction
        self.direction = @options[:direction]
    end

    def direction=(direction)
        if direction != :in && direction != :out
            raise "unsupported gpio direction. use :out or :in"
        end

        @direction = direction
    end

    def value
        @value
    end

    def value=(val)
        @value = val
    end

    def direction
        @direction
    end

    def on
        self.value = true
    end

    def off
        self.value = false
    end

    def on?
        value
    end

    def off?
        !value
    end
end
