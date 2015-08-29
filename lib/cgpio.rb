require "cgpio/version"

module Cgpio
    class Gpio

        attr_reader :pin

        def initialize(pin, options={})
            options = {
                direction: :out
            }.merge(options)

            @pin = pin

            # this will export the pin and open
            # a filedescriptor for the value of the gpio
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
    end
end

require 'cgpio/cgpio'
