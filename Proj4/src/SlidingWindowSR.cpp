#include "../include/SlidingWindowSR.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

SlidingWindowSR::SlidingWindowSR() {
    winSize = 3;
    setMaxSeqNum(7);
}

SlidingWindowSR::SlidingWindowSR(uint _winSize, uint _maxSeqNum) {
    winSize = _winSize;
    setMaxSeqNum(_maxSeqNum);
}

void SlidingWindowSR::setWinSize(uint size) {
    winSize = size;
}

uint SlidingWindowSR::getWinSize() {
    return winSize;
}

void SlidingWindowSR::setMaxSeqNum(uint size) {
    maxSeqNum = size;

    // clear stateVec lists
    stateVec.clear();
    stateVec.resize(size);

    // refill using new size
    for (int i = 0; i < maxSeqNum; i++) {
        stateVec[i] = 0;
    }
}

uint SlidingWindowSR::getMaxSeqNum() {
    return maxSeqNum;
}

uint SlidingWindowSR::getNrUnacked() {
    return nrUnacked;
}

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
    for (int i = start; i <= start + winSize; i++) {
        // account for looping around by modding current seq with maxSeqNum + 1
        int correctedSeq = i % (maxSeqNum + 1);

        // we found an unsent seq, mark as sent and increment nrUnacked
        if (stateVec[correctedSeq] == 0) {
            stateVec[correctedSeq] = 1;
            nrUnacked++;

            // seq to send is the last seq num, we need to reset everything in statevec up to current window
            if (correctedSeq == maxSeqNum) {
                for (int i = 0; i <= maxSeqNum - winSize; i++) {
                    stateVec[i] = 0;
                }
            }

            return correctedSeq;
        }
    }

    // something went wrong, return -1
    return -1;
}

void SlidingWindowSR::ack(uint ackedSeq) {
    // if ackedSeq != lastAck and maps to an sent, unacked seq, this is a positive ack, update the statevec accordingly
    if (ackedSeq != lastAck && stateVec[ackedSeq] == 1) {
        // see if we've looped around by checking if ackSeq maps to an unacked seq in the window which is less than lastAck
        if ((int)ackedSeq < lastAck) {
            // nrackedseqs is now equal to the end window index - ackedSeq
            int endWindowIndex = (lastAck + winSize) % (maxSeqNum + 1);
            nrUnacked = endWindowIndex - ackedSeq;

            // mark appropriate seqences acked: lastAck + 1 to maxSeqNum, and 0 to ackedSeq
            for (int i = lastAck + 1; i <= maxSeqNum; i++) {
                stateVec[i] = 2;
            }
            for (int i = 0 + 1; i <= ackedSeq; i++) {
                stateVec[i] = 2;
            }
        }  
        // otherwise, ack all seqs in window that are less than unacked seq
        else {
            int start = lastAck + 1;
            for (int i = start; i <= start + winSize; i++) {
                if (ackedSeq >= i) {
                    nrUnacked--;
                }
            }
        }

        lastAck = ackedSeq;
    }

    if (stateVec[ackedSeq] == 0) {
        cout << "faulty ack, seq hasn't been sent yet" << endl;
    }
    if (stateVec[ackedSeq] == 2) {
        cout << "duplicate ack received" << endl;
    }

    printStateVec();

    // otherwise there is nothing to do
}

bool SlidingWindowSR::canSend() {
    return nrUnacked < winSize;
}
