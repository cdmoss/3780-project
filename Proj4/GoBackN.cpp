#include "GoBackN.h"

GoBackNSender::GoBackNSender(unsigned int _seqAmt, unsigned int _winSize) {
    seqAmt = _seqAmt;
    winSize = _winSize;
}

int GoBackNSender::sendSeq() {
    // we are maxed out and waiting for acks (or window size is 0), no seq should be sent
    if (numUnacknowledgedSeq == winSize) {
        return -1;
    }

    // the entire segment has been sent, no seq should be sent
    if (numSeqSent == seqAmt) {
        return -2;    
    }

    // seq to send is the number of seqs sent mod window size
    unsigned int seqToSend = numSeqSent % winSize;
    numSeqSent++;

    return seqToSend;
}

