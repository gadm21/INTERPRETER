#include "common.h"
#include "Instruction.h"
#include "Reader.h"
#include "MIS.h"
#include "clientMIS.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

int main(int argc, char* argv[]) {

	int portnum= atoi(argv[2]);
	char* address= argv[1];
	string filename= argv[3];
	TCPSocket client( address, portnum);

	clientMIS m( filename, client);
	m.Run();
    return 0;
}
