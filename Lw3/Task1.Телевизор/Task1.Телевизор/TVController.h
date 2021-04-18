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
	const string TV_ALREADY_TURNED_ON = "��������� ��� �������";
	const string TV_WAS_TURNED_ON = "��������� ������� �������";
	const string TV_ALREADY_TURNED_OFF = "��������� ��� ��������";
	const string TV_WAS_TURNED_OFF = "��������� ������� ��������";
	const string ENTER_CHANNEL_NAME_OR_NUMBER = "������� ����� / �������� ������";
	const string THERE_IS_NO_CHANNEL_WITH_THAT_NAME = "��� ������ � ����� ���������";
	const string THERE_IS_NO_CHANNEL_WITH_THAT_NUMBER = "��� ������ � ����� �������";
	const string CHANNEL_CHANGED = "����� ������� ����������";

	const string TV_IS_OFF = "��������� ��������";
	const string ENTER_CHANNEL_NUMBER = "������� ����� ������";
	const string ENTER_CHANNEL_NAME = "������� �������� ������";
	const string NAME_SETTLED = "�������� ������� �����������";
	const string INCORRECT_NAME = "�������� �� ������ ���� ������ � �� ��������� ���� �������";
	const string DELETED_SUCCESS = "�������� ������ ������� �������";
	const string THERE_IS_NO_NAME_FOR_THAT_CHANNEL = "� ������� ������ ��� ��������";
	const string THERE_IS_NO_PREVIOUS_CHANNEL = "��� ����������� ������";
};

