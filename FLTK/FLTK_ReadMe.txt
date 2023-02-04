(1)
Sprawdź czy masz zainstalowane w systemie programy git oraz CMake. Wywołaj:
git --version
cmake --version
Obydwa powinny odpowiedzieć numerem wersji - jeśli nie, to zainstaluj.

(2)
Z poziomu katalogu (BookCPP_PL) wywołaj:
git clone https://github.com/fltk/fltk.git FLTK

Cały projekt powinien się ściągnąć z platformy github.com i umieścić w katalogu FLTK.

(3)
W zależności od systemu i dostępnych narzędzi przeczytaj 
README.CMake.txt
README.Unix.txt
README.Windows.txt
README.macOS.md

i zbuduj FLTK zgodnie z instrukcjami tam zawartymi, albo przejdź do pktu (4*).

(4*)
###
Będąc w systemie Windows 10, na poziomie katalogu BookCPP_PL, otwieramy okno terminala cmd i wywołujemy:

cd FLTK
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug -D FLTK_BUILD_EXAMPLES=ON .. 

Jeśli wszystko jest OK (przeczytajmy komunikaty z programu cmake) to w katalogu buld powinniśmy znaleźć
FLTK.sln

Po podwójnym kliknięciu w FLTK.sln otwiera się Visual Studio (ja mam zainstalowane VS 2022), po czym klikamy 
Build - Build solution (F7)

Jeśli proces ukończy się powodzeniem, powinniśmy zobaczyć komunikat (ważne jest 0 failed)
========== Build: 149 succeeded, 0 failed, 0 up-to-date, 2 skipped ==========

W katalogu 
BookCPP_PL\FLTK\build\lib\Debug
powinniśmy znaleźć m.in. pliki: fltkd.lib

###
Będąc w systemie Linux (u mnie Ubuntu 20.04, działające w Virtual Box'ie na natywnym Win10):

dokładnie tak samo wołamy powyższe 4 komendy, po czym uruchamiamy
make 





(5)
Więcej informacji na stronie:
https://www.fltk.org/

