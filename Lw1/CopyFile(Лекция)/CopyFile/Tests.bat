@echo off

REM Путь к тестируемой программе передеатеся через 1-й агрумент командной строки
SET MyProgram = "%~1"

REM Защита от запуска без аргумента
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" || goto err

REM Copy non-empty file
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" || goto err
fc NoneEmpty.txt "%TEMP%\output.txt" || goto err

REM Тесты прошли успешно
exit /B 0


REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1