#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p1[2];
  int p2[2];
  pipe(p1);
  pipe(p2);
  char buf[8]; 
  if (fork() == 0) {
    read(p1[1], buf, 8);
    printf("%d: received ping\n", getpid());
    write(p2[0], buf, 8);
  } else {
    wait(0);
    read(p2[1], buf, 8);
    printf("%d: received pong\n", getpid());
    write(p1[0], buf, 8);
  }
  exit(0);
}
