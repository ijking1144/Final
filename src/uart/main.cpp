#include "um982.hpp"
#include <unistd.h>

int main(){
  UM982 gps("/dev/ttyAMA0");
  if (gps.um982_init()!=0){
    return 1;
  }
  for (int i=0;i<10;i++){
    gps.readgps();
    sleep(1);
  }
  return 0;
}
