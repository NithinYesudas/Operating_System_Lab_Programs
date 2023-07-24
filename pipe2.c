#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int isPrime(int num)
{
    for (int i = 2; i < num / 2; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int size_pipe[2];
    int arr_pipe[2];
    int size_pipe2[2];
    int arr_pipe2[2];
    pipe(size_pipe2);
    pipe(arr_pipe2);
    pipe(arr_pipe);
    pipe(size_pipe);
    pid_t pid = fork();
    if (pid == 0)
    {
        close(size_pipe[1]);
        close(arr_pipe[1]);
        close(arr_pipe2[0]);
        close(size_pipe2[0]);

        int size;
        read(size_pipe[0], &size, sizeof(size));
        int arr[size];
        read(arr_pipe[0], arr, sizeof(arr));
        int prime[size];
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (isPrime(arr[i]))
            {
                prime[count] = arr[i];
                count++;
            }
        }
        write(size_pipe2[1], &count, sizeof(count));
        write(arr_pipe2[1], prime, sizeof(prime));
    }
    else
    {
        close(size_pipe[0]);
        close(arr_pipe[0]);
        close(arr_pipe2[1]);
        close(size_pipe2[1]);

        int size;
        printf("Enter the size of the array to the parent: ");
        scanf("%d", &size);

        write(size_pipe[1], &size, sizeof(size));

        int arr[size];
        printf("Enter the numbers: ");
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &arr[i]);
        }
        write(arr_pipe[1], arr, sizeof(arr));
        read(size_pipe2[0], &size, sizeof(size));
        int arr2[size];
        read(arr_pipe2[0], arr2, sizeof(arr2));
        printf("Prime numbers: ");
        for (int i = 0; i < size; i++)
        {
            printf("%d\t", arr2[i]);
        }
        wait(NULL);
    }
}