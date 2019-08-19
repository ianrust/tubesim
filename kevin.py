from typing import Tuple
import pygame.midi
import serial

pygame.midi.init()

print('device_count', pygame.midi.get_count())

device_info = pygame.midi.get_device_info(0)
print('device_info', device_info)

# open a specific midi device
inp = pygame.midi.Input(0)

use_serial = False

if use_serial:
    print('opening port')
    ser = serial.Serial('/dev/ttyUSB0')  # open serial port
    print('serial', ser.name)  # check which port was really used


def map_mini_output_to_pattern(status: int, data: Tuple[int, int, int]):
    [key_id, __, __] = data

    if key_id == 0:
        print('fuck')

    if key_id == 1:
        print('shit')


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

