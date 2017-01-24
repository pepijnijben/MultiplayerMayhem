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
	Settings() : NetSolution(NetworkSolution::Interpolation),
	Latency(0),
	WinningScore(80){ }

public:
	static Settings * getInstance();
	
	NetworkSolution NetSolution;
	int Latency;
	int WinningScore;
};