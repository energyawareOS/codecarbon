# libcodecarbon

Enhancements to [CodeCarbon](https://github.com/mlco2/codecarbon) for C Programs and System-wide Carbon Tracking

## Overview

This project extends the functionality of the open-source tool CodeCarbon, originally designed for Python-based energy consumption tracking, to support C programs and system-level carbon monitoring. It introduces two major components:

- **libcarbon**: A C-compatible shared library that enables integration of CodeCarbon-like functionality into C-based projects.
- **carboneye**: A standalone daemon that tracks energy usage and carbon emissions across the entire system.

## Features

- C API support via `libcarbon`
- Real-time system-wide energy and CO₂ tracking via `carboneye`
- Compatible with Linux-based environments
- Designed to work alongside the original Python-based CodeCarbon framework
- Suppresses verbose output from CodeCarbon by default. To enable verbose messages, set the `CODECARBON_LOG_LEVEL` environment variable to an appropriate level recognized by Python's `logging` module (e.g., `INFO`, `DEBUG`). If the variable is not set, logging is suppressed by default using the `CRITICAL` level.

## Getting Started

To see how `libcarbon` can be integrated into a C program, refer to the sample code provided in `examples/test_libcodecarbon.c`.

## Python Dependencies

To enable integration with CodeCarbon, the following Python modules must be installed:

```
pandas
rapidfuzz
py-cpuinfo
psutil
pynvml
requests
arrow
prometheus_client
```

These modules should be installed in the Python environment used by the CodeCarbon backend.

## Build Instructions

This project uses CMake for build configuration.

```bash
mkdir build
cd build
cmake ..
make
```

This will build both `libcarbon` and `carboneye`.
