class Cgpio::VirtualGpio < Cgpio::Gpio

    def initialize(nr, options)
        super(nr, options)

        @value = false
        @events = {}

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
        if @value != val && @events[:value_change]
            @events[:value_change].call(val, @value)
        end

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

    def value_change(&block)
        @events[:value_change] = block
    end
end
