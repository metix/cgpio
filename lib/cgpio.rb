require "cgpio/version"

module Cgpio
    class Gpio

        attr_reader :pin

        def initialize(pin, options={})
            options = {
                direction: :out
            }.merge(options)

            @pin = pin

            # this will export the pin
            setup @pin

            # set the initial direction
            direction = options[:direction]
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

        def on
            value = true
        end

        def off
            value = false

        def on?
            value
        end

        def off?
            !value
        end
    end
end

require 'cgpio/cgpio'
