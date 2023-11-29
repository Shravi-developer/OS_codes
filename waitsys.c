#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
pid_t child_pid;

child_pid=fork();
if(child_pid<0)
{
perror("fork failed");
exit(EXIT_FAILURE);
}
else if(child_pid==0)
{
printf("This is the child process(PID: %d)\n",getpid());
exit(EXIT_SUCCESS);
}
else
{
printf("This is the parent process(PID: %d)\n",getpid());
wait(NULL);

printf("Child process has exited");

}
return 0;
}
