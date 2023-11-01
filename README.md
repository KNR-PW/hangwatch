# hangwatch
To jest repozytorium projektu interaktywnego haczyka Który podaje informacje czy ktoś znajduje się w sali kołowej.

 Projekt składa się z modelu wieszaka na klucze oraz kodu wgrywanego do płytki ESP oraz kodu prostej strony internetowej, 
na której pojawiać się będzie informacja czy ktoś znajduje się w sali.Jeżeli w sali znajduje się ktos i powiesił
klucze na haczyku to na stronie internetowej pojawia się wartość gpio równa 10 natomiast jeżeli nikogo nie ma to 
na stronie zamiast wartosci gpio pokazywany jest []

Model haczyka składa się z:
 	-haczyka, 
	-korpusu, do którego przytwierdzone są mocowania na haczyk i ścianę, 
przygotowane w nim są miejsca do przytwierdzenia krańcówki oraz płytki przy użyciu heat insertów.
	-wieczka, które zamyka całość od góry
Mechanicznie haczyk ma działać tak, że po powieszeniu kluczyka na element pracujący, 
dołożony ciężar zmienia pozycję dźwigni krańcówki zamykając jej obwód, 
o czym informacja dalej przekazywana jest do płytki ESP.

W zakładce arduino znajduje się kod do płytki ESP. Składa się on z :
-zdefiniowanych bibliotek których używa program.
-podawane jest nazwa i hasło do sieci z którym łączyć ma się płytka 
-następnie podawane jest adress strony na która wysyłana ma byc wartość odczytana z płytki
-w setupie płytka łączy się z siecią
- w loopie najpierw podawana jest wartość gpio
-potem stworzony jest obiekt  DynamicJsonDocument o rozmiarze 200 bajtów, do którego dodawany 
jest stan GPIO jako atrybut "gpioState".
-następnie inicjalizowane jest połączenie HTTP z serwerem flask
-wysyłana jest wartość gpio na strone internetową
-po zakończeniu wysyłanie odczekiwana jest przewa po czym program jeszcze raz wysyła żądanie na strone 

w zakładce serwer znajduje się kod od flaska serve oraz folder template w którym jest index.html  
-w index.html znajduje się prosta strona internetowa 
- w serve znajduje sie :
a) prosta aplikacja flask oraz okreslamy jej nazwe
b) tworzymy pusty słownik gpiostate w którym przechowywana będzie wartośc gpio 
c)tworzymy endpoint /gpiostate w którym będzie obsługiwał otrzymane dane
d) otrzymujemy dane z płytki
e)Definiujemy endpoint "/get_gpio_state" , który będzie zwracał aktualny stan gpio_state
f)Definiujemy endpoint główny "/" , który będzie renderował szablon "index.html"

