@echo off
SET MyProgram="%~1"

REM �������� �� ������, ���� �� �������� ��������
if %MyProgram%=="" (
	echo Please specify path to programm
	exit /B 1
)

REM ������ �������
%MyProgram% EmptyMatrix.txt matrix1.txt || goto err

REM ��� �������� �������
%MyProgram% matrix1.txt matrix2.txt || goto err

REM ���������� ����� ���� � ����� ��������
%MyProgram% matrix1.txt || goto err

REM ����� ������ �������
echo Tests passed
exit /B 0

REM ���� �������� � ������ ������
:err
echo Test failed
exit /B