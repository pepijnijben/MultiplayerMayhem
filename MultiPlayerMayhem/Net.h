#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "APIHandler.h"

using namespace std;
using namespace sf;

struct Message
{
	float time;
	string message;

	Message(float t, string m) { time = t; message = m; };
};

class Net 
{
private:
	static Net * instance;

	UdpSocket socket;
	int localPort = 8081;

	vector<NetPlayer> remotePlayers;
	vector<Message> m_messages;
public:
	Net();
	~Net();

	int PackagesSend = 0;
	int PackagesReceived = 0;
	int BytesSend = 0;
	int BytesReceived = 0;

	float GameTime = 0;

	static Net * GetInstance();

	void Send(string message);
	// Only send message to a certain player
	void Send(string message, string name);
	vector<string> Receive();

	int GetLocalPort() { return localPort; }
	void SetRemotePlayers(vector<NetPlayer> rp) { remotePlayers = rp; }
};