#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int checkPalindrome(char str[]){
    int length = strlen(str);
    for (int i = 0; i < length/2;i++){
        if(str[i]!= str[length -i -1]){
            return 0;
        }

    }
    return 1;
}
int main()
{

    int arr_pipe[2];
    int palindrome[2];

    pipe(palindrome);
    pipe(arr_pipe);

    pid_t pid = fork();
    if (pid == 0)
    {
        close(arr_pipe[1]);
        close(palindrome[0]);
        
        char str[100];
        read(arr_pipe[0], str, sizeof(str));
        int isPalindrome = checkPalindrome(str);
        write(palindrome[1], &isPalindrome, sizeof(isPalindrome));
    }
    else
    {

        close(arr_pipe[0]);
        close(palindrome[1]);

        char str[100];
        int isPalindrome;
        printf("Enter the string to check palindrome: ");
        scanf("%s", str);
        write(arr_pipe[1], str, sizeof(str));
        read(palindrome[0], &isPalindrome, sizeof(isPalindrome));
        if(isPalindrome){
            printf("The inputed string is Palindrome");
        }
        else{
            printf("The inputted string is Not Palindrome");
        }
        wait(NULL);
    }
}