js:
	cd images && python3 img_to_c.py && cd .. && . ~/emsdk/emsdk_env.sh && emcc --bind include/js_patterns.cpp -o js/patterns.js  -s "BINARYEN_TRAP_MODE='clamp'"

website:
	python3 -m http.server

upload:
	platformio run -e goals --target upload

.PHONY: js upload