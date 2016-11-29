#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

struct NetPlayer
{
	NetPlayer() {};
	string name;
	string ip;
	int port;
	int room_id;
};

class APIHandler
{
private:
	static APIHandler * instance;
	int me;
	Http http;
public:
	APIHandler()
	{
		//http.setHost("http://192.168.99.100:32776/");
		http.setHost("http://docker.local/");
	};
	static APIHandler * GetInstance();

	void newPlayer(string player, int port);
	void checkInPlayer();
	vector<NetPlayer> getPlayers();
};