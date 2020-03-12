#include <unistd.h>
#include <stdio.h>

int main() {
    char input[50];
    while (1)
    {
        printf("Enter your cammand: ");
        scanf("%s",input);

        if (strcmp(input,"quit") == 0) {
            printf("Users wanna quit.\n");
            return 0;
        }

        int pid = fork();
        if (pid == 0) {
            char  *args[] = {input, NULL};
            execvp(input, args);
        } 
        else {
            wait();
        }

    }

    return 0;
}