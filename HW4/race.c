
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2
#define NUM_ITERATIONS 1000000

int balance = 500; // 初始帳戶金額

void *deposit(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        balance += 1;
    }
    return NULL;
}

void *withdraw(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        balance -= 1;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // 創建存款和提款的執行緒
    pthread_create(&threads[0], NULL, deposit, NULL);
    pthread_create(&threads[1], NULL, withdraw, NULL);

    // 等待所有執行緒完成
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 檢查結果
    printf("Final balance: %d\n", balance);
    if (balance != 500) {
        printf("Race condition occurred! Final balance: %d\n", balance);
    }

    return 0;
}
