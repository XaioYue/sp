
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2
#define NUM_ITERATIONS 100000

int balance = 500; // 初始帳戶金額
pthread_mutex_t mutex;

void *deposit(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        balance += 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *withdraw(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        balance -= 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    // 創建存款和提款的執行緒
    pthread_create(&threads[0], NULL, deposit, NULL);
    pthread_create(&threads[1], NULL, withdraw, NULL);

    // 等待所有執行緒完成
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 檢查結果
    printf("Final balance: %d\n", balance);
    if (balance != 200500) {
        printf("Error occurred! Final balance: %d\n", balance);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
