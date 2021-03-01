@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Test without number
%MyProgram% && goto err
echo Test1 passed

REM Test with binary number
%MyProgram% 0b110 && goto err
echo Test2 passed

REM Test with octal number
%MyProgram% 012 && goto err
echo Test3 passed

REM Test with hex number
%MyProgram% 0xF && goto err
echo Test4 passed

REM Test with decimal number
%MyProgram% 6 > %TMP%\output.txt && fc 6.txt %TMP%\output.txt || goto err
echo Test5 passed

%MyProgram% 163 > %TMP%\output.txt && fc 163.txt %TMP%\output.txt || goto err
echo Test6 passed

REM Test with letter
%MyProgram% f && goto err
echo Test7 passed

REM Test with out of range < 0
%MyProgram% -2 && goto err
echo Test8 passed

REM Test with out of range > 255
%MyProgram% 280 && goto err
echo Test9 passed

REM Test with border value = 0
%MyProgram% 0 || goto err
echo Test10 passed

REM Test with border value = 255
%MyProgram% 255 || goto err
echo Test11 passed

echo All test sucessfully passed
exit /B 0

:err
echo Test failed
exit /B 1