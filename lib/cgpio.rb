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
end
