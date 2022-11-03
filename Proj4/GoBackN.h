#ifndef GOBACKN_HEADER
#define GOBACKN_HEADER

class GoBackNSender {
private:
    // number of sequence numbers
    unsigned int seqAmt;
    unsigned int winSize;
    unsigned int numUnacknowledgedSeq = 0;
    unsigned int numSeqSent = 0;

public:
    // n: number of sequence numbers that need to be sent
    GoBackNSender(unsigned int _seqAmt, unsigned int _winSize);
    
    // returns new sequence number if the sliding window is able to advance or -1 if sliding window can't advance
    int sendSeq();

    // mocks the even in which the sender recieves an acknowledgement
    int recieveAck(unsigned int seqNum);

    // sets the sliding window max size
    void setWinSize(unsigned int n);
};

class GoBackNReciever {
private:
    // number of sequence numbers
    unsigned int seqAmt;
    unsigned int winSize;
    unsigned int lastAckedSeq = 0;

public:
    // n: number of sequence numbers that need to be sent
    GoBackN(unsigned int _seqAmt, unsigned int _winSize);
    
    // send the next sequence number available in the sliding window
    int sendSeq();

    // mocks the even in which the sender recieves an acknowledgement
    int recieveAck(unsigned int seqNum);

    // sets the sliding window max size
    void setWinSize(unsigned int n);

    // mocks an acknowledgement from the reciever for the given sequence number
    void acknowledge(unsigned int s);
};



#endif