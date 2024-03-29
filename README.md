
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

  **Endpoint  **`hooks`***  
Program pobiera z płytkek ESP informacje na temat haczyków tzn  id płytek , sali w której się znajdują oraz ich stanu .Obsługuje żądanie typu POST  i GET . Po otrzymaniu  żądania , endpoint pobiera dane JSON z żądania i aktualizuje  zmienną *"state"* przechowująca informacje czy w jakiejś sali ktoś się znajduje . 
Tu również tutaj wysyłana będzie rutynowa  informacja od płytki sprawdzająca czy urządzenie działa. 

Jeżeli w sali znajduje się ktoś i powiesił klucze na haczyku to na stronie internetowej pojawia się wartość 
 ```json
{
 "1234" {
			"place": "warsztat027",
			"state": "hanged",
			"last_activity_time" : "1707679919",
			"state_change_time" : "1707679019"
        }
}
```

Czas jest podany w sekundach

Natomiast jeżeli nikogo nie ma to pojawia się informacja 
 ```json
{
 "1234" {
			"place": "warsztat027",
			"state": "empty",
			"last_activity_time" : "1707679919",
			"state_change_time" : "1707679019"
        }
}
```
  
Możliwa jest również sytuacja kiedy pojawi się awaria. Wtedy na stronie pojawi się informacja
 ```json
{
 "1234" {
			"place": "warsztat027",
			"state": "offline",
			"last_activity_time" : "1707679919",
			"state_change_time" : "1707679019"
        }
}
```
## Uruchomienie  servera

1. Odpalamy terminal w folderze `server`, który może odpalić nasz serwer np. może być to Visual Studio Code.
2. W terminalu wpisujemy
 ```bash 
	  "pip install -r requirements.txt"
 ```
 Plik requirements.txt znajduje się w repozytorium.

3. Wpisujemy w terminalu

```bash 
"python3 serve.py"
```

### Uruchomienie w dockerze

```bash
cd serve
docker build --tag hangwatch .
docker run -p 8080:80 hangwatch
```

Aby uruchomić w tle laneży dodać flagę `-d --restart=always`.