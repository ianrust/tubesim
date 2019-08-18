import pygame.midi

pygame.midi.init()

device_info = pygame.midi.get_device_info(0)
print('device_info', device_info)

# open a specific midi device
inp = pygame.midi.Input(0)

# run the event loop
while True:
    if inp.poll():
        # no way to find number of messages in queue
        # so we just specify a high max value
        events = inp.read(1000)
        for [[status, data1, data2, data3], timestamp] in events:
            print(status, timestamp)
            print(data1, data2, data2)
            print()

        # wait 10ms - this is arbitrary, but wait(0) still resulted
        # in 100% cpu utilization
        pygame.time.wait(10)

