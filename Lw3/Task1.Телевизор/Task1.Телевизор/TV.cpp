#include "TV.h"
#include <iostream>

bool TV::TurnOn()
{
	if (m_isTurned)
	{
		return false;
	}

	m_isTurned = true;
	if (m_history.empty())
	{
		m_currentChannel = 1;
		m_history.push_back(1);
	}
	else
	{
		m_currentChannel = m_history.back();
	}
	return true;

}

bool TV::TurnOff()
{
	if (!m_isTurned)
	{
		return false;
	}

	m_isTurned = false;
	m_currentChannel = 0;
	return true;
}

bool TV::SelectChannel(int channel)
{
	if (!m_isTurned || channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		return false;
	}

	m_history.push_back(channel);
	m_currentChannel = channel;
	return true;
}

bool TV::SelectChannel(string channelName)
{
	if (!m_isTurned || m_channelsNameToNumber.find(channelName) == m_channelsNameToNumber.end())
	{
		return false;
	}

	SelectChannel(m_channelsNameToNumber[channelName]);
	return true;
}

string TV::Info() const
{
	string info = "Состояние: ";
	info += m_isTurned ? "включен\n" : "выключен\n";
	info += "Номер канала: " + to_string(m_currentChannel) + "\n";

	for (auto iter = m_channelsNumberToName.begin(); iter != m_channelsNumberToName.end(); iter++)
	{
		if (iter != m_channelsNumberToName.begin())
		{
			info += "\n";
		}
		info += to_string(iter->first) + " - " + iter->second;
	}

	return info;
}

bool TV::SelectPreviousChannel()
{
	if (!m_isTurned || m_history.size() <= 1)
	{
		return false;
	}

	m_currentChannel = m_history[m_history.size() - 2];
	m_history.pop_back();
	return true;
}

bool TV::IsTurnedOn() const
{
	return m_isTurned;
}

int TV::GetChannel() const
{
	return m_currentChannel;
}

bool TV::SetChannelName(int channel, string channelName)
{
	bool isOK = EraseExtraBlanks(channelName);
	if (!m_isTurned || !isOK || channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		return false;
	}

	auto isChannelNumberDefined = m_channelsNumberToName.find(channel) != m_channelsNumberToName.end(); // 1, "первый"
	auto isChannelNameDefined = m_channelsNameToNumber.find(channelName) != m_channelsNameToNumber.end(); // "первый", 1

	if (isChannelNumberDefined && isChannelNameDefined)
	{
		int prevChannelNumber = m_channelsNameToNumber[channelName]; // номер канала, у которого данное название
		string prevChannelName = m_channelsNumberToName[channel]; // название канала, у которого данный номер

		m_channelsNumberToName[prevChannelNumber] = prevChannelName;
		m_channelsNameToNumber[prevChannelName] = prevChannelNumber;

		m_channelsNumberToName[channel] = channelName;
		m_channelsNameToNumber[channelName] = channel;
	}
	else if (!isChannelNumberDefined && isChannelNameDefined)
	{
		int prevChannelNumber = m_channelsNameToNumber[channelName]; // номер канала, у которого данное название
		m_channelsNameToNumber[channelName] = channel;
		m_channelsNumberToName.erase(prevChannelNumber);
		m_channelsNumberToName[channel] = channelName;
	}
	else
	{
		// isChannelNumberDefined && !isChannelNameDefined если данный номер канала записан, но нет данного названия канала, меняем старое название канала на новое
		// если не записан данный номер канала и не записано данное название, то записываем // !isChannelNameDefined && !isChannelNumberDefined
		m_channelsNumberToName[channel] = channelName;
		m_channelsNameToNumber[channelName] = channel;
	}

	return true;
}

bool TV::DeleteChannelName(string channelName)
{
	if (!m_isTurned || m_channelsNameToNumber.find(channelName) == m_channelsNameToNumber.end())
	{
		return false;
	}

	int channel = m_channelsNameToNumber[channelName];
	m_channelsNumberToName.erase(channel);
	m_channelsNameToNumber.erase(channelName);
	return true;
}

string TV::GetChannelName(int channel)
{
	if (!m_isTurned || channel < MIN_CHANNEL || channel > MAX_CHANNEL || m_channelsNumberToName.find(channel) == m_channelsNumberToName.end())
	{
		return "";
	}

	return m_channelsNumberToName[channel];
}

int TV::GetChannelByName(string channelName)
{
	if (!m_isTurned || m_channelsNameToNumber.find(channelName) == m_channelsNameToNumber.end())
	{
		return -1;
	}

	return m_channelsNameToNumber[channelName];
}

bool TV::EraseExtraBlanks(string& str) const
{
	str.erase(
		unique_copy(str.begin(), str.end(), str.begin(),
			[](char c1, char c2) { return c1 == ' ' && c2 == ' '; }),
		str.end());
	if (str.empty() || str == " ")
	{
		return false;
	}

	if (str.front() == ' ')
	{
		str.erase(0, 1);
	}
	if (str.back() == ' ')
	{
		str.erase(str.length() - 1, 1);
	}

	return true;
}
