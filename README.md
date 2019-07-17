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

Fix the arduino scripts, ie make them actually run

Make sidelines by either expanding Tube to have a special "1-sided" mode or it's own class
    they need to have way different indexing (start at the center) and have the ability for angles

Serial to browser w/ frequency spectrum
    needs integration w/ audio board with filters and such

Get index -> spatial location working w/ a common definition with the Tube object since so much of that lives there. In the future this could be a config file?

Nice-to-have, better realism: try adding diffusers, ie cylinders w/ low alpha and blend turned on.