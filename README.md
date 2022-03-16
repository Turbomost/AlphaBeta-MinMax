# AlphaBeta-MinMax
## Turbomošt
### Running


```bash
make
```

### Guide

```bash
./run [terminals left to right, top to bottom]{40}
```
Run with 2021/2022 structure and custom terminals. Order is from top to bottom, then from left to right - your input should start with **./run inf 0 -inf 0**.

```bash
./run help
./run custom help
```
Print help or help for custom sturctures.
#### Custom structure:

```bash
./run custom [structure] end [terminals] end
```
Custom structure is number of branches from left to right, top to bottom.
Custom terminals order is from left to right, top to bottom.

### Example
![alt text](https://i.postimg.cc/NfjD8xzS/izu.png)

```bash
./run inf 0 -inf 0 8 -4 6 10 -8 6 -12 3 -10 0 inf -5 -6 -6 -6 3 4 0 5 -12 -2 -11 0 -12 4 5 -5 -4 2 -8 5 8 11 2 3 6
```
or
```bash
./run custom 4 2 1 2 1 2 2 2 2 2 1 2 1 2 2 2 2 -1 2 1 2 2 -1 3 -1 1 3 3 2 3 3 1 4 3 3 -1 2 2 1 2 end inf 0 -inf 0 8 -4 6 10 -8 6 -12 3 -10 0 inf -5 -6 -6 -6 3 4 0 5 -12 -2 -11 0 -12 4 5 -5 -4 2 -8 5 8 11 2 3 6 end
```
