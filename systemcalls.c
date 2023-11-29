#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>  

int main()
{
    int fd;
    char buffer[80];
    static char message[] = "This is a system calls program";

    fd = open("myfile.txt", O_RDWR | O_CREAT, 0644); 
    if (fd != -1)
    {
        

        write(fd, message, sizeof(message) - 1);  

        lseek(fd, 0, SEEK_SET);  

        read(fd, buffer, sizeof(message) - 1);
        buffer[sizeof(message) - 1] = '\0'; 

        printf("%s - written to the file \n", buffer);

        close(fd);
    }
    else
    {
        printf("Error opening myfile.txt\n");
    }

    return 0;
}
