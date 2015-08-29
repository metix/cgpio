# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'cgpio/version'

Gem::Specification.new do |spec|
  spec.name          = "cgpio"
  spec.version       = Cgpio::VERSION
  spec.authors       = ["Maximilian Etti"]
  spec.email         = ["maximilian_etti@yahoo.de"]

  spec.summary       = "GPIO C Wrapper for Beaglebone Black"
  spec.description   = "A simple GPIO C Wrapper for Beaglebone Black."
  spec.homepage      = "http://github.com/metix/cgpio"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = %w[ext/cgpio/extconf.rb]

  spec.add_development_dependency "bundler", "~> 1.10"
  spec.add_development_dependency "rake", "~> 10.0"
end
