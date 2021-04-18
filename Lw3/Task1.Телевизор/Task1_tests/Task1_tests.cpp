#include <iostream>
#include <sstream>
#include <Windows.h>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task1.Телевизор/TV.h"
#include "../Task1.Телевизор/TVController.h"

SCENARIO("У выключенного телевизора канал 0")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "У выключенного телевизора канал 0" << endl;
	TV tv;
	REQUIRE(tv.GetChannel() == 0);
	tv.SelectChannel(55);
	tv.TurnOff();
	REQUIRE(tv.GetChannel() == 0);
}


SCENARIO("Если у выкл. телевизора вызвать метод TurnOn, то он включится")
{
	cout << "Если у выкл. телевизора вызвать метод TurnOn, то он включится" << endl;
	TV tv;
	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn() == true);
}

SCENARIO("При самом первом включении телевизор включается на первом канале.")
{
	cout << "При самом первом включении телевизор включается на первом канале." << endl;
	TV tv;
	tv.TurnOn();
	REQUIRE(tv.GetChannel() == 1);
}

SCENARIO("Если у вкл. телевизора вызвать метод TurnOn, то он останется включенными")
{
	cout << "Если у вкл. телевизора вызвать метод TurnOn, то он останется включенными" << endl;
	TV tv;
	tv.TurnOn();
	tv.TurnOn();
	REQUIRE(tv.IsTurnedOn() == true);
}

SCENARIO("Если у выкл. телевизора вызвать метод TurnOff, то он останется выключенными")
{
	cout << "Если у выкл. телевизора вызвать метод TurnOff, то он останется выключенными" << endl;
	TV tv;
	tv.TurnOff();
	REQUIRE(tv.Info() == "Состояние: выключен\nНомер канала: 0\n");
}

SCENARIO("Если у вкл. телевизора вызвать метод TurnOff, то он выключится")
{
	cout << "Если у вкл. телевизора вызвать метод TurnOff, то он выключится" << endl;
	TV tv;
	tv.TurnOn();
	tv.TurnOff();
	REQUIRE(tv.IsTurnedOn() == false);
}

SCENARIO("Если переключить канал выкл. телевизора, он останется 0")
{
	cout << "Если переключить канал выкл. телевизора, он останется 0" << endl;
	TV tv;
	tv.SelectChannel(34);
	REQUIRE(tv.GetChannel() == 0);
}

SCENARIO("Если переключить вкл. телевизор на канал  < 1, то он останется прежним")
{
	cout << "Если переключить вкл. телевизор на канал  < 1, то он останется прежним" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(-43);
	REQUIRE(tv.GetChannel() == 1);
}

SCENARIO("Если переключить вкл. телевизор на канал  > 99, то он останется прежним")
{
	cout << "Если переключить вкл. телевизор на канал  > 99, то он останется прежним" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(103);
	REQUIRE(tv.GetChannel() == 1);
}

SCENARIO("Если переключить вкл. телевизор на канал  от 1 до 99, то он переключится на него")
{
	cout << "Если переключить вкл. телевизор на канал  от 1 до 99, то он переключится на него" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(56);
	REQUIRE(tv.GetChannel() == 56);
}

SCENARIO("Если выключить канал, а потом включить, то канал будет прежним, который был до выключения")
{
	cout << "Если выключить канал, а потом включить, то канал будет прежним, который был до выключения" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(56);
	tv.TurnOff();
	tv.TurnOn();
	REQUIRE(tv.GetChannel() == 56);
}

SCENARIO("Есть возможность переключения на предыдущий канал у включенного телевизора")
{
	cout << "Есть возможность переключения на предыдущий канал" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(54);
	tv.SelectPreviousChannel();
	REQUIRE(tv.GetChannel() == 1);
	tv.SelectChannel(55);
	tv.SelectChannel(56);
	tv.SelectChannel(57);
	REQUIRE(tv.GetChannel() == 57);
	tv.SelectPreviousChannel();
	REQUIRE(tv.GetChannel() == 56);
	tv.SelectPreviousChannel();
	REQUIRE(tv.GetChannel() == 55);
	tv.SelectPreviousChannel();
	REQUIRE(tv.GetChannel() == 1);
	tv.SelectPreviousChannel();
	REQUIRE(tv.GetChannel() == 1);

}

SCENARIO("Нет возможности переключения на предыдущий канал у выключенного телевизора")
{
	cout << "Нет возможности переключения на предыдущий канал у выключенного телевизора" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(54);
	tv.TurnOff();
	tv.SelectPreviousChannel();
	REQUIRE(tv.GetChannel() == 0);
}

SCENARIO("Нельзя установить название канала у выкл.телевизора")
{
	cout << "Нельзя установить название канала у выкл.телевизора" << endl;
	TV tv;
	tv.SetChannelName(1, "Первый");
	tv.TurnOn();
	REQUIRE(tv.GetChannelByName("Первый") == -1);
}

SCENARIO("Нельзя установить название канала как пустую строку")
{
	cout << "Нельзя установить название канала как пустую строку" << endl;
	TV tv;
	tv.TurnOn();
	REQUIRE(tv.SetChannelName(1, "") == false);
}

SCENARIO("Нельзя установить название канала одними пробелами")
{
	cout << "Нельзя установить название канала одними пробелами" << endl;
	TV tv;
	tv.TurnOn();
	REQUIRE(tv.SetChannelName(1, "    ") == false);
}

SCENARIO("Если задать название с пробелами, то установится название без лишних пробелов")
{
	cout << "Если задать название с пробелами, то установится название без лишних пробелов" << endl;
	TV tv;
	tv.TurnOn();
	REQUIRE(tv.SetChannelName(1, "  Первый  ") == true);
	REQUIRE(tv.GetChannelName(1) == "Первый");
}

SCENARIO("Если телевизор включен, и каналу не было задано название и данное название не принадлежит никакому другому каналу, то каналу установится это название")
{
	cout << "Если телевизор включен, и каналу не было задано название и данное название не принадлежит никакому другому каналу, то каналу установится это название" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	REQUIRE(tv.GetChannelByName("Первый") == 1);
}

SCENARIO("Если телевизор включен, и каналу не было задано название, но данное название принадлежит другому каналу, то этому каналу установится данное название, а у старого канала пропадет название")
{
	cout << "Если телевизор включен, и каналу не было задано название, но данное название принадлежит другому каналу, то этому каналу установится данное название, а у старого канала пропадет название" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.SetChannelName(2, "Первый");
	REQUIRE(tv.GetChannelName(1) == "");
	REQUIRE(tv.GetChannelName(2) == "Первый");
}

SCENARIO("Если телевизор включен, и каналу было задано название и данное название не принадлежит другому каналу, то этому каналу установится новое название")
{
	cout << "Если телевизор включен, и каналу было задано название и данное название не принадлежит другому каналу, то этому каналу установится новое название" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	REQUIRE(tv.GetChannelName(1) == "Первый");
	tv.SetChannelName(1, "Новый первый");
	REQUIRE(tv.GetChannelName(1) == "Новый первый");
}

SCENARIO("Если телевизор включен, и каналу было задано название и у задаваемого канала есть название, то произойдет смена ассоциаций")
{
	cout << "Если телевизор включен, и каналу было задано название и у задаваемого канала есть название, то произойдет смена ассоциаций" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.SetChannelName(2, "Второй");
	REQUIRE(tv.GetChannelName(1) == "Первый");
	REQUIRE(tv.GetChannelName(2) == "Второй");
	tv.SetChannelName(2, "Первый");
	REQUIRE(tv.GetChannelName(1) == "Второй");
	REQUIRE(tv.GetChannelName(2) == "Первый");
}

// Select channel по имени канала
SCENARIO("Если телевизор выкл, то канал не переключится")
{
	cout << "Если телевизор выкл, то канал не переключится" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(5, "Пятый");
	tv.TurnOff();
	REQUIRE(tv.GetChannel() == 0);
	tv.SelectChannel("Пятый");
	REQUIRE(tv.GetChannel() == 0);
}

SCENARIO("Если ввести название канала, кот. не сущ, то телевизоре не переключится")
{
	cout << "Если ввести название канала, кот. не сущ, то телевизоре не переключится" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(5, "Пятый");
	tv.SelectChannel("Первый");
	REQUIRE(tv.GetChannel() == 1);
}

SCENARIO("Если ввести название канала, кот. сущ, то телевизоре переключится на него")
{
	cout << "Если ввести название канала, кот. сущ, то телевизоре переключится на него" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(5, "Пятый");
	tv.SelectChannel("Пятый");
	REQUIRE(tv.GetChannel() == 5);
}

SCENARIO("Нельзя удалить название канала у выкл. телевизора")
{
	cout << "Нельзя удалить название канала у выкл. телевизора" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.TurnOff();
	REQUIRE(tv.DeleteChannelName("Первый") == false);
	tv.TurnOn();
	REQUIRE(tv.GetChannelByName("Первый") == 1);
}

SCENARIO("Нельзя удалить название канала, который не задан ни одному каналу")
{
	cout << "Нельзя удалить название канала, который не задан ни одному каналу" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	REQUIRE(tv.DeleteChannelName("Второй") == false);
}

SCENARIO("Можно удалить название канала, который задан какому-то каналу")
{
	cout << "Можно удалить название канала, который задан какому-то каналу" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	REQUIRE(tv.DeleteChannelName("Первый") == true);
	REQUIRE(tv.GetChannelByName("Первый") == -1);
}

SCENARIO("Нельзя получить навзвание канала у выкл. телевизора, т.е. будет пустая строка")
{
	cout << "Нельзя получить номер у выкл. телевизора, т.е. будет пустая строка" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.TurnOff();
	REQUIRE(tv.GetChannelName(1) == "");
}

SCENARIO("Нельзя получить название канала который < 0 или > 99, т.е. будет пустая строка")
{
	cout << "Нельзя получить название канала который < 0 или > 99, т.е. будет пустая строка" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.TurnOff();
	REQUIRE(tv.GetChannelName(-3) == "");
	REQUIRE(tv.GetChannelName(105) == "");
}

SCENARIO("Нельзя получить название канала который не установлен, т.е. будет пустая строка")
{
	cout << "Нельзя получить название канала который не установлен, т.е. будет пустая строка" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.TurnOff();
	REQUIRE(tv.GetChannelName(4) == "");
}

SCENARIO("Если канал установлен, то получим название этого канала")
{
	cout << "Если канал установлен, то получим название этого канала" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	REQUIRE(tv.GetChannelName(1) == "Первый");
}

SCENARIO("Нельзя получить номер канала у выкл. телевизора, т.е. будет -1")
{
	cout << "Нельзя получить номер канала у выкл. телевизора, т.е. будет -1" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.TurnOff();
	REQUIRE(tv.GetChannelByName("Первый") == -1);
}

SCENARIO("Нельзя получить номер канала который не установлен, т.е. будет -1")
{
	cout << "Нельзя получить номер канала который не установлен, т.е. будет -1" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.TurnOff();
	REQUIRE(tv.GetChannelByName("Второй") == -1);
}

SCENARIO("Если название установлено, то получим номер этого канала")
{
	cout << "Если название установлено, то получим номер этого канала" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	REQUIRE(tv.GetChannelByName("Первый") == 1);
}

SCENARIO("Проверка инфо у выкл. телевизора, у которого не заданы названия каналов")
{
	cout << "Проверка инфо у выкл. телевизора" << endl;
	TV tv;
	REQUIRE(tv.Info() == "Состояние: выключен\nНомер канала: 0\n");
}

SCENARIO("Проверка инфо у выкл. телевизора, у которого заданы названия каналов")
{
	cout << "Проверка инфо у выкл. телевизора, у которого заданый названия каналов" << endl;
	TV tv;
	tv.TurnOn();
	tv.SetChannelName(1, "Первый");
	tv.SetChannelName(2, "Второй");
	tv.SetChannelName(3, "Третий");
	tv.SetChannelName(4, "Четвертый");
	tv.SetChannelName(5, "Пятый");
	tv.TurnOff();
	REQUIRE(tv.Info() == "Состояние: выключен\nНомер канала: 0\n1 - Первый\n2 - Второй\n3 - Третий\n4 - Четвертый\n5 - Пятый");
}

SCENARIO("Проверка инфо у вкл. телевизора, который включили в первый, у которого не заданы названия каналов")
{
	cout << "Проверка инфо у вкл. телевизора, который включили в первый раз, у которого не заданы названия каналов" << endl;
	TV tv;
	tv.TurnOn();
	REQUIRE(tv.Info() == "Состояние: включен\nНомер канала: 1\n");
}

SCENARIO("Проверка инфо у вкл. телевизора, который до этого включали и ставили какой-то канал, у которого не заданы названия каналов")
{
	cout << "Проверка инфо у вкл. телевизора, который включили в первый раз, у которого не заданы названия каналов" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	tv.TurnOff();
	tv.TurnOn();
	REQUIRE(tv.Info() == "Состояние: включен\nНомер канала: 5\n");
}

SCENARIO("Проверка инфо у вкл. телевизора, который до этого включали и ставили какой-то канал, у которого заданы названия каналов")
{
	cout << "Проверка инфо у вкл. телевизора, который включили в первый раз, у которого заданы названия каналов" << endl;
	TV tv;
	tv.TurnOn();
	tv.SelectChannel(5);
	tv.SetChannelName(1, "Первый");
	tv.SetChannelName(2, "Второй");
	tv.SetChannelName(3, "Третий");
	tv.SetChannelName(4, "Четвертый");
	tv.SetChannelName(5, "Пятый");
	REQUIRE(tv.Info() == "Состояние: включен\nНомер канала: 5\n1 - Первый\n2 - Второй\n3 - Третий\n4 - Четвертый\n5 - Пятый");
}


//////////////

SCENARIO("TVController: если включить тв, то выведет, что тв успешно включен")
{
	cout << "TVController: если включить тв, то выведет, что тв успешно включен" << endl;
	stringstream input;
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если попытаться вкл. включенный тв, то выведет, что тв уже включен")
{
	cout << "TVController: если попытаться вкл. включенный тв, то выведет, что тв уже включен" << endl;
	stringstream input;
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\nТелевизор уже включен\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.TurnOn();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если выключить тв, то выведет, что тв успешно выключен")
{
	cout << "TVController: если выключить тв, то выведет, что тв успешно выключен" << endl;
	stringstream input;
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\nТелевизор успешно выключен\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.TurnOff();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если попытатсья выключить выключенный тв, то выведет, что тв уже выключен")
{
	cout << "TVController: если попытатсья выключить выключенный тв, то выведет, что тв уже выключен" << endl;
	stringstream input;
	ostringstream output;
	string expectedOutput = "Телевизор уже выключен\n";
	TVController tvC(input, output);
	tvC.TurnOff();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если попытаться установить канал у выкл. ТВ, то выведет, что тв выключен")
{
	cout << "TVController: если попытаться установить канал у выкл. ТВ, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;
	string expectedOutput = "Телевизор выключен\n";
	TVController tvC(input, output);
	tvC.SetChannelName();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если попытаться установить канал, который < 1 или > 99, то выведет, что такого канала нет")
{
	cout << "TVController: если попытаться установить канал, который < 1 или > 99, то выведет, что такого канала нет" << endl;
	stringstream input;
	input << "0";
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: Нет канала с таким номером\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SetChannelName();
	REQUIRE(expectedOutput == output.str());

	stringstream input1;
	input1 << "102";
	ostringstream output1;
	TVController tvC1(input1, output1);
	tvC1.TurnOn();
	tvC1.SetChannelName();
	REQUIRE(expectedOutput == output1.str());
}

SCENARIO("TVController: если попытаться установить пустое назавние канала или лишь пробелы, то выведет, что нельзя ввести пустую строку или строку с пробелами")
{
	cout << "TVController: если попытаться установить канал у выкл. ТВ, то выведет, что тв выключен" << endl;
	stringstream input1;
	input1 << "1" << endl << "" << endl;
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: \nВведите название канала: Название не должно быть пустым и не содержать лишь пробелы\n";
	TVController tvC(input1, output);
	tvC.TurnOn();
	tvC.SetChannelName();
	REQUIRE(expectedOutput == output.str());

	output.str("");
	stringstream input2;
	input2 << "2" << endl << "   " << endl;
	TVController tvC1(input2, output);
	tvC1.TurnOn();
	tvC1.SetChannelName();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если установить нормальному номеру нормальное название, то выведет, что название успешно установлено")
{
	cout << "TVController: если установить нормальному номеру нормальное название, то выведет, что название успешно установлено" << endl;
	stringstream input;
	input << "1" << endl << "Первый" << endl;
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: \nВведите название канала: Название успешно установлено\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SetChannelName();
	REQUIRE(expectedOutput == output.str());
}

SCENARIO("TVController: если выбрать канал, который < 1 или > 99, то выведет, что нет такого канала")
{
	cout << "TVController: если выбрать канал, который < 1 или > 99, то выведет, что нет такого канала, или ввести название канала, которое не было задано - выведет нет канала с таким названием" << endl;
	stringstream input1;
	stringstream input2;
	stringstream input3;
	input1 << "0";
	input2 << "105";
	input3 << "Первый";
	ostringstream output;
	string expectedOutput = "Телевизор успешно включен\nВведите номер / название канала: Нет канала с таким номером\n";
	TVController tvC(input1, output);
	tvC.TurnOn();
	tvC.SelectChannel();
	REQUIRE(expectedOutput == output.str());

	output.str("");
	TVController tvC1(input2, output);
	tvC1.TurnOn();
	tvC1.SelectChannel();
	REQUIRE(expectedOutput == output.str());

	string expectedOutput1 = "Телевизор успешно включен\nВведите номер / название канала: Нет канала с таким названием\n";
	output.str("");
	TVController tvC2(input3, output);
	tvC2.TurnOn();
	tvC2.SelectChannel();
	REQUIRE(expectedOutput1 == output.str());
}

SCENARIO("TVController: если выбрать нормальный номер канала или установленное название, то выведет, что успешно переключено")
{
	cout << "TVController: если выбрать нормальный номер канала или установленное название, то выведет, что успешно переключено" << endl;
	stringstream input1;
	stringstream input2;
	input1 << "1";
	input2 << "1" << endl << "Первый" << endl << "Первый";
	ostringstream output;
	string expectedOutput1 = "Телевизор успешно включен\nВведите номер / название канала: Канал успешно переключен на 1\n";
	TVController tvC1(input1, output);
	tvC1.TurnOn();
	tvC1.SelectChannel();
	REQUIRE(expectedOutput1 == output.str());

	output.str("");
	TVController tvC2(input2, output);
	tvC2.TurnOn();
	tvC2.SetChannelName();
	tvC2.SelectChannel();
	string expectedOutput2 = "Телевизор успешно включен\nВведите номер канала: \nВведите название канала: Название успешно установлено\nВведите номер / название канала: Канал успешно переключен на Первый\n";
	REQUIRE(expectedOutput2 == output.str());
}

SCENARIO("TVController: если попытаться удалить название канала при выкл. тв, то выведет, что тв выключен")
{
	cout << "TVController: если попытаться удалить название канала при выкл. тв, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;

	string expectedOutput = "Телевизор выключен\n";
	TVController tvC(input, output);
	tvC.DeleteChannelName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться удалить название канала, которое не задано, то выведет, что нет канала с таким названием")
{
	cout << "TVController: если попытаться удалить название канала, которое не задано, то выведет, что нет канала с таким названием" << endl;
	stringstream input;
	ostringstream output;
	input << "Первый";

	string expectedOutput = "Телевизор успешно включен\nВведите название канала: Нет канала с таким названием\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.DeleteChannelName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если удалить название канала, которое задано, то выведет, что название канала успешно удалено")
{
	cout << "TVController: если удалить название канала, которое задано, то выведет, что название канала успешно удалено" << endl;
	stringstream input;
	ostringstream output;
	input << "1" << endl << "Первый" << endl << "Первый";

	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: \nВведите название канала: Название успешно установлено\nВведите название канала: Название канала успешно удалено\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SetChannelName();
	tvC.DeleteChannelName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться получить название канала у выкл. тв, то выведет, что тв выключен")
{
	cout << "TVController: если попытаться получить название канала у выкл. тв, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;

	string expectedOutput = "Телевизор выключен\n";
	TVController tvC(input, output);
	tvC.GetChannelName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться получить название канала у канала, которому не устан. название, то выведет, что нет названия для этого канала")
{
	cout << "TVController: если попытаться получить название канала у выкл. тв, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;
	input << "1" << endl;

	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: У данного канала нет названия\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.GetChannelName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться получить название канала у канала, которому устан. название, то выведет название этого канала")
{
	cout << "TVController: если попытаться получить название канала у канала, которому устан. название, то выведет название этого" << endl;
	stringstream input;
	ostringstream output;
	input << "1" << endl << "Первый" << endl << "1" << endl;

	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: \nВведите название канала: Название успешно установлено\nВведите номер канала: Первый\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SetChannelName();
	tvC.GetChannelName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться получить номер канала у выкл. тв, то выведет, что тв выключен")
{
	cout << "TVController: если попытаться получить название канала у выкл. тв, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;

	string expectedOutput = "Телевизор выключен\n";
	TVController tvC(input, output);
	tvC.GetChannelByName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться получить номер канала у канала, название которого не соотв. каналу, то выведет, что нет названия для этого канала")
{
	cout << "TVController: если попытаться получить название канала у выкл. тв, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;
	input << "Первый" << endl;

	string expectedOutput = "Телевизор успешно включен\nВведите название канала\nНет канала с таким названием\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.GetChannelByName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться получить номер канала у канала, которому устан. название, то выведет номер этого канала")
{
	cout << "TVController: если попытаться получить название канала у канала, которому устан. название, то выведет название этого" << endl;
	stringstream input;
	ostringstream output;
	input << "1" << endl << "Первый" << endl << "Первый" << endl;

	string expectedOutput = "Телевизор успешно включен\nВведите номер канала: \nВведите название канала: Название успешно установлено\nВведите название канала\n1\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SetChannelName();
	tvC.GetChannelByName();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться перекл. на пред. канала, то выведет, что тв выключен")
{
	cout << "TVController: если попытаться перекл. на пред. канала, то выведет, что тв выключен" << endl;
	stringstream input;
	ostringstream output;

	string expectedOutput = "Телевизор выключен\n";
	TVController tvC(input, output);
	tvC.SelectPreviousChannel();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться перекл. на пред. канала, но уже нет предыдущего канала, то выведет, что нет предыдыщуего канала")
{
	cout << "TVController: если попытаться перекл. на пред. канала, но уже нет предыдущего канала, то выведет, что нет предыдыщуего канала" << endl;
	stringstream input;
	ostringstream output;

	string expectedOutput = "Телевизор успешно включен\nНет предыдущего канала\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SelectPreviousChannel();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: если попытаться перекл. на пред. канал и есть предыдущий канал, то выведет, что канал успешно переключен")
{
	cout << "TVController: если попытаться перекл. на пред. канал и есть предыдущий канал, то выведет, что канал успешно переключен" << endl;
	stringstream input;
	ostringstream output;
	input << "5";

	string expectedOutput = "Телевизор успешно включен\nВведите номер / название канала: Канал успешно переключен на 5\nКанал успешно переключен\n";
	TVController tvC(input, output);
	tvC.TurnOn();
	tvC.SelectChannel();
	tvC.SelectPreviousChannel();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("TVController: info")
{
	cout << "TVController: info. Если тв выключено и не заданы названия, то состояние: выключено, номер канала: 0" << endl;
	stringstream input1;
	ostringstream output;

	string expectedOutput1 = "Состояние: выключен\nНомер канала: 0\n\n";
	TVController tvC1(input1, output);
	tvC1.Info();
	REQUIRE(expectedOutput1 == output.str());

	cout << "TVController: info. Если тв выключено и заданы названия, то состояние: выключено, номер канала: 0, а также выведет названия каналов" << endl;
	output.str("");
	stringstream input2;
	input2 << "1" << endl << "Первый" << endl << "2" << endl << "Второй" << endl;
	string expectedOutput2 =
		"Телевизор успешно включен\nВведите номер канала: \n"
		"Введите название канала: Название успешно установлено\n"
		"Введите номер канала: \nВведите название канала: Название успешно установлено\n"
		"Телевизор успешно выключен\n"
		"Состояние: выключен\nНомер канала: 0\n1 - Первый\n2 - Второй\n";
	TVController tvC2(input2, output);
	tvC2.TurnOn();
	tvC2.SetChannelName();
	tvC2.SetChannelName();
	tvC2.TurnOff();
	tvC2.Info();
	REQUIRE(expectedOutput2 == output.str());

	cout << "TVController: info. Если тв впервый раз вкл, то состояние: включено, номер канала 1" << endl;
	output.str("");
	stringstream input3;
	string expectedOutput3 = "Телевизор успешно включен\nСостояние: включен\nНомер канала: 1\n\n";
	TVController tvC3(input3, output);
	tvC3.TurnOn();
	tvC3.Info();
	REQUIRE(output.str() == expectedOutput3);

	cout << "TVController: info. Если тв был переключен на какой-то канал, а потом включен, то состояние: включено, номер канала предыдущий";
	output.str("");
	stringstream input4;
	string expectedOutput4 = "Телевизор успешно включен\n"
		"Введите номер / название канала: Канал успешно переключен на 56\n"
		"Телевизор успешно выключен\nТелевизор успешно включен\nСостояние: включен\nНомер канала: 56\n\n";
	input4 << "56" << endl;
	TVController tvC4(input4, output);
	tvC4.TurnOn();
	tvC4.SelectChannel();
	tvC4.TurnOff();
	tvC4.TurnOn();
	tvC4.Info();
	REQUIRE(output.str() == expectedOutput4);

	cout << "TVController: info. Если тв был переключен на какой-то канал, а потом включен и введены названия каналов, то состояние: включено, номер канала предыдущий, и выдаст список каналов";
	output.str("");
	stringstream input5;
	input5 << "1" << endl << "Первый" << endl << "2" << endl << "Второй" << endl << "56" << endl;
	string expectedOutput5 =
		"Телевизор успешно включен\n"
		"Введите номер канала: \n"
		"Введите название канала: Название успешно установлено\n"
		"Введите номер канала: \n"
		"Введите название канала: Название успешно установлено\n"
		"Введите номер / название канала: Канал успешно переключен на 56\n"
		"Телевизор успешно выключен\nТелевизор успешно включен\nСостояние: включен\nНомер канала: 56\n1 - Первый\n2 - Второй\n";
	TVController tvC5(input5, output);
	tvC5.TurnOn();
	tvC5.SetChannelName();
	tvC5.SetChannelName();
	tvC5.SelectChannel();
	tvC5.TurnOff();
	tvC5.TurnOn();
	tvC5.Info();
	REQUIRE(output.str() == expectedOutput5);
}