#include "um982.hpp"

UM982::UM982(const char* _port): 
  fd(-1) 
  {}

int UM982::close_serial_port(){
  if (fd>0){
    close(fd);
    fd=-1;
    return 1;
  }
  else{
    return 0;
  }
  return 1;
}

int UM982::readgps(){
  if(fd==-1){
    return -1;
  }
  int bytes=::read(fd, &buffer[0], sizeof(buffer)-1);
  if (bytes < 1){
    close(fd);
    fd = -1;
    return -1;
  }
  buffer[bytes]='\0';
  printf("UM982 (%d bytes): %s", bytes, buffer);
  return 0;
}

int UM982::um982_init(){
  if (fd > 0){
    return 0;
  }
  int flags = (O_RDWR | O_NOCTTY | O_NONBLOCK);
  fd=open("/dev/ttyAMA0", flags);
  if (fd < 0){
    fd = -1;
    return 1;
  }
  if (!isatty(fd)){
    close(fd);
    fd = -1;
    return 1;
  }
  struct termios uart_config{};
  tcgetattr(fd, &uart_config);
  uart_config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
  uart_config.c_oflag &= ~ONLCR;
  uart_config.c_cflag |= CS8;
  uart_config.c_cflag &= ~(CSTOPB | PARENB);
  uart_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
  int termios_state = cfsetispeed(&uart_config, BAUD);
  termios_state = cfsetospeed(&uart_config, BAUD);
  termios_state = tcsetattr(fd, TCSANOW, &uart_config);
  if (termios_state < 0) {
    close(fd);
    fd = -1;
    return 1;
  }
  return 0;
}


UM982::~UM982(){
  close_serial_port();
}

