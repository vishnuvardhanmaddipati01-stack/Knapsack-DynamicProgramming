# 0/1 Knapsack Using Dynamic Programming in C

Finds the maximum total value that fits in a bag of a given capacity. Each item can be selected at most once.

## Compile and run
```bash
gcc src/knapsack.c -o knapsack
./knapsack
```
On Windows, run `knapsack.exe`.

## Complexity
- Time: `O(nW)`.
- Space: `O(nW)`.
Here `n` is the number of items and `W` is the capacity. This is pseudo-polynomial time because it depends on the numeric capacity.
