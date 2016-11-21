#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

class APIHandler
{
private:
	static APIHandler * instance;
	Http http;
public:
	APIHandler()
	{
		//http.setHost("http://192.168.99.100:32776/");
		http.setHost("http://docker.local/");
	};
	static APIHandler * GetInstance();

	void newPlayer(string player, int port);
};