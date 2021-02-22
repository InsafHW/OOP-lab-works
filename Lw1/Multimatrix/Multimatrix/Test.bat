@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Test Without files
%MyProgram% && goto err
echo Test1 passed

REM Test With zero matrix
%MyProgram% ZeroMatrix.txt matrix1.txt > %TMP%\output.txt && fc ZeroMatrix.txt %TMP%\output.txt || goto err
echo Test2 passed

REM Test With two non-empty files
%MyProgram% matrix1.txt matrix2.txt > %TMP%\output.txt && fc matrix1matrix2.txt %TMP%\output.txt || goto err
echo Test3 passed

%MyProgram% matrix2.txt matrix1.txt > %TMP%\output.txt && fc matrix2matrix1.txt %TMP%\output.txt || goto err
echo Test4 passed

echo All tests successfully passed
exit /B 0

:err
echo Test failed
exit /B 1