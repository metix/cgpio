# Cgpio

A simple GPIO Wrapper in Ruby (which uses C to access the SYSFS structures)

```ruby
require 'cgpio'

# switch on a led on port 48
led = Cgpio::Gpio.new(48)
led.on
```

Tested only with Beaglebone Black.

WARN: the gem is not stable yet!

## Features
* set/get value
* set/get direction

## Installation
```
gem install cgpio
```

## Usage
### Example
```ruby
require 'cgpio'

# setup a new port (output is default)
led = Cgpio::Gpio.new(48)

# setup a new input port
switch = Cgpio::Gpio.new(66, direction: :in)

# connect led with switch
loop do led.value = switch.value end
```

### Initializing a port
```ruby
# setup a new port (output is default)
led = Cgpio::Gpio.new(48)

# setup a new input port
switch = Cgpio::Gpio.new(66, direction: :in)
```

Note: The initialization will export the port (/sys/class/gpio/export) if it is
not exported already. But when the GC (Garbage Collector) deletes this object,
the port will not be unexported.

### Set direction of port
```ruby
# port as output
led.direction = :out

# port as input
switch.direction = :in
```

### Get direction of port
```ruby
# returns :in or :out
dir = switch.direction
```

### Set value of port
```ruby
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
```ruby
val = switch.value
val = switch.on?
val = switch.off?
```

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
