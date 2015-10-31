#include "Raig.h" // API for developers

extern "C" {
	#include "../libsocket/Sockets.h"
}

using namespace raig;

// RaigImpl class declaration
class Raig::RaigImpl
{
public:
	void connect(char* ipAddress);
	void sendData(char* dataString);
	void sendData(int value);
	void sendData(Packet* packet);
	Packet* readData();
	void update();

	// Private members and functions
	void cleanUp();
	bool isComplete;
	bool alive;

	int iSocketFileDescriptor;
	char* strServerIPAddress;
	struct Address sAddress;
	Packet readPacket;
};

/*
 *  Raig class implementation
 */
Raig::Raig() : m_Impl(new RaigImpl())
{
	m_Impl->isComplete = false;
	m_Impl->alive = true;
}

Raig::~Raig()
{
	m_Impl->cleanUp();
}

void Raig::connect(char* ipAddress)
{
	m_Impl->connect(ipAddress);
}

void Raig::sendData(char* dataString)
{
	m_Impl->sendData(dataString);
}

void Raig::sendData(int value)
{
	m_Impl->sendData(value);
}

void Raig::sendData(Packet* packet)
{
	m_Impl->sendData(packet);
}

Packet* Raig::readData()
{
	return (Packet*) m_Impl->readData();
}

void Raig::update()
{
	m_Impl->update();
}

/*
 * RaigImpl implementation
 */
void Raig::RaigImpl::connect(char* ipAddress)
{
	std::cout << "Raig::RaigImpl::connect()" << std::endl;

	strServerIPAddress = ipAddress;

	iSocketFileDescriptor = Socket(AF_INET, SOCK_STREAM, 0);

	Address(AF_INET, (struct Address*) &sAddress, strServerIPAddress, HANGMAN_TCP_PORT);

	Connect(iSocketFileDescriptor, (struct sockaddr*) &sAddress.m_sAddress, sizeof(sAddress.m_sAddress));

}

void Raig::RaigImpl::sendData(char* dataString)
{
	std::cout << "Raig::RaigImpl::sendData() : " << dataString << std::endl;
	//multiplexStdinFileDescriptor(stdin, iSocketFileDescriptor);

	//close(iSocketFileDescriptor);
}

void Raig::RaigImpl::sendData(int value)
{
	std::cout << "Raig::RaigImpl::sendData() : " << value << std::endl;
}

void Raig::RaigImpl::sendData(Packet* packet)
{
	Write(iSocketFileDescriptor, packet, sizeof(Packet));
	printf("Packet sent ok (%d, %d)\n", packet->x, packet->y);
}

Packet* Raig::RaigImpl::readData()
{
	Read(iSocketFileDescriptor, &readPacket, sizeof(Packet));
	printf("Packet read ok (%d, %d)\n", readPacket.x, readPacket.y);
	return &readPacket;
}

void Raig::RaigImpl::update()
{
	std::cout << "Raig::RaigImpl::update()" << std::endl;
}

void Raig::RaigImpl::cleanUp()
{
	std::cout << "Raig::RaigImpl::cleanUp()" << std::endl;
	close(iSocketFileDescriptor);
}
