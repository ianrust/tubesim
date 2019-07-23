# tubesim

# Dependencies

- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) (note that emsdk must be put at ~/)
- python3
- [platform.io](https://platformio.org/) (optional, required for programming board)

# How to Run

## Javascript
`pip install image` 

[platform.io](https://platformio.org/) (optional, required for programming board)


The js simulation is cross-compiled using emscripten to wasm. You can run it using
a python webserver using the following commands.

Before running, you'll need to source the emsdk env variables:

```
source $(HOME_PATH)/emscripten-core/emsdk/emsdk_env.sh
```

```
$ make js // compile the javascript
$ make website // run the webserver, navigate to localhost:8000
```

## Board

```
$ make upload // this will sync with the board
```

# TODOs

- [ ] Make sidelines by either expanding Tube to have a special "1-sided" mode or it's own class
    they need to have way different indexing (start at the center) and have the ability for angles

- [ ] Get index -> spatial location working w/ a common definition with the Tube object since so much of that lives there. In the future this could be a config file?

- [ ] Make animations smoother. We have the frame rate we just need to

- [ ] Make addressing match wiring plan (2 goal posts on each ethernet port)

- [ ] Get sound playing in browser so you can actually tell if it's a satisfying pattern

- [ ] Make sure timing matches in sim (specifically the "tick" variable)

- [ ] I'm not that impressed with the performance of the spectrum chip. We should really be able to do an fft, but that is hard.

- [ ] Nice-to-have, better realism: try adding diffusers, ie cylinders w/ low alpha and blend turned on.

- [x] HOTTEST FIRE - Make sure the arduino doesn't crash
    -currently happens after about an hour

- [x] Test images on real tube - 6 or 12 strips? ANSWER - 12

- [x] Make a colormap for each LED type in order to get truer colors - FIXED w/ gamma correction
