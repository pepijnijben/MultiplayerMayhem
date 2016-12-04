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
	IpAddress ip;
	int port;
	int room_id;
};

struct Room
{
	Room() {};
	int id;
	string name;
	int owner;
	int started;
};

class APIHandler
{
private:
	static APIHandler * instance;
	string myName;
	int me;
	int currentRoom;
	Http http;

	vector<NetPlayer> DeserializePlayers(string message);
	vector<Room> DeserializeRooms(string message);
public:
	APIHandler()
	{
		//http.setHost("http://192.168.99.100:32776/");
		http.setHost("http://docker.local/");
	};
	static APIHandler * GetInstance();

	string GetName() { return myName; }

	void newPlayer(string player, int port);
	void checkInPlayer();
	vector<NetPlayer> getPlayers();
	vector<NetPlayer> getRoomPlayers();
	vector<NetPlayer> getRoomOtherPlayers();
	vector<NetPlayer> getRoomOtherPlayers(vector<NetPlayer> players);

	void createRoom();
	void removeRoom();
	void joinRoom(int roomId);
	vector<Room> getRooms();

	bool IsHost();
};