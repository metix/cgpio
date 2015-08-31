require 'cgpio/version'
require 'cgpio/gpio'
require 'cgpio/configuration'

# include c extensions
require 'cgpio/cgpio'

module Cgpio
    class << self
        attr_accessor :configuration
    end

    def self.configuration
        @configuration ||= Configuration.new
    end

    def self.reset
        @configuration = Configuration.new
    end

    def self.configure
        yield configuration
    end

    def self.new(nr, options={})
        if Cgpio.configuration.virtual
            Cgpio::VirtualGpio.new(nr, options)
        else
            Cgpio::RealGpio.new(nr, options)
        end
    end
end
