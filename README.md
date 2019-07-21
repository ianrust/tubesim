# tubesim

# Dependencies

[Emscripten](https://emscripten.org/docs/getting_started/downloads.html) (note that emsdk must be put at ~/)

python3

`pip install image` 

[platform.io](https://platformio.org/) (optional, required for programming board)


## How to run

```bash
./compile_and_run.sh
```

open your web browser to 0.0.0.0:8000

hooray!

## TODOs

HOTTEST FIRE - Make sure the arduino doesn't crash
    -currently happens after about an hour

Test images on real tube - 6 or 12 strips?

Get sound playing in browser so you can actually tell if it's a satisfying pattern

Make sure timing matches in sim (specifically the "tick" variable)

Make sidelines by either expanding Tube to have a special "1-sided" mode or it's own class
    they need to have way different indexing (start at the center) and have the ability for angles

Make sure LEDs have the right r,g,b order (do at end when everything is bought)
    Make a colormap for each LED type in order to get truer colors

Get index -> spatial location working w/ a common definition with the Tube object since so much of that lives there. In the future this could be a config file?
    - should wait til I know there are two controllers. If the leds for the lines are groups of 100 not 300 it might be better to just have 1 controller. if we increase the number of LEDs on the poles then we probably still need 2 controllers for the number of LED addresses.

I'm not that impressed with the performance of the spectrum chip. We should really be able to do an fft, but that is hard.

Nice-to-have, better realism: try adding diffusers, ie cylinders w/ low alpha and blend turned on.
