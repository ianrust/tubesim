# tubesim

# Dependencies

[Emscripten](https://emscripten.org/docs/getting_started/downloads.html) (note that emsdk must be put at ~/)

python3

[platform.io](https://platformio.org/) (optional, required for programming board)


## How to run

```bash
./compile_and_run.sh
```

open your web browser to 0.0.0.0:8000

hooray!

## TODOs

Pipe goal left/right;

Get sound playing in browser so you can actually tell if it's a satisfying pattern

Make sure timing matches in sim (specifically the "tick" variable)

Make sidelines by either expanding Tube to have a special "1-sided" mode or it's own class
    they need to have way different indexing (start at the center) and have the ability for angles

Make sure LEDs have the right r,g,b order
    Make a colormap for each LED type in order to get truer colors

Get index -> spatial location working w/ a common definition with the Tube object since so much of that lives there. In the future this could be a config file?

I'm not that impressed with the performance of the spectrum chip. We should really be able to do an fft, but that is hard.

Nice-to-have, better realism: try adding diffusers, ie cylinders w/ low alpha and blend turned on.