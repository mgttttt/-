#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *msg = "10707 hello";

    // Открытие файла устройства
    fd = open("/dev/pid_data", O_RDWR);

    if (fd < 0) {
        perror("Failed to open the device...");
        return 1;
    }

    // Запись в устройство
    write(fd, msg, strlen(msg));

    // Чтение из устройства
    char buf[1024] = "10707";
    read(fd, buf, sizeof(buf));
    printf("Read from device: %s\n", buf);

    // Закрытие файла устройства
    close(fd);

    return 0;
}