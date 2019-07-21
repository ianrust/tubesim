source:
	source /home/calvin/dev/src/github.com/emscripten-core/emsdk/emsdk_env.sh

js:
	emcc --bind include/js_patterns.cpp -o js/patterns.js

website:
	python3 -m http.server

upload:
	platformio run -e goals --target upload

.PHONY: js upload