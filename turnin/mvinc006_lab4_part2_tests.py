# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).

tests = [ 
    
    { # Test 1: Does both button press, check for init to 0x07.
    'description': 'PINA: 0x03 => PORTC: 0x07',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 5 },
               ],
    'expected': [('PORTC',0x07)],
    },

    { # Test 2: Does no button press, check for PORTC to 0x00.
    'description': 'PINA: 0x00 => PORTC: 0x00',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 5 },
               ],
    'expected': [('PORTC',0x00)],
    },
    
    { # Test 3: Does button 1 press, 5 times, check for PORTC to 0x05.
    'description': 'PINA: 0x01 => PORTC: 0x05',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5 },
               ],
    'expected': [('PORTC',0x05)],
    },
    
    { # Test 4: Does button 2 press, 3 times, check for PORTC to 0x02.
    'description': 'PINA: 0x02 => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 3 },
               ],
    'expected': [('PORTC',0x02)],
    },

    { # Test 5: Does button 2 press, 5 times, check for PORTC to 0x00.
    'description': 'PINA: 0x02 => PORTC: 0x00',
    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 5 },
               ],
    'expected': [('PORTC',0x00)],
    },

    { # Test 6: Does button 1 press, 15 times, check for PORTC to 0x09.
    'description': 'PINA: 0x01 => PORTC: 0x09',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 15 },
               ],
    'expected': [('PORTC',0x09)],
    },

    { # Test 7: Does button 1 and 2 press, 15 times, check for PORTC to 0x09.
    'description': 'PINA: 0x03 => PORTC: 0x09',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 15 },
               ],
    'expected': [('PORTC',0x09)],
    },
 
    { # Test 8: Does no press, 15 times, check for PORTC to 0x00.
    'description': 'PINA: 0x00 => PORTC: 0x00',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 15 },
               ],
    'expected': [('PORTC',0x00)],
    },

    ]

watch = ['PINA', 'main::state', 'main::flag','PORTC']
