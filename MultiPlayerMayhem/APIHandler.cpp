#include "APIHandler.h"

APIHandler * APIHandler::instance = 0;
bool APIHandler::HOST = false;

vector<NetPlayer> APIHandler::DeserializePlayers(string message)
{
	size_t pos = 0;
	string delimiter = ";";
	vector<string> token;
	vector<NetPlayer> players;

	while ((pos = message.find(delimiter)) != string::npos) {
		token.push_back(message.substr(0, pos));
		message.erase(0, pos + delimiter.length());
	}

	for (int i = 0; i < token.size(); i += 4)
	{
		NetPlayer np;
		np.name = token[i];
		np.room_id = stoi(token[i + 1]);
		np.ip = token[i + 2];
		np.port = stoi(token[i + 3]);

		players.push_back(np);
	}

	return players;
}

vector<Room> APIHandler::DeserializeRooms(string message)
{
	vector<Room> rooms;
	size_t pos = 0;
	string delimiter = ";";
	vector<string> token;

	while ((pos = message.find(delimiter)) != string::npos) {
		token.push_back(message.substr(0, pos));
		message.erase(0, pos + delimiter.length());
	}

	for (int i = 0; i < token.size(); i += 4)
	{
		Room r;
		r.id = stoi(token[i]);
		r.name = token[i + 1];
		r.owner = stoi(token[i + 2]);
		r.started = stoi(token[i + 3]);

		rooms.push_back(r);
	}

	return rooms;
}

APIHandler * APIHandler::GetInstance()
{
	if (instance == 0)
	{
		instance = new APIHandler();
	}

	return instance;
}

void APIHandler::newPlayer(string player, int port)
{
	ostringstream ss;

	ss << "name=" << player << "&port=" << port;

	Http::Request request(prefix + "/newPlayer.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);

	try
	{
		myName = player;
		me = stoi(response.getBody());
		cout << "Successfully logged in with id " << me << endl;
	}
	catch (exception e)
	{
		cout << "An error occured when logging into the lobby server: " << response.getStatus() << endl;
	}
}

void APIHandler::checkInPlayer()
{
	ostringstream ss;

	ss << "id=" << me;

	Http::Request request(prefix + "/checkInPlayer.php", Http::Request::Post);
	request.setBody(ss.str());
	
	Http::Response response = http.sendRequest(request);
}

vector<NetPlayer> APIHandler::getPlayers()
{
	Http::Request request(prefix + "/getPlayers.php", Http::Request::Get);

	Http::Response response = http.sendRequest(request);

	string message = response.getBody();

	return DeserializePlayers(message);
}

vector<NetPlayer> APIHandler::getRoomPlayers()
{
	ostringstream ss;

	ss << "roomId=" << currentRoom;

	Http::Request request(prefix + "/getRoomPlayers.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);

	string message = response.getBody();
	return DeserializePlayers(message);
}

vector<NetPlayer> APIHandler::getRoomOtherPlayers()
{
	return getRoomOtherPlayers(getRoomPlayers());
}

vector<NetPlayer> APIHandler::getRoomOtherPlayers(vector<NetPlayer> players)
{
	vector<NetPlayer> newPlayers;
	for (auto & player : players)
	{
		if (player.name != myName)
		{
			newPlayers.push_back(player);
		}
	}

	return newPlayers;
}

bool APIHandler::leaveRoom()
{
	ostringstream ss;

	ss << "id=" << me;

	Http::Request request(prefix + "/leaveRoom.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);

	if (response.getStatus() != 200)
	{
		return false;
	}

	currentRoom = -1;
	return true;
}

bool APIHandler::createRoom()
{
	ostringstream ss;

	ss << "id=" << me;

	Http::Request request(prefix + "/createRoom.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);

	try
	{
		cout << "Successfully created room " << response.getBody() << endl;
		return joinRoom(stoi(response.getBody()));
	}
	catch (exception e)
	{
		cout << "An error occured when creating a new room: " << response.getBody() << endl;
		return false;
	}
}

void APIHandler::removeRoom()
{
	ostringstream ss;

	ss << "roomId=" << currentRoom;

	Http::Request request(prefix + "/removeRoom.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);
	currentRoom = -1;
}

bool APIHandler::joinRoom(int roomId)
{
	if (currentRoom == roomId)
	{
		return true;
	}

	ostringstream ss;

	ss << "id=" << me << "&roomId=" << roomId;

	Http::Request request(prefix + "/joinRoom.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);
	
	try
	{
		currentRoom = stoi(response.getBody());
		cout << "Successfully joined room " << currentRoom << endl;
	}
	catch (exception e)
	{
		cout << "An error occured when joining a room: " << response.getBody() << endl;
		return false;
	}

	return true;
}

vector<Room> APIHandler::getRooms()
{
	Http::Request request(prefix + "/getRooms.php", Http::Request::Get);

	Http::Response response = http.sendRequest(request);

	string message = response.getBody();

	return DeserializeRooms(message);
}

bool APIHandler::IsHost()
{
	/*auto rooms = getRooms();

	if(rooms.size() <= 0)
	{
		cout << "An error occured when trying to retrieve the rooms information" << endl;
	}

	for(auto& obj : rooms)
	{
		if (obj.id == currentRoom)
		{
			if (obj.owner == me)
			{
				return true;
			}

			break;
		}
	}

	return false;*/
	return HOST;
}
