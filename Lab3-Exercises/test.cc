#include <cstdint>
#include <inttypes.h>
#include <stdio.h>

int main() {
  uint8_t data = 0b100000  ;
  printf("%" PRId8 "\n", data);
}