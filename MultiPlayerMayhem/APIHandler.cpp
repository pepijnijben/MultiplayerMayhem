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

	cout << response.getBody() << endl;
}
