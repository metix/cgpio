# Cgpio

A simple GPIO Wrapper in Ruby (which uses C to access the SYSFS structures)

```ruby
require 'cgpio'

# switch on a led on port 48
led = Cgpio.new(48)
led.on
```

Tested with Linux-Kernel Version "4.1.6" on
* [Beaglebone Black](http://beagleboard.org/black)

WARN: the gem is not stable yet!

## Features
* set/get value
* set/get direction
* virtual GPIO

## Installation
```
gem install cgpio
```

## Usage
### Example
```ruby
require 'cgpio'

# setup a new port (output is default)
led = Cgpio.new(48)

# setup a new input port
switch = Cgpio.new(66, direction: :in)

# connect led with switch
loop do led.value = switch.value end
```

### Initializing a port
```ruby
# setup a new port (output is default)
led = Cgpio.new(48)

# setup a new input port
switch = Cgpio.new(66, direction: :in)
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

### Get static info about port
```ruby
# get port number
nr = port.nr
```

### Virtual GPIO
When you want to run your program on a hardware which don't have GPIO, you can
use virtual GPIOs.

For this you have to configure the Cgpio before you use it:
```ruby
# put this at the beginning of your program
Cgpio.configure do |config|
    # use virtual gpio instead of real gpio
    config.virtual = true
end
```

#### Value changed event
You can can define a function which will be called when the value of the virtual
GPIO changes:
```ruby
# will be called when value changes
led.value_change do |new, old|
    puts "led change value from #{old} to #{new}"
end
```

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
