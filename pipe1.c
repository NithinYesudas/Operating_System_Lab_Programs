#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    int size_pipe[2];//size_pipe[0],size_pipe[1]
    int arr_pipe[2];
    pipe(size_pipe);
    pipe(arr_pipe);
    pid_t pid = fork();
    if(pid ==0){//child process

        close(size_pipe[1]);
        close(arr_pipe[1]);
        int size;
        read(size_pipe[0], &size, sizeof(size));
        int arr[size];
        read(arr_pipe[0], arr, sizeof(arr));
        printf("Numbers received at children");
        for (int i = 0; i < size;i++){
            printf("%d", arr[i]);
        }
    }
    else{
        //parent process
        close(size_pipe[0]);
        close(arr_pipe[0]);
        int size;
        printf("Enter the size of array: ");
        scanf("%d", &size);
        write(size_pipe[1], &size, sizeof(size));
        printf("Enter the numbers from parent");
        int arr[size];
        for (int i = 0; i < size;i++){
            scanf("%d", &arr[i]);

        }
        write(arr_pipe[1], arr, sizeof(arr));
        wait(NULL);
    }

}