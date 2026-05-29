# KV Store
A Redis-like key-value store built from scratch in C++.

## Features
- [x] TCP server on port 6379
- [x] GET/SET/DELETE commands
- [ ] LRU eviction
- [ ] Persistence to disk
- [ ] Benchmarks vs Redis

## Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
./Debug/kvserver.exe
```

## Usage
```
Coming soon: SET key value / GET key / DELETE key
```
