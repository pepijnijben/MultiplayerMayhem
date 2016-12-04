#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "APIHandler.h"

using namespace std;
using namespace sf;

class Net 
{
private:
	static Net * instance;

	UdpSocket socket;
	int localPort = 8081;

	vector<NetPlayer> remotePlayers;
public:
	Net();
	~Net();

	static Net * GetInstance();

	void Send(string message);
	vector<string> Receive();

	int GetLocalPort() { return localPort; }
	void SetRemotePlayers(vector<NetPlayer> rp) { remotePlayers = rp; }
};