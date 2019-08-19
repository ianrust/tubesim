import struct
from typing import Tuple
import pygame.midi
import serial

pygame.midi.init()

print('device_count', pygame.midi.get_count())

device_id = 3

device_info = pygame.midi.get_device_info(device_id)
print('device_info', device_info)

# open a specific midi device
inp = pygame.midi.Input(device_id)

use_serial = True

if use_serial:
    print('opening port')
    ser = serial.Serial('/dev/ttyACM0')  # open serial port
    print('serial', ser.name)  # check which port was really used

red = 0
green = 0
blue = 0

def map_mini_output_to_pattern(status: int, data: Tuple[int, int, int]):
    [key_id, knob_value, __] = data

    pattern = 'd'
    reset_ticks = 0

    # When we click a button, we want to update the patten
    if status == 192:
        reset_ticks = 1
        if key_id == 0:
            pattern = 's'

        if key_id == 1:
            pattern = '0'

    # When we turn a knob, we want to update rgb
    if status == 176:
        reset_ticks = 0
        if key_id == 1:
            red = knob_value
        if key_id == 2:
            green = knob_value
        if key_id == 3:
            blue = knob_value

    bytes_to_send = struct.pack('BBBBBBB', 254, pattern, reset_ticks, red, green, blue, 255)
    ser.write(bytes_to_send)

# run the event loop
while True:
    if inp.poll():
        # no way to find number of messages in queue
        # so we just specify a high max value
        events = inp.read(1000)
        for [[status, data1, data2, data3], timestamp] in events:
            print(status, timestamp)
            print(data1, data2, data2)

            map_mini_output_to_pattern(status, (data1, data2, data3))

            # wait 10ms - this is arbitrary, but wait(0) still resulted
            # in 100% cpu utilization
            pygame.time.wait(10)

