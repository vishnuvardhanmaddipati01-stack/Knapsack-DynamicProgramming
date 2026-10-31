#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, capacity;
    printf("Enter number of items (1-100): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("Invalid number of items.\n");
        return 1;
    }
    printf("Enter bag capacity (0-100000): ");
    if (scanf("%d", &capacity) != 1 || capacity < 0 || capacity > 100000) {
        printf("Invalid capacity.\n");
        return 1;
    }

    int *weight = malloc((size_t)n * sizeof(int));
    int *value = malloc((size_t)n * sizeof(int));
    if (!weight || !value) {
        printf("Memory allocation failed.\n");
        free(weight); free(value);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter weight and value for item %d: ", i + 1);
        if (scanf("%d %d", &weight[i], &value[i]) != 2 ||
            weight[i] <= 0 || value[i] < 0) {
            printf("Weights must be positive and values non-negative.\n");
            free(weight); free(value);
            return 1;
        }
    }

    size_t cols = (size_t)capacity + 1;
    int *dp = calloc(((size_t)n + 1) * cols, sizeof(int));
    if (!dp) {
        printf("Memory allocation failed.\n");
        free(weight); free(value);
        return 1;
    }
    #define DP(i, w) dp[(size_t)(i) * cols + (size_t)(w)]

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            DP(i, w) = DP(i - 1, w);
            if (weight[i - 1] <= w) {
                int candidate = DP(i - 1, w - weight[i - 1]) + value[i - 1];
                if (candidate > DP(i, w)) DP(i, w) = candidate;
            }
        }
    }

    printf("\nMaximum value: %d\n", DP(n, capacity));
    printf("Selected items (1-based item numbers): ");
    int w = capacity, selected = 0;
    for (int i = n; i >= 1; i--) {
        if (DP(i, w) != DP(i - 1, w)) {
            printf("%s%d", selected ? ", " : "", i);
            selected = 1;
            w -= weight[i - 1];
        }
    }
    if (!selected) printf("none");
    printf("\n");

    free(dp); free(weight); free(value);
    return 0;
}
