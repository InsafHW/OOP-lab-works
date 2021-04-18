#include "TVController.h"
#include "TV.h"

TVController::TVController(istream& input, ostream& output)
	:input(input)
	, output(output)
{ }

void TVController::TurnOn()
{
	if (!tv.TurnOn())
	{
		output << TV_ALREADY_TURNED_ON << endl;
	}
	else
	{
		output << TV_WAS_TURNED_ON << endl;
	}
}

void TVController::TurnOff()
{
	if (!tv.TurnOff())
	{
		output << TV_ALREADY_TURNED_OFF << endl;
	}
	else
	{
		output << TV_WAS_TURNED_OFF << endl;
	}
}

void TVController::SelectChannel()
{
	if (!tv.IsTurnedOn())
	{
		output << TV_IS_OFF << endl;
		return;
	}

	output << ENTER_CHANNEL_NAME_OR_NUMBER << ": ";
	string channel;
	input >> channel;
	bool isOK = true;

	if (channel.find_first_not_of("0123456789") == -1)
	{
		if (!tv.SelectChannel(stoi(channel)))
		{
			isOK = false;
			output << THERE_IS_NO_CHANNEL_WITH_THAT_NUMBER << endl;
		}
	}
	else
	{
		if (!tv.SelectChannel(channel))
		{
			isOK = false;
			output << THERE_IS_NO_CHANNEL_WITH_THAT_NAME << endl;
		}
	}

	if (isOK)
	{
		output << CHANNEL_CHANGED << " на " << channel << endl;

	}
}

void TVController::Info()
{
	output << tv.Info() << endl;
}

void TVController::SetChannelName()
{
	if (!tv.IsTurnedOn())
	{
		output << TV_IS_OFF << endl;
		return;
	}

	int channel;
	string name;
	output << ENTER_CHANNEL_NUMBER << ": ";
	input >> channel;

	if (channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		output << THERE_IS_NO_CHANNEL_WITH_THAT_NUMBER << endl;
		return;
	}
	output << endl << ENTER_CHANNEL_NAME << ": ";

	char ch;
	ch = input.get();
	while (true)
	{
		ch = input.get();
		if (ch == '\n') break;
		name += ch;
	}

	if (tv.SetChannelName(channel, name))
	{
		output << NAME_SETTLED << endl;
	}
	else
	{
		output << INCORRECT_NAME << endl;
	}
}

void TVController::DeleteChannelName()
{
	if (!tv.IsTurnedOn())
	{
		output << TV_IS_OFF << endl;
		return;
	}
	string name;
	output << ENTER_CHANNEL_NAME << ": ";
	input >> name;
	if (tv.DeleteChannelName(name))
	{
		output << DELETED_SUCCESS << endl;
	}
	else
	{
		output << THERE_IS_NO_CHANNEL_WITH_THAT_NAME << endl;
	}
}

void TVController::GetChannelName()
{
	if (!tv.IsTurnedOn())
	{
		output << TV_IS_OFF << endl;
		return;
	}

	int channel;
	output << ENTER_CHANNEL_NUMBER << ": ";
	input >> channel;

	if (tv.GetChannelName(channel).empty())
	{
		output << THERE_IS_NO_NAME_FOR_THAT_CHANNEL << endl;
	}
	else
	{
		output << tv.GetChannelName(channel) << endl;
	}
}

void TVController::GetChannelByName()
{
	if (!tv.IsTurnedOn())
	{
		output << TV_IS_OFF << endl;
		return;
	}

	string name;
	output << ENTER_CHANNEL_NAME << endl;
	input >> name;
	if (tv.GetChannelByName(name) == -1)
	{
		output << THERE_IS_NO_CHANNEL_WITH_THAT_NAME << endl;
	}
	else
	{
		output << tv.GetChannelByName(name) << endl;
	}
}

void TVController::SelectPreviousChannel()
{
	if (!tv.IsTurnedOn())
	{
		output << TV_IS_OFF << endl;
		return;
	}

	if (!tv.SelectPreviousChannel())
	{
		output << THERE_IS_NO_PREVIOUS_CHANNEL << endl;
	}
	else
	{
		output << CHANNEL_CHANGED << endl;
	}
}
