import serial
import struct
import json
import sys

ser = serial.Serial('/dev/ttyACM0', 115200)
ser.reset_input_buffer()

music_started = False
freqs_recording = []
fn = sys.argv[1]

if __name__ == "__main__":
    while 1:
        response = ser.readline()
        if (len(response) < 15):
            continue
        freqs = list(struct.unpack('hhhhhhh', response[:14]))
        print(sum(freqs))
        if (sum(freqs) > 100 and not music_started):
            music_started = True
        if (sum(freqs) < -100 and music_started):
            break
            music_started = False

        if (music_started):
            freqs_recording.append(freqs)

print("Done recording, writing")
json = "var song = " + json.dumps(freqs_recording)
with open(fn, 'w') as f:
    f.write(json)