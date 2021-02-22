@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Test without file
%MyProgram% && goto err
echo Test1 passed

REM Test with empty file
%MyProgram% Empty.txt && goto err
echo Test2 passed

REM Test with matrix which determinate is 0
%MyProgram% Zeromatrix.txt && goto err
echo Test3 passed

REM Test with non zero determinate matrix
%MyProgram% matrix1.txt > %TMP%\output.txt && fc %TMP%\output.txt matrix1inverted.txt || goto err
echo Test4 passed

REM Test with non digit value
%MyProgram% LetterContain.txt && goto err
echo Test5 passed

REM Test with not-full matrix
%MyProgram% NotfullMatrix.txt && goto err
echo Test6 passed

REM Test with double numbers
%MyProgram% matrix1Double.txt > %TMP%\output.txt && fc %TMP%\output.txt matrix1inverted.txt || goto err
echo Test7 passed

echo All test passed successfully
exit /B 0

:err
echo Test failed
exit /B 1