#include "APIHandler.h"

APIHandler * APIHandler::instance = 0;

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

	Http::Request request("/newPlayer.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);

	try
	{
		me = stoi(response.getBody());
		cout << "Successfully logged in with id " << me << endl;
	}
	catch (exception e)
	{
		cout << "An error occured when logging into the lobby server: " << response.getBody() << endl;
	}
}

void APIHandler::checkInPlayer()
{
	ostringstream ss;

	ss << "id=" << me;

	Http::Request request("/checkInPlayer.php", Http::Request::Post);
	request.setBody(ss.str());

	Http::Response response = http.sendRequest(request);
}

vector<NetPlayer> APIHandler::getPlayers()
{
	Http::Request request("/getPlayers.php", Http::Request::Get);

	Http::Response response = http.sendRequest(request);

	string message = response.getBody();

	size_t pos = 0;
	string delimiter = ";";
	vector<string> token;
	vector<NetPlayer> players;

	while ((pos = message.find(delimiter)) != string::npos) {
		token.push_back(message.substr(0, pos));
		message.erase(0, pos + delimiter.length());
	}

	for(int i = 0; i < token.size(); i += 4)
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