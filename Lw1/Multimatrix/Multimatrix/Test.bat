@echo off
SET MyProgram="%~1"

REM Проверка на случай, если не передали аргумент
if %MyProgram%=="" (
	echo Please specify path to programm
	exit /B 1
)

REM Пустая матрица
%MyProgram% EmptyMatrix.txt matrix1.txt || goto err

REM Две непустые матрицы
%MyProgram% matrix1.txt matrix2.txt || goto err

REM Программой всего лишь с одной матрицей
%MyProgram% matrix1.txt || goto err

REM Тесты прошли успешно
echo Tests passed
exit /B 0

REM Сюда попадаем в случае ошибки
:err
echo Test failed
exit /B