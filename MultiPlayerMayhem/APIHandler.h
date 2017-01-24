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

	string prefix;

	vector<NetPlayer> DeserializePlayers(string message);
	vector<Room> DeserializeRooms(string message);
public:
	static bool HOST;
	APIHandler()
	{
		//http.setHost("http://pepijn.pw/");
		//prefix = "/multiplayer";
		//http.setHost("http://docker.local/");
		http.setHost("http://lobby.pepijn.pw/");
		prefix = "";
	};
	static APIHandler * GetInstance();

	string GetName() { return myName; }

	void newPlayer(string player, int port);
	void checkInPlayer();
	vector<NetPlayer> getPlayers();
	vector<NetPlayer> getRoomPlayers();
	vector<NetPlayer> getRoomOtherPlayers();
	vector<NetPlayer> getRoomOtherPlayers(vector<NetPlayer> players);
	bool leaveRoom();

	bool createRoom();
	void removeRoom();
	bool joinRoom(int roomId);
	vector<Room> getRooms();

	bool IsHost();
};