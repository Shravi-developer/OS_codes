#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "b.txt";  
    mode_t new_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

    if (chmod(filename, new_mode) == 0) {
        printf("Permissions changed successfully.\n");
    } else {
        perror("chmod error");
    }

    return 0;
}
