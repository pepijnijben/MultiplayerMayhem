#pragma once

enum NetworkSolution
{
	ClientPredictionExtrapolation,
	Interpolation
};

class Settings
{
private:
	static Settings * instance;
	Settings() : NetSolution(NetworkSolution::ClientPredictionExtrapolation),
	Latency(0),
	WinningScore(60){ }

public:
	static Settings * getInstance();
	
	NetworkSolution NetSolution;
	int Latency;
	int WinningScore;
};