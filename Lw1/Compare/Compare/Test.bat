@echo off

echo %~1

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Test Two Empty Files
%MyProgram% emptyFile1.txt emptyFile2.txt && fc emptyFile1 emptyFile2 || goto err
echo Test1 passed

REM Test Two equal Files
%MyProgram% file1.txt file2.txt && fc file1.txt file2.txt || goto err
echo Test2 passed

REM Test Two Different Files
%MyProgram% file1.txt file3.txt || fc file1.txt file3.txt && goto err
echo Test3 passed

REM Test With only one file
%MyProgram% file1.txt && goto err
echo Test4 passed

REM Test Without Files
%MyProgram% && goto err
echo Test5 passed

echo All tests succesfully passed
exit /B 0

:err
echo Test failed
exit /B 1