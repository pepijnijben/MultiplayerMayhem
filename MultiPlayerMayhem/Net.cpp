#include "Net.h"
#include "Settings.h"

Net * Net::instance = 0;

Net::Net()
{
	socket.setBlocking(false);
	socket.unbind();

	// Uncommend this to play in the lab with other pc's
	//socket.bind(5228);
	Socket::Status s = socket.send("UDPHolePunching", 100, "178.62.78.172", 54000);
	if (s != Socket::Done)
	{
		cout << "Was unable to send UDPHolePunching message" << endl;
	}
	else
	{
		localPort = socket.getLocalPort();
		cout << "Succesfully binded to port " << socket.getLocalPort() << endl;
	}
}

Net::~Net()
{
	socket.unbind();
}

Net * Net::GetInstance()
{
	if (instance == 0)
	{
		instance = new Net();
	}

	return instance;
}

void Net::Send(string message)
{
	for (auto & remote : remotePlayers)
	{
		Socket::Status s = socket.send(message.c_str(), 100, remote.ip, remote.port);

		if (s != sf::Socket::Done)
		{
			cout << "Was unable to send message to " << remote.ip << ":" << remote.port << endl;
			cout << "Socket status: " << s << endl;
		}

		PackagesSend++;
		BytesSend += message.size();
	}
}

void Net::Send(string message, string name)
{
	for (auto & remote : remotePlayers)
	{
		if (remote.name == name)
		{
			Socket::Status s = socket.send(message.c_str(), 100, remote.ip, remote.port);

			if (s != sf::Socket::Done)
			{
				cout << "Was unable to send message to " << remote.ip << ":" << remote.port << endl;
				cout << "Socket status: " << s << endl;
			}

			PackagesSend++;
			BytesSend += message.size();

			break;
		}
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
			m_messages.push_back(Message(GameTime + (Settings::getInstance()->Latency *0.001), data));
	}

	for (int i = m_messages.size() - 1; i >= 0; i--)
	{
		if (m_messages[i].time <= GameTime)
		{
			messages.push_back(m_messages[i].message);

			PackagesReceived++;
			BytesReceived += messages[i].size();

			m_messages.erase(m_messages.begin() + i);
		}
	}

	return messages;
}
