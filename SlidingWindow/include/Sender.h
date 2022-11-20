#ifndef SLIDINGWINDOW_SENDER_H
#define SLIDINGWINDOW_SENDER_H

#include "Receiver.h"
#include "SlidingWindow.h"
#include <set>
#include <vector>

/**
 * This class provides a sender for a selective repeat protocol communciation
 * channel.
 */
class Sender {
private:
  unsigned int numOfFrames{255};
  SlidingWindow *slidingWindow;
  int lastSeqNumAck = -1;

public:
  Sender();
  Sender(unsigned int numOfFrames, SlidingWindow *slidingWindow);
  ~Sender();

  unsigned int getNumOfFrames() const;

  void setNumOfFrames(unsigned int numOfFrames);
  SlidingWindow *getSlidingWindow();
  unsigned send();
  unsigned sendMulti(unsigned amt);
  //   void receiveAck(std::pair<unsigned int, std::set<unsigned int> *>
  //   acknowledgement); we can return back to this if we decide to do something
  //   with the out of order set
  unsigned receiveAck(unsigned ackedSeq);
  bool windowMatchesSet(std::vector<unsigned>);
  void resetSlidingWindow(unsigned winSize);
};
#endif // SLIDINGWINDOW_SENDER_H
