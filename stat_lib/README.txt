Создание и использование статических и динамических библиотек.

Для создания демонстрационного исполняемого файла, использующего статические библиотеки перейдите в директорию, где хранятся исходники
и вызовите команду:

make VV_test_stat

... а после запустите исполняемый файл:

./VV_test_stat

Для тех же целей, но с динамической библиотекой:

make VV_test_dyn

... и для запуска:

./VV_test_dyn

!!!!!ВНИМАНИЕ!!!!!
При возникновении ошибки с динамической библиотекой, попробуйте ввести команду:

export LD_LIBRARY_PATH=$PWD

... находясь при этом в директории с исходниками и самой библиотекой.
!!!!!ВНИМАНИЕ!!!!!
