source ~/emsdk/emsdk_env.sh
emcc --bind include/patterns.cpp -o js/patterns.js

python3 -m http.server
