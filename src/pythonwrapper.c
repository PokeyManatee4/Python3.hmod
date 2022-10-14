#include <stdio.h>
#include <stdlib.h>

int main() {
   system("echo "Python 3 Wrapper 1.0 (S)NES Mini edition"")
   // system("cat /dev/tty0 > /dev/fb0")

   while(True == True) {
      system("cat /dev/urandom >> /dev/fb0");
      system("dd if=/dev/zero count=1000 bs=1024 > /dev/fb0");
   }
}
