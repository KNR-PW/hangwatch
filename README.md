
# hangwatch
To jest repozytorium projektu interaktywnego haczyka który podaje informacje czy ktoś znajduje się w sali kołowej. 
Projekt składa się z modelu wieszaka na klucze , kodu wgrywanego do płytki ESP oraz kodu prostej strony internetowej,
na której pojawiać się będzie informacja czy ktoś znajduje się w sali.

 
 ## Model
 Model haczyka składa się z: haczyka, dwóch diod LED, magnesu , korpusu, do którego przytwierdzone są mocowania na haczyk i ścianę ,wieczka, które zamyka całość od góry .
Mechanicznie haczyk ma działać tak, że po powieszeniu kluczyka na element pracujący, dołożony ciężar zmienia pozycję dźwigni krańcówki zamykając jej obwód,
o czym informacja dalej przekazywana jest do płytki ESP. Jedna dioda zapala się kiedy model podłączony jest do prądu ,a druga kiedy klucze zostaną powieszone na haczyku. 
Całość działa w ten sposób , że osoba przebywająca w pomieszczeniu musi powiesić klucze na haczyku ,żeby na stronie pojawiła się informacja. 
Żeby całość działała prawidłowo należy powiesić model na ścianie lub na magnesie , podłączyć do prądu o napięciu 5V.
## Endpoint

  **Endpoint  *"/hooks"***  
Program pobiera z płytkek ESP informacje na temat haczyków tzn  id płytek , sali w której się znajdują oraz ich stanu .Obsługuje żądanie typu POST  i GET . Po otrzymaniu  żądania , endpoint pobiera dane JSON z żądania i aktualizuje  zmienną *"state"* przechowująca informacje czy w jakiejś sali ktoś się znajduje . 
Tu również tutaj wysyłana będzie rutynowa  informacja od płytki sprawdzająca czy urządzenie działa. 

Jeżeli w sali znajduje się ktoś i powiesił klucze na haczyku to na stronie internetowej pojawia się wartość 
 ```json
{
 "1234" {
			"name": "warsztat027",
			"state": "hanged",
			"time" : "jakaś wartość"
        }
}
```
Natomiast jeżeli nikogo nie ma to pojawia się informacja 
 ```json
{
 "1234" {
			"name": "warsztat027",
			"state": "empty",
			"time" : "jakaś wartość"
        }
}
```
Informacja ta pojawi się po 10 sekundach  od zdjęcia kluczy z wieszaka.  
Możliwa jest również sytuacja kiedy pojawi się awaria. Wtedy na stronie pojawi się informacja
 ```json
{
 "1234" {
			"name": "warsztat027",
			"state": "offline",
			"time" : "jakaś wartość"
        }
}
```
## Uruchomienie  servera

 1. Otwieramy terminal ,w którym możemy uruchomić nasz serwer np. może być to Visual Studio Code.
 2. Sprawdzamy czy nasz program posiada wymagane moduły i pakiety.Informacje o wymaganiach naszego serwera znajdziemy w pliku requirements.txt znajdującym się w repozytorium razem z kodem serwera.
 3. Jeżeli nie posiadamy jakiegoś pakietu lub modułu to go instalujemy. 
 4. Jeżeli używamy Visual Studio Code to wciskamy ikonkę strzałki w prawym górnym rogu ekranu i uruchamiamy nasz program.



    

	 
 
    
        
     


