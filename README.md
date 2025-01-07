# TDD for Embedded C - Practice Examples

Implementation of examples from James W. Grenning's "Test-Driven Development for Embedded C" book. This repository contains practical exercises and implementations following the TDD methodology presented in the book.

Build
=====

```
cd tdd_embedded_c
git submodule update --init --recursive

cmake -S . -B build
cmake --build build/ -t all
```

Execution
=========

```
build/bin/CircularBufferTests
build/bin/LightSchedulerTests
build/bin/LedDriverTests
build/bin/FlashTests
```
