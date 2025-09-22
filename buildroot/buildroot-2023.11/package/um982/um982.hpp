#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define BAUD B9600
#define BUFFER_SIZE 1024

class UM982
{
public:
    UM982(const char* _port = "/dev/ttyAMA0");
    ~UM982();
    int readgps();
    int write();
    int um982_init();

private:
    int fd;
    int close_serial_port();
    char buffer[BUFFER_SIZE];
};
