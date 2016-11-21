#include "Net.h"

bool Net::IsPlayer1 = false;

Net::Net()
{
	socket.setBlocking(false);
}

Net::~Net()
{
	socket.unbind();
}

void Net::Init()
{
	socket.unbind();

	if (Net::IsPlayer1)
	{
		localPort = p1Port;
		remotePort = p2Port;
	}
	else
	{
		localPort = p2Port;
		remotePort = p1Port;
	}

	if (socket.bind(localPort) != Socket::Done)
	{
		cout << "Unable to bind socket to port " << localPort << endl;
	}
	else
	{
		cout << "Sucessfully binded to port " << localPort << endl;
	}
}

void Net::Send(string message)
{
	Socket::Status s = socket.send(message.c_str(), 100, remoteIp, remotePort);

	if (s != sf::Socket::Done)
	{
		cout << "Was unable to send message: " << message << endl;
		cout << "Socket status: " << s << endl;
	}
	else
	{
		//cout << "Send Message: " << message << endl;
	}
}

vector<string> Net::Receive()
{
	vector<string> messages;

	IpAddress sender;
	unsigned short port;

	char data[100];
	size_t received;

	while (socket.receive(data, 100, received, sender, port) != Socket::NotReady)
	{
		if (received > 0)
			messages.push_back(data);
	}

	/*if (socket.receive(data, 100, received, sender, port) != Socket::NotReady)
	{	
		if (received > 0)
			return data;
	}*/

	return messages;
}
