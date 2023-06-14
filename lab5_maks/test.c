#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>



int main()
{
    int fd;
    char msg[1024] = "9876543210dnbkldfgnflk 945 9456 ";

    fd = open("/dev/sort", O_RDWR);

    if (fd < 0) {
        perror("Failed to open the device...");
        return 1;
    }
    read(fd, msg, strlen(msg) + 1);
    printf("Read from device: %s\n", msg);
    close(fd);
    
}