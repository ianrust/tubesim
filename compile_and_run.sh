source ~/emsdk/emsdk_env.sh
emcc --bind include/js_patterns.cpp -o js/patterns.js -s "BINARYEN_TRAP_MODE='clamp'"

if [[ $1 = "upload" ]]; then
    platformio run -e $2 --target upload 
else
    python3 -m http.server
fi