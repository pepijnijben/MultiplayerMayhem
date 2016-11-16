#pragma once
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Net 
{
private:
	UdpSocket socket;
	int localPort = 8081;

	int remotePort = 8080;
	IpAddress remoteIp = "192.168.1.43";
public:
	Net();
	~Net();
	void Send();
	string Receive();
};