js:
	. ~/emsdk/emsdk_env.sh && emcc --bind include/js_patterns.cpp -o js/patterns.js

website:
	python3 -m http.server

upload:
	platformio run -e goals --target upload

.PHONY: js upload