#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *msg = "hello";

    fd = open("/dev/crypto_chardev", O_RDWR);

    if (fd < 0) {
        perror("Failed to open the device...");
        return 1;
    }
    write(fd, msg, strlen(msg));

    char buf[512];
    read(fd, buf, sizeof(buf));
    printf("Read from device: %s\n", buf);

    close(fd);

    return 0;
}