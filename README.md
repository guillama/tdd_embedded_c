# Embedded C: Test-Driven Development Exercise

This repository contains my solution to an exercise from the book *Test-Driven Development for Embedded C* by James W. Grenning. The exercise focuses on applying **Test-Driven Development (TDD)** techniques to develop robust and reliable embedded systems software.

## Overview

The exercise demonstrates the application of TDD principles to develop and test embedded software incrementally. The primary focus is on writing unit tests for embedded C code and ensuring clean, maintainable, and testable designs suitable for resource-constrained environments.

## Key Features

- Implementation of embedded C functionality with a TDD approach.
- Utilization of mock objects to isolate hardware dependencies.
- A systematic approach to writing and refactoring tests and production code.

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
