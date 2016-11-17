#include "Net.h"

bool Net::IsPlayer1 = false;

Net::Net()
{
	if (socket.bind(localPort) != Socket::Done)
	{
		cout << "Unable to bind socket to port " << localPort << endl;
	}
	else
	{
		cout << "Sucessfully binded to port " << localPort << endl;
	}

	socket.setBlocking(false);
}

Net::~Net()
{
}

void Net::Send()
{
	char data[] = "This is a test message";
	Socket::Status s = socket.send(data, 100, remoteIp, remotePort);

	if (s != sf::Socket::Done)
	{
		cout << "Was unable to send message: " << data << endl;
		cout << "Socket status: " << s << endl;
	}
	else
	{
		cout << "Send Message: " << data << endl;
	}
}

string Net::Receive()
{
	IpAddress sender;
	unsigned short port;

	char data[100];
	size_t received;

	if (socket.receive(data, 100, received, sender, port) != Socket::NotReady)
	{	
		cout << "Received data package with " << received << " bytes." << endl;

		if (received > 0)
			return data;
	}

	return string();
}
