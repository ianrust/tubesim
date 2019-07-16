source ~/emsdk/emsdk_env.sh
emcc --bind include/patterns.cpp -o js/patterns.js

if [[ $1 = "upload" ]]; then
    platformio run --target upload
else
    python3 -m http.server
fi