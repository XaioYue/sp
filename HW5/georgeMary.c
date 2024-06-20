#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>

void print_george() {    // 每隔一秒鐘印出一次 George 的函數
    while (1) {    
        printf("George\n");    
        sleep(1);    
    }
}

void print_mary() {     // 每隔2秒鐘印出一次 Mary 的函數
    while (1) {    
        printf("Mary\n");    
        sleep(2);    
    }    
}

int main() { 
    pid_t pid1, pid2;

    pid1 = fork(); // 創建第一個子進程
    if (pid1 == 0) { // 在第一個子進程中執行
        print_george();
        exit(0); // 子進程結束
    } else if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    pid2 = fork(); // 創建第二個子進程
    if (pid2 == 0) { // 在第二個子進程中執行
        print_mary();
        exit(0); // 子進程結束
    } else if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

 
    while (1) {     // 主程式每隔一秒鐘
        printf("----------------\n");    // 就印出分隔行
        sleep(1);     // 停止一秒鐘
    }

   
    return 0;    
}
