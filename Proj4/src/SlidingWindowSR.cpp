#include "../include/SlidingWindowSR.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

SlidingWindowSR::SlidingWindowSR() {
  winSize = 3;
  setMaxSeqNum(7);
}

SlidingWindowSR::SlidingWindowSR(uint _winSize, uint _maxSeqNum) {
  winSize = _winSize;
  setMaxSeqNum(_maxSeqNum);
}

void SlidingWindowSR::setWinSize(uint size) { winSize = size; }

uint SlidingWindowSR::getWinSize() { return winSize; }

void SlidingWindowSR::setMaxSeqNum(uint size) {
  maxSeqNum = size;

  // clear stateVec lists
  stateVec.clear();
  stateVec.resize(size + 1);

  // refill using new size
  for (int i = 0; i <= maxSeqNum; i++) {
    stateVec[i] = 0;
  }
}

uint SlidingWindowSR::getMaxSeqNum() { return maxSeqNum; }

void SlidingWindowSR::printStateVec() {
  for (int i : stateVec) {
    cout << i << " ";
  }
  cout << endl;
}

uint SlidingWindowSR::send() {
  // window is maxed: return -1
  if (!canSend()) {
    cout << "window size is maxed" << endl;
    return -1;
  }

  // window isn't maxed: find next seq available in window
  int start = lastAck + 1;

  // first, clean the window to make sure we don't run into any left over acks and mess up the search below
  for (int i = start; i <= start + winSize; i++) {
    int correctedSeq = i % (maxSeqNum + 1);
    if (stateVec[i] == 2) {
      stateVec[i] = 0;
    }
  }
  
  for (int i = start; i <= start + winSize; i++) {
    // account for looping around by modding current seq with maxSeqNum + 1
    int correctedSeq = i % (maxSeqNum + 1);

    // we found an unsent seq, mark as sent and increment nrUnacked
    if (stateVec[correctedSeq] == 0) {
      stateVec[correctedSeq] = 1;

      // seq to send is the last seq num, we need to reset everything in
      // statevec up to current window
      if (correctedSeq == maxSeqNum) {
        for (int i = 0; i <= maxSeqNum - winSize; i++) {
          stateVec[i] = 0;
        }
      }

      cout << "sent: " << correctedSeq << endl;
      return correctedSeq;
    }
  }

  // something went wrong, return -1
  cout << "something went wrong" << endl;
  return -1;
}

void SlidingWindowSR::receiveAck(uint ackedSeq) {
  // if ackedSeq != lastAck and maps to an sent, unacked seq, this is a positive
  // ack, update the statevec accordingly
  cout << "recieved ack for: " << ackedSeq << endl;
  cout << "stateVec before recieving ack: ";
  printStateVec();

  // if ack is for an unsent seq, its an error
  if (stateVec[ackedSeq] == 0) {
    cout << "faulty ack, seq hasn't been sent yet" << endl;
    return;
  }

  // if ack is for an already acked seq, its a duplicate
  if (stateVec[ackedSeq] == 2) {
    cout << "duplicate ack received" << endl;
    return;
  }

  if (ackedSeq != lastAck && stateVec[ackedSeq] == 1) {
    // see if we've looped around by checking if ackSeq maps to an unacked seq
    // in the window which is less than lastAck
    if ((int)ackedSeq < lastAck) {
      // mark appropriate seqences acked: lastAck + 1 to maxSeqNum, and 0 to
      // ackedSeq
      for (int i = lastAck + 1; i <= maxSeqNum; i++) {
        stateVec[i] = 2;
      }
      for (int i = 0; i <= ackedSeq; i++) {
        stateVec[i] = 2;
      }
    }
    // otherwise, ack all seqs in window that are less than unacked seq
    else {
      int start = lastAck + 1;
      for (int i = start; i <= start + winSize; i++) {
        if (ackedSeq >= i) {
          stateVec[i] = 2;
        }
      }

      // also check to see the ackedSeq is the last seq num. if it is, reset
      // stateVec
      if (ackedSeq == maxSeqNum) {
        for (int i = 0; i <= maxSeqNum; i++) {
          stateVec[i] = 0;
        }
      }
    }

    cout << "stateVec after recieving ack: ";
    printStateVec();

    lastAck = ackedSeq;
  }

  // printStateVec();
  // otherwise there is nothing to do
}

bool SlidingWindowSR::canSend() { return getNrUnacked() < winSize; }

uint SlidingWindowSR::getNrUnacked() {
  uint count = 0;
  for (uint i : stateVec) {
    if (i == 1) {
      count++;
    }
  }

  return count;
}
