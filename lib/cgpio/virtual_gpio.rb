class Cgpio::VirtualGpio
    attr_reader :nr

    def initialize(nr, options={})
        options = {
            direction: :out
        }.merge(options)

        @nr = nr
        @value = false

        # set the initial direction
        self.direction = options[:direction]
    end

    def direction=(direction)
        if direction == :out
            @direction = 0x01
        elsif direction == :in
            @direction = 0x02
        else
            raise "unsupported gpio direction. use :out or :in"
        end
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
