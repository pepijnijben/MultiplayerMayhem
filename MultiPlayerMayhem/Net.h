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

	int p1Port = 8081;
	int p2Port = 8082;
	int remotePort = 8080;
	IpAddress remoteIp = "127.0.0.1";
public:
	Net();
	~Net();
	void Init();
	void Send(string message);
	string Receive();

	// Temp value
	static bool IsPlayer1;
};