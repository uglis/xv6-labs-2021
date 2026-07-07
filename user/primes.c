#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void filter(int fd) {
  int prime;
  int ret = read(fd, &prime, 4);
  if (ret <= 0)
    exit(0);
  int p[2];
  pipe(p);
  printf("prime %d\n", prime);

  if (fork() == 0) {
    close(p[1]);
    filter(p[0]);
    exit(0);
  }

  close(p[0]);

  while (1) {
    int n;
    int m = read(fd, &n, 4);
    if (m <= 0) break;
    if (n % prime != 0) {
      write(p[1], &n, 4);
    }
  }

  close(p[1]);
  close(fd);
  wait(0);
  exit(0);
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  int nums[35] = {2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                  14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                  26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  write(p[1], &nums, 35 * 4);

  if (fork() == 0) {
    close(p[1]);
    filter(p[0]);
    exit(0);
  }

  close(p[0]);
  close(p[1]);
  wait(0);
  exit(0);
}
