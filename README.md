# KV Store
A Redis-like key-value store built from scratch in C++.

## Features (building up)
- [ ] TCP server
- [ ] GET/SET/DELETE commands
- [ ] LRU eviction
- [ ] Persistence to disk
- [ ] Benchmarks vs Redis

## Build
mkdir build && cd build
cmake ..
make
./kvserver