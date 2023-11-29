# hangwatch
To jest repozytorium projektu interaktywnego haczyka który podaje informacje czy ktoś znajduje się w sali kołowej. 
Projekt składa się z modelu wieszaka na klucze , kodu wgrywanego do płytki ESP oraz kodu prostej strony internetowej,
na której pojawiać się będzie informacja czy ktoś znajduje się w sali.

 ## Działanie strony
 Jeżeli w sali znajduje się ktoś i powiesił klucze na haczyku to na stronie internetowej pojawia się wartość gpio równa 10 
, natomiast jeżeli nikogo nie ma to pojawia się informacja gpiostate:”offline”. Informacja ta pojawi się po 2 minutach od zdjęcia kluczy z wieszaka.
 ## Model
 Model haczyka składa się z: haczyka, dwóch diod LED, magnesu , korpusu, do którego przytwierdzone są mocowania na haczyk i ścianę ,wieczka, które zamyka całość od góry .
Mechanicznie haczyk ma działać tak, że po powieszeniu kluczyka na element pracujący, dołożony ciężar zmienia pozycję dźwigni krańcówki zamykając jej obwód,
o czym informacja dalej przekazywana jest do płytki ESP. Jedna dioda zapala się kiedy model podłączony jest do prądu ,a druga kiedy klucze zostaną powieszone na haczyku. 
Całość działa w ten sposób , że osoba przebywająca w pomieszczeniu musi powiesić klucze na haczyku ,żeby na stronie pojawiła się informacja. 
Żeby całość działała prawidłowo należy powiesić model na ścianie lub na magnesie , podłączyć do prądu o napięciu 5V.
## Endpointy 

 1.  **Endpoint  *"adres/gpio_state"***
	  obsługuje żądanie typu POST i aktualizuje stan gpio. 				Po otrzymaniu  żądania , endpoint pobiera dane JSON z żądania  i aktualizuje  zmienną `"gpio_state" przechowująca stan pinów GPIO

 2.  **endpoint *"/get_gpio_state "***:
 obsługuje żądanie typu GET i służy do pokazywania aktualnego stanu pinów gpio.Jeżeli od ostatniej aktualizacji stanów mineło więcej niż dwie minuty stan zostanie ustawiony na "offline". Nastepnię endpiont renderuje szablon "index.html" ze zmieniona nowym stanem GPIO . Wygląda to tak:
 *GPIO state: {'gpioState': 'offline'}*
 

 3. **Endpoint *" /"***
 Obsługuje żądanie typu GET i jest domyślną stroną "stroną internetową" . Pobiera i renderuje "index.html" z przekazaną informacją o stanie GPIO.

