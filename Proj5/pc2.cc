#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <string>

// provide hostname and port value as command line arguments
// Mess up with these values and the socket call will likely fail
// argv[0] is the executable name
int main(int argc, char *argv[]) {
  int sock, rval;
  struct addrinfo hints, *results, *ptr;

  // quick check if we preovide the right arguments
  if (argc != 2) {
    std::cout << "Usage " << argv[0] << "destination_port" << std::endl;
    return 1; // terminate
  }

  // if we obtain the data from getaddrinfo, we might as well use it to open the socket

  // first, we prepare hints by clearing all of its fields

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;  // we ask for both IPv4 and IPv6
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  if ((rval = getaddrinfo(NULL, argv[1], &hints, &results)) != 0) { // error
    std::cerr << "Error getting the destination address: " << gai_strerror(rval) << std::endl;
    return 2;
  }

  // loop through the results from the linked list
  for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
    if ((sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) != -1) {
      break;  // socket successful, no need to search further
    }
  }

  if (ptr == NULL) {
    std::cerr << "Failed to open socket" << std::endl;
    return 3;
  }
  // we now need to bind the socket
  if (bind(sock, ptr->ai_addr, ptr->ai_addrlen) == -1) {
  std::cerr << " Cannot bind the socket " << std::endl;
  return 4;
  }

 int byte_count ;
  socklen_t fromlen ;
  struct sockaddr_storage fromaddr;
  fromlen = sizeof(fromaddr);
  char buf [512];
  byte_count = recvfrom (sock, buf, sizeof(buf) -1, 0, (sockaddr*) (&fromaddr), &fromlen);

  buf [byte_count]=0;
  std::cout << buf << std::endl;

  fromlen = sizeof(fromaddr);

  if(sendto(sock, buf, sizeof(buf) -1, 0, (sockaddr*) (&fromaddr), fromlen) == -1) {
    std::cout << "failed to send\n";
  }


  close(sock);
}
