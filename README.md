# Cgpio

A simple GPIO Wrapper in Ruby (which uses C to access the SYSFS structures)

Tested with Beaglebone Black.

WARN: the gem is not stable yet!

## Features
* set/get value
* set direction
## Usage
### Example
```
# create a new port (default is output)
led = Cgpio::Gpio.new(48);

# enable led
led.on
```

### Initializing a port
```
# create a new port (default is output)
led = Cgpio::Gpio.new(48);

# create a new input port
switch = Cgpio::Gpio.new(66, direction: :input)
```

### Set value of port
```
# set value to true
led.value = true
# or
led.on

# set value to false
led.value = false
# or
led.off

```

### Read value of port
```
val = switch.value
val = switch.on?
val = switch.off?
```

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
