# hangwatch
To jest repozytorium projektu interaktywnego haczyka który podaje informacje czy ktoś znajduje się w sali kołowej. 
Projekt składa się z modelu wieszaka na klucze , kodu wgrywanego do płytki ESP oraz kodu prostej strony internetowej,
na której pojawiać się będzie informacja czy ktoś znajduje się w sali.

 ## Działanie strony
 Jeżeli w sali znajduje się ktoś i powiesił klucze na haczyku to na stronie internetowej pojawia się wartość gpio równa 10 
, natomiast jeżeli nikogo nie ma to pojawia się informacja gpiostate:”offline”. Informacja ta pojawi się po 2 minutach od zdjęcia kluczy z wieszaka.
 ## Model
 Model haczyka składa się z: haczyka, korpusu, do którego przytwierdzone są mocowania na haczyk i ścianę,wieczka, które zamyka całość od góry 
.Mechanicznie haczyk ma działać tak, że po powieszeniu kluczyka na element pracujący, dołożony ciężar zmienia pozycję dźwigni krańcówki zamykając jej obwód,
o czym informacja dalej przekazywana jest do płytki ESP.

