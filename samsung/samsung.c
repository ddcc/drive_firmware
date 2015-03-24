#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// Samsung SSD Firmware Deobfuscation Tool
// v0.2 - 2015/02/06
// https://www.github.com/ddcc/drive_firmware
// GNU GPL v2 - see LICENSE.md

uint8_t encode(uint8_t v) {
  return (v & 0x80)
    ? (~(v<<1) & 0xE0) | (v & 0x0F)
    : (v<<1 & 0xE0) | 0x10 | (v & 0x0F);
}

uint8_t decode(uint8_t v) {
  return (v & 0x10)
    ? (v>>1 & 0x70) | (v & 0x0F)
    : (~(v>>1) & 0x70) | 0x80 | (v & 0x0F);
}

int main(int argc, char** argv) {
  FILE *ip = NULL, *op = NULL;

  uint8_t *buf;
  size_t i ,buf_size;
  int enc = (argc >= 4 && !strcmp(argv[3], "-e"));

  int ret = 0;

  if (argc < 3) {
    printf("Usage: %s <input> <output> [-e] \n", argv[0]);
    ret = -1;
    goto end;
  }

  if (!(ip = fopen(argv[1], "rb"))) {
    printf("Error: Cannot open %s!\n", argv[1]);
    ret = -1;
    goto end;
  }

  fseek(ip, 0, SEEK_END);
  buf_size = ftell(ip);

  if (!(buf = malloc(buf_size))) {
    printf("Error: Cannot allocate input buffer of size %zu!\n", buf_size);
    ret = -1;
    goto end_buf;
  }

  rewind(ip);
  if (fread(buf, sizeof(*buf), buf_size / sizeof(*buf), ip) != buf_size / sizeof(*buf)) {
    perror(NULL);
    printf("Error: Cannot read %zu bytes!\n", buf_size);
    ret = -1;
    goto end_buf;
  }

  for (i = 0; i < buf_size; i++) {
    buf[i] = enc ? encode(buf[i]) : decode(buf[i]);
  }

  if (!(op = fopen(argv[2], "wb"))) {
    printf("Error: Cannot open %s!\n", argv[2]);
    ret = -1;
    goto end_buf;
  }

  if (fwrite(buf, sizeof(*buf), buf_size / sizeof(*buf), op) != buf_size / sizeof(*buf)) {
    printf("Error: Cannot write to output file!\n");
    ret = -1;
  }

  fclose(op);

end_buf:
  free(buf);
  fclose(ip);

end:
  return ret;
}
