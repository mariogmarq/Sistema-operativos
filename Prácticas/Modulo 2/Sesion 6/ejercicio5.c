#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 3)
    return 1;
  int fd1, fd2;
  char *map1, *map2;
  struct stat sb;
  // Abrimos fd1 y fd2
  fd1 = open(argv[1], O_RDONLY);
  if (fd1 == -1)
    return 2;
  fd2 = open(argv[2], O_CREAT | O_RDWR | O_EXCL);
  fstat(fd1, &sb);

  map1 = (char *)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd1, 0);

  ftruncate(fd2, sb.st_size);

  map2 = (char *)mmap(0, sb.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);

  close(fd1);
  close(fd2);
  memcpy(map2, map1, sb.st_size);
}
