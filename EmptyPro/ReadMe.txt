
Przykładowy szablon do tworzenia własnych projektów użytkownika.

Zakładając, że twój projekt nazywa się „MyPro”, wykonaj następujące czynności:

1. Utwórz katalog o nazwie „MyPro” i skopiuj do niego wszystkie pliki
i foldery z „EmptyPro”.

2. W pliku ./MyPro/CMakeLists.txt znajdź linię
set(PROJECT_NAME PustyPro)
i zmień „EmptyPro” na nazwę swojego projektu, np. „MyPro” w naszym przykładzie
set(PROJECT_NAME MyPro)

3. Skopiuj/utwórz WSZYSTKIE swoje pliki źródłowe do ./MyPro/src
i WSZYSTKIE nagłówki do pliku ./MyPro/include

4. Zbuduj swój projekt zgodnie ze wspólnym schematem (poniżej).


=================================
Aby zbudować projekt, wykonaj następujące czynności:


1. W zależności od systemu operacyjnego zmień katalog na ten:
build_win
build_linux
build_mac
(lub po prostu stwórz swój "build")

2. Otwórz terminal i ustaw bieżący katalog na powyższy.

3. Z poziomu katalogu build_xxx napisz
cmake ..

4. Przejdź do katalogu build_xxx i uruchom swój projekt.



=================================
=================================

The purpose of this project is to provide a template project
for user's own projects. 
Assuming your project is named "MyPro", proceed as follows:

1. Make a directory named "MyPro" and copy to it all files 
and folders from the "EmptyPro".

2. In the ./MyPro/CMakeLists.txt find the line
set( PROJECT_NAME EmptyPro )
and change "EmptyPro" to the name of your project, i.e. "MyPro" in our example
set( PROJECT_NAME MyPro )

3. Copy/create ALL your source files to the ./MyPro/src
and ALL headers to the ./MyPro/include

4. Build your project in accordance with the common scheme (below).

=================================
To build a project do as follows:

1. Depending on your OS change directory to the one:
build_win
build_linux
build_mac

2. Open terminal and set current directory to the above one.

3. type 
cmake ..

4. Go to the build_xxx directory and launch your project.




