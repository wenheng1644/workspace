#include "apue.h"

int main(void)
{
    printf("hello world from process ID %ld\n",(long)getpid());
    printf("current userID: %d and groupID: %d\n",getuid(),getgid());

    pause();
    return 0;
}