require 'cgpio/real_gpio'
require 'cgpio/virtual_gpio'

class Cgpio::Gpio
    def self.new(nr, options={})
        if Cgpio.configuration.virtual
            Cgpio::VirtualGpio.new(nr, options)
        else
            Cgpio::RealGpio.new(nr, options)
        end
    end
end
