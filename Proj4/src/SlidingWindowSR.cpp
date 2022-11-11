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

uint SlidingWindowSR::send() {
    cout << "sending" << endl;
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
        cout << "corrected index from " << i << " to " << correctedSeq << endl;
        if (stateVec[correctedSeq] == 0) {
            stateVec[correctedSeq] = 1;
            nrUnacked++;
            cout << "nr unacked updated to " << nrUnacked << endl;

            // seq to send is the last seq num, reset statevec
            if (correctedSeq == maxSeqNum) {
                for (int i = 0; i < maxSeqNum; i++) {
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
    // if ackedSeq != lastAck and maps to an unacked seq, this is a positive ack, update the statevec accordingly
    if (ackedSeq != lastAck && stateVec[ackedSeq] < 2) {
        // see if we've looped around by checking if ackSeq maps to an unacked seq in the window which is less than lastAck
        if ((int)ackedSeq < lastAck) {

            // nrackedseqs is now equal to the end window index - ackedSeq
            int endWindowIndex = (lastAck + winSize) % (maxSeqNum + 1);
            nrUnacked = endWindowIndex - ackedSeq;
        }  
        // otherwise, ack all seqs in window that are less than unacked seq
        else {
            int start = lastAck + 1;
            for (int i = start; i <= start + winSize; i++) {
                if (ackedSeq >= i) {
                    nrUnacked--;
                    cout << "nr unacked updated to " << nrUnacked << endl;
                }
            }
        }

        lastAck = ackedSeq;
    }

    

    // otherwise there is nothing to do
}

bool SlidingWindowSR::canSend() {
    return nrUnacked < winSize;
}

// // SRSender::SRSender(unsigned int _winSize, unsigned int _maxSeqNum) {
// //     winSize = _winSize;
// //     maxSeqNum = _maxSeqNum;
// // }

// // unsigned int SRSender::send() {
// //     // return -1 if window is already maxed
// //     if (unAckedSeqs.size() == winSize) {
// //         return -1;
// //     }

// //     // calculate seqnum to send
// //     lastSent = (lastSent + 1) % maxSeqNum;

// //     unAckedSeqs.push_back(lastSent);    
// //     sort(unAckedSeqs.begin(), unAckedSeqs.end());

// //     return lastSent;
// // }

// // void SRSender::receiveAck(unsigned int ackedSeq) {
// //     /* if ackedSeq is higher than last ack: the receiver has received all seqs in order 
// //     between lastAck and ackSeq, so lastAck is set to ackedSeq and all the intermediate seqs are removed from the unacked list */
// //     if (ackedSeq >= lastAck + 1) {
// //         lastAck = ackedSeq;

// //         for (int i = unAckedSeqs.size() - 1; i >=0; i--) {
// //             // prune anything <= than ackedSeq
// //             if (unAckedSeqs[i] == ackedSeq) {
// //                 // multiple seqs can be removed
// //                 if (i > 0) 
// //                     unAckedSeqs.erase(unAckedSeqs.begin(), unAckedSeqs.begin() + i);
                
// //                 // only removing first entry
// //                 else    
// //                     unAckedSeqs.erase(unAckedSeqs.begin());

// //                 return;
// //             }
// //         }
// //     }
    
//     /* 
//     the other cases would be:
//     - the out of order case - ackedSeq is the same as lastAck: this means the receiver received an out of order frame. so we do nothing 
//     - ackedSeq is less than lastAck - this is just an old ack and can be ignored as well 
//     */
    
// }

// uintvec SRSender::getUnackedSeqs() {
//     return unAckedSeqs;
// }

// SRReceiver::SRReceiver(unsigned int _winSize) {
//     _winSize = winSize;
// }

// SRReceiver::SRReceiver(unsigned int _winSize, int _lastAck) {
//     winSize = _winSize;
//     lastAck = _lastAck;
// } 

// SRReceiver::SRReceiver(unsigned int _winSize, uintvec initList) {
//     winSize = _winSize;
//     outOfOrderSeqList = initList;
// } 

// SRReceiver::SRReceiver(unsigned int _winSize, int _lastAck, uintvec initList) {
//     winSize = _winSize;
//     lastAck = _lastAck;
//     outOfOrderSeqList = initList;
// } 

// unsigned int SRReceiver::receive(unsigned int sentSeq) {
//     // special case for first transmission so modulo doesnt break things 
//     if (lastAck == -1) {
//         lastAck++;
//         return lastAck
//     }

//     // an out of order int is received, check if its in the out of order buffer already, return lastAck
//     if (sentSeq != (lastAck % winSize) + 1) {
//         for (unsigned int i: outOfOrderSeqList) {
//             // its already in the buffer, return last ack
//             if (sentSeq == i) {
//                 return lastAck;
//             }
//         }

//         // it wasn't in the buffer, add it, sort the list ascending, then return last ack
//         outOfOrderSeqList.push_back(sentSeq);
//         sort(outOfOrderSeqList.begin(), outOfOrderSeqList.end());

//         return lastAck;
//     }

//     // an in order seq has been received. re-assign lastAck to sentSeq, discern which buffered out of order seqs are now in order, copy over out of order seqs to a new vector and exclude the in order seqs 
//     lastAck = sentSeq;

//     for (unsigned int i = 0; i < outOfOrderSeqList.size(); i++) {
//         if (outOfOrderSeqList[i] == lastAck + 1) {
//             // current element is now in order regarding new lastAck. assign it as lastAck.
//             lastAck = outOfOrderSeqList[i];
//         }
//         else {
//             /* 
//             current element is out of order regarding new lastAck. 
//             since list is sorted by ascending, we can assume the rest of the elements are also out of order, so the vector slice from current index to the end is the new out of order buffer.
//             save new list and return new lastAck
//             */
//             outOfOrderSeqList = uintvec(outOfOrderSeqList.begin() + i, outOfOrderSeqList.end());
//             return lastAck;
//         }
//     }

//     // if we got here, there are no more out of order seqs, so clear the list and return new lastAck
//     outOfOrderSeqList.clear();
//     return lastAck;
// }

// uintvec SRReceiver::getOutOfOrderSeqs() {
//     return outOfOrderSeqList;