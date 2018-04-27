#include "BNO080.h"
#include "PracticalSocket.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

const unsigned int BUF_SIZE = 1024;

void HandleConnection(TCPSocket *sock);

int main(){
	BNO080 tt(0,0,0);
        tt.begin();
        tt.enableGameRotationVector(10);

        try{
            TCPServerSocket servSock(9000);
            for(;;){
                HandleConnection(servSock.accept(), tt);
            }
        } catch(SocketException e){
            cerr << e.what() << endl;
            exit(1);
        }
	return 0;
}

void HandleConnection(TCPSocket *sock, BNO080 &sensor1){
    cout << "Handling client ";
    try {
        cout << sock->getForeignAddress() << ":";
    } catch (SocketException e) {
        cerr << "Unable to get foreign address" << endl;
    }
    try {
        cout << sock->getForeignPort();
    } catch (SocketException e) {
        cerr << "Unable to get foreign port" << endl;
    }
    cout << endl;

    // Send received string and receive again until the end of transmission
    char echoBuffer[RCVBUFSIZE];
    int recvMsgSize;
    while ((recvMsgSize = sock->recv(echoBuffer, 1)) > 0) { // Zero means
        // end of transmission
        if(strcmp(echoBuffer, "Q") == 0){
            //get the data
            float quatX = tt.getQuatI();
            float quatY = tt.getQuatJ();
            float quatZ = tt.getQuatK();
            float quatW = tt.getQuatReal();
            ostringstream os;
            os << quatW << ',' << quatX << ',' << quatY << ',' << quatZ;
            string tempS = os.str();
            unsigned char len = tempS.length();
            sock->send(&len, 1);
            sock->send(tempS.c_str(), len);
        }
    }
    delete sock;
}
