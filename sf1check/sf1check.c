#include <stdlib.h>
#include <stdio.h>

void usage(char* self) {
  printf("Usage: %s [path/to/STARA.COM]\nExitcode: 0 consistent save\n          1 inconsistent save\n          2 error\n", self);
}

void main(int argc, char** argv) {
  FILE *fh;
  char buf;
  if(argc == 1) {
    usage("SF1CHECK");
    exit(0);
  }
  fh = fopen(argv[1], "rb");
  if(fh == NULL) {
    fprintf(stderr, "Error opening file %s for read\n", argv[1]);
    exit(2);
  }
  if(fseek(fh, 4088, SEEK_SET)) {
    fprintf(stderr, "Error seeking file\n");
    exit(2);
  }
  if(fread(&buf, 1, 1, fh) != 1) {
    fprintf(stderr, "Error reading file\n");
    exit(2);
  }
  fclose(fh);
  switch (buf) {
  case '\x01':
    // saved
    exit(0);
  case '\x00':
    // inconsistent
    exit(1);
  default:
    fprintf(stderr, "Unexpected flag %d found\n", buf);
    exit(2);
  }
}
