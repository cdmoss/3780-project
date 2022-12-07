#ifndef __SIMPLEHEADER_H
#define __SIMPLEHEADER_H

#include <cstdint>
// maximum size for the payload
#define DATA_SZ 1024
// size of header
#define HEADER_SZ 4


struct simplepacket {
  uint8_t header[HEADER_SZ];
  char data[DATA_SZ];  // payload
};

// class to be tested. Implements the demo header structure below.
// exports routines to get and set the header parameters val (integer between 0 and 3) and payload_length (16 bit unsigned integer)
//  0 1  2 7   8 15  16   32
// +---+-----+-----+--------+
// |Val| unu | unu |payload |
// |   | sed | sed |length  |
// +---+-----+-----+--------+

class SimpleHeader {
private:
  struct simplepacket packet;

  // start index of the payload length field (private)
  const int PL=2;

  // start index of val header field
  const int VL=0;

public:
  // default constructor initializes the header to zero.
  SimpleHeader();

  // sets the value of the payload length
  // val = length; if val > DATA_SZ, the value set is DATA_SZ
  // 16 bit value
  void setLength(unsigned int val);

  // returns the length
  unsigned int getLength() const;


  // sets the value field of Type in the header.
  // val must be less than 3
  void setType(unsigned int val);

  // returns the Type field of the header
  // 2 bit value
  unsigned int getType() const;

  // sets the TR field of the header.
  // 1 bit value
  // val must be less than 2
  void setTR(unsigned int val);

  // returns the TR field of the header
  // 1 bit value
  unsigned int getTR() const;

  // sets the Window field of the header.
  // 5 bit value
  // val must be less than 32
  void setWindow(unsigned int val);

  // returns the Window field of the header
  // 5 bit value
  unsigned int getWindow() const;


  // sets the sequence number value
  // 8 bit value
  // value must be less than 256
  void setSeqNum(unsigned int val);

  // returns sequence number value
  // 8 bit value
  unsigned int getSeqNum();

  // returns the size of the packet, including headers and data
  // to be used with recvfrom() or sendto()
  unsigned int totalPacketSize() const {
    return getLength() + HEADER_SZ;
  }

  // returns pointer to the structure holding the thePacket, including the headers
  // To be used with recvfrom or sendto
  void * thePacket() {
    return &packet;
  }

  void * thePayload() {
    return packet.data;
  }
};

#endif
