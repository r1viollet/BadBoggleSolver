# Bad boggle solver

Toy program to generate a workload to test Datadog apps.
It also solves boggles.

## Retrieving english words

This could use with a script. For now I hard coded them in the repo.

[English words](https://github.com/dwyl/english-words.git)

## Build

Build commands

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make -j 4
```
