# TaskSys


[![Build Status](https://travis-ci.org/francisfsjiang/TaskSys.svg?branch=master)](https://travis-ci.org/francisfsjiang/TaskSys) 


## Dependencies

- C++ > 11
- Boost{test} > 1.68

## How to Build

Clone this repo and make build dir.
```bash
git clone https://github.com/francisfsjiang/TaskSys.git
cd TaskSys
mkdir build

```

Use cmake to automatically build and find depends.
```bash
cd build
cmake ..
make

```

Now the built libraries are in `lib/`.

Or build with unit test.
```bash
cmake -DBUILD_TEST=on ..
```

Or build with custom Boost dir.
```bash
cmake -DBOOST_ROOT=/path/to/boost/ ..
```

Or build with in release mode.
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
```

## Run unit test
```bash
cd TaskSys/bin
./test

```

## Continues Integration Environment

- Ubuntu 16.04(trusty) GCC-7
- Ubuntu 16.04(trusty) Clang-5
- macOS Xcode-10

Status: [![Build Status](https://travis-ci.org/francisfsjiang/TaskSys.svg?branch=master)](https://travis-ci.org/francisfsjiang/TaskSys) 


## TODO

- Logging support.

- More test cases.

- Check simulator's thread's return value.