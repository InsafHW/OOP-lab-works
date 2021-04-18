#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MIN_CHANNEL = 1;
const int MAX_CHANNEL = 99;

class TV
{
public:
	bool TurnOn();
	bool TurnOff();
	bool SelectChannel(int channel);
	bool SelectChannel(string channelName);
	string Info() const;
	bool SelectPreviousChannel();
	bool IsTurnedOn() const;
	int GetChannel() const;
	bool SetChannelName(int channel, string channelName);
	bool DeleteChannelName(string channelName);
	string GetChannelName(int channel);
	int GetChannelByName(string channelName);
private:
	bool m_isTurned = false;
	int m_currentChannel = 0;
	vector<int> m_history;
	map<int, string> m_channelsNumberToName;
	map<string, int> m_channelsNameToNumber;
	bool EraseExtraBlanks(string& str) const;
};

