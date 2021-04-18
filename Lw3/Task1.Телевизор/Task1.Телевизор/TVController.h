#pragma once
#include "TV.h"
#include <iostream>

class TVController
{
public:
	TVController(istream& input, ostream& output);
	void TurnOn();
	void TurnOff();
	void SelectChannel();
	void Info();
	void SetChannelName();
	void DeleteChannelName();
	void GetChannelName();
	void GetChannelByName();
	void SelectPreviousChannel();
private:
	TV tv;
	ostream& output;
	istream& input;
	const string TV_ALREADY_TURNED_ON = "Телевизор уже включен";
	const string TV_WAS_TURNED_ON = "Телевизор успешно включен";
	const string TV_ALREADY_TURNED_OFF = "Телевизор уже выключен";
	const string TV_WAS_TURNED_OFF = "Телевизор успешно выключен";
	const string ENTER_CHANNEL_NAME_OR_NUMBER = "Введите номер / название канала";
	const string THERE_IS_NO_CHANNEL_WITH_THAT_NAME = "Нет канала с таким названием";
	const string THERE_IS_NO_CHANNEL_WITH_THAT_NUMBER = "Нет канала с таким номером";
	const string CHANNEL_CHANGED = "Канал успешно переключен";

	const string TV_IS_OFF = "Телевизор выключен";
	const string ENTER_CHANNEL_NUMBER = "Введите номер канала";
	const string ENTER_CHANNEL_NAME = "Введите название канала";
	const string NAME_SETTLED = "Название успешно установлено";
	const string INCORRECT_NAME = "Название не должно быть пустым и не содержать лишь пробелы";
	const string DELETED_SUCCESS = "Название канала успешно удалено";
	const string THERE_IS_NO_NAME_FOR_THAT_CHANNEL = "У данного канала нет названия";
	const string THERE_IS_NO_PREVIOUS_CHANNEL = "Нет предыдущего канала";
};

