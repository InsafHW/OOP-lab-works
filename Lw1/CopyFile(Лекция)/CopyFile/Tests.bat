@echo off

REM ���� � ����������� ��������� ����������� ����� 1-� �������� ��������� ������
SET MyProgram = "%~1"

REM ������ �� ������� ��� ���������
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

REM ����� ������ �������
exit /B 0


REM ���� ����� �������� � ������ ������
:err
echo Test failed
exit /B 1