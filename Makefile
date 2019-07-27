images:
	cd images && python3 img_to_c.py && cd ..

js:
	. ~/emsdk/emsdk_env.sh && emcc --bind include/js_patterns.cpp -o js/patterns.js  -s "BINARYEN_TRAP_MODE='clamp'"

server:
	python3 -m http.server

website: images js server

c:
	platformio run -e goals

upload:
	platformio run -e goals --target upload

uploadfps:
	platformio run -e fps --target upload

sleep:
	sleep 3

monitor:
	platformio device monitor


fps: images uploadfps sleep monitor

flash: images upload

all: images js c

.PHONY: images js server website upload flash all c
