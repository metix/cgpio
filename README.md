# Cgpio

A simple GPIO Wrapper in Ruby (which uses C to access the SYSFS structures)

Tested with Beaglebone Black.

## Usage
```
# create a new output port
led = Cgpio::Gpio.new(48);

# set pin direction
led.direction = :out

# led on
led.value = true
```

## Features
* set/get value
* set direction

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
