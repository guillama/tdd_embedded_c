tdd_embedded_c
=========


Build
=====

```
cd tdd_embedded_c
cmake -S . -B build
cmake --build build/ -t [CircularBufferTests][LightSchedulerTests][LedDriverTests][FlashTest]
```

Execution
=========

```
build/bin/CircularBufferTests
build/bin/LightSchedulerTests

build/bin/LedDriverTests
build/bin/FlashTests
```