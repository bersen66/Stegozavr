# Stegozavr.

* Implementation of steganographic API using ```C++```
  and [userver-framework](https://userver.tech/).

## Installation

To build service from sources you have to install conan and cmake.

```
$ pip install conan==1.55.0
$ pip install cmake
```

### DB-setup

* You have to specify DB-connection before running
  service. [See how](configs/README.md).

### HOW TO RUN SERVICE:

* ```make build-release``` - to build service in release mode.
* ```make run-release``` - to run build and run service in release mode.
* ```make run-tests``` - to build project and run unit-tests

### Generate documentation:

* ```$ doxygen``` - this folder.