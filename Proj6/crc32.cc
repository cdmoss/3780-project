#include <iostream>
#include <zlib.h>

using namespace std;

int main() {
  unsigned long crc;
  string s;

	std::cout << "Please type a string (one line) to compute its CRC32" << std::endl;

	std::getline(std::cin, s);

  crc=crc32(0L, NULL, 0);
  crc = crc32(crc, reinterpret_cast<const Bytef*>(s.c_str()), s.size());

  cout << "The crc32 value for: " << s << " is " << hex << crc << endl;

  return 0;
}
