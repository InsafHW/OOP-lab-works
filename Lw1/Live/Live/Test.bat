@echo off

SET MyProgram="%~1"
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Test without file
%MyProgram% && goto err
echo Test1 passed

REM Test with field without any person on
%MyProgram% EmptyField.txt > %TMP%\output.txt && fc EmptyField.txt %TMP%\output.txt || goto err
echo Test2 passed

REM Test with 4neighbours person
%MyProgram% 4neighboursInput.txt > %TMP%\output.txt && fc 4neighboursOutput.txt %TMP%\output.txt || goto err
echo Test3 passed

REM Test Shoudl render new person
%MyProgram% shouldRenderNewPersonInput.txt > %TMP%\output.txt && fc shouldRenderNewPersonOutput.txt %TMP%\output.txt || goto err
echo Test4 passed

REM Test with output file
%MyProgram% shouldRenderNewPersonInput.txt output.txt && fc shouldRenderNewPersonOutput.txt output.txt || goto err
echo Test5 passed

REM Test with file rows length which is less than previous one
%MyProgram% moreRow.txt && goto err
echo Test6 passed

REM Test with file rows length which is more than previous one
%MyProgram% lessRow.txt && goto err
echo Test7 passed

echo All test passed successfully
exit /B 0

:err
echo Test failed
exit /B 1