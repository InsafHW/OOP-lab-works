#include <iostream>
#include "TV.h"
#include "TVController.h"
#include <algorithm>
#include <sstream>
#include <ostream>
#include <Windows.h>

const string TURN_ON_TV = "Включить телевизор";
const string TURN_OFF_TV = "Выключить телевизор";
const string SELECT_CHANNEL = "Выбрать канал";
const string INFO = "Вывести информацию";
const string EXIT = "Выйти";
const string SET_CHANNEL_NAME = "Установить название канала";
const string DELETE_CHANNEL_NAME = "Удалить название канала";
const string GET_CHANNEL_NUMBER = "Получить номер канала";
const string GET_CHANNEL_NAME = "Получить название канала";
const string SELECT_PREVIOUS_CHANNEL = "Переключиться на предыдущий канал";

const string FIRST = "1 - ";
const string SECOND = "2 - ";
const string THIRD = "3 - ";
const string FOURTH = "4 - ";
const string FIFTH = "5 - ";
const string SIXTH = "6 - ";
const string SEVENTH = "7 - ";
const string EIGTH = "8 - ";
const string NINETH = "9 - ";
const string TENTH = "10 - ";
const string BORDER = "-------------------------------------";

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	TVController tvController(cin, cout);
	int answer;
	bool isFinished = false;

	while (true)
	{
		if (isFinished) break;
		cout << BORDER << endl;
		cout << FIRST << TURN_ON_TV << endl;
		cout << SECOND << TURN_OFF_TV << endl;
		cout << THIRD << SELECT_CHANNEL << endl;
		cout << FOURTH << INFO << endl;
		cout << FIFTH << SET_CHANNEL_NAME << endl;
		cout << SIXTH << DELETE_CHANNEL_NAME << endl;
		cout << SEVENTH << GET_CHANNEL_NAME << endl;
		cout << EIGTH << GET_CHANNEL_NUMBER << endl;
		cout << NINETH << SELECT_PREVIOUS_CHANNEL << endl;
		cout << NINETH << EXIT << endl;
		cout << BORDER << endl;
		cin >> answer;

		switch (answer)
		{
		case 1:
			tvController.TurnOn();
			break;
		case 2:
			tvController.TurnOff();
			break;
		case 3:
			tvController.SelectChannel();
			break;
		case 4:
			tvController.Info();
			break;
		case 5:
			tvController.SetChannelName();
			break;
		case 6:
			tvController.DeleteChannelName();
			break;
		case 7:
			tvController.GetChannelName();
			break;
		case 8:
			tvController.GetChannelByName();
			break;
		case 9:
			tvController.SelectPreviousChannel();
			break;
		default:
			isFinished = true;
			break;
		}
	}
}
