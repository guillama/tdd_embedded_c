tdd_embedded_c
=========


Build
=====

```
cd tdd_embedded_c
cmake -S . -B build -DCIBLE=test
cmake --build build/
```

Execution
=========

```
build/test/cppUTests/CircularBuffer/CircularBufferTests
build/test/cppUTests/LightScheduler/LightSchedulerTests

build/test/unityTests/LedDriverTests
build/test/unityTests/FlashTest
```