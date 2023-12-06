
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
## Działanie servera
Działanie serwera krok po kroku wygląda tak :
 1. Importuje moduły time ,flask,request oraz jsonify. Time zawiera funkcje związane z czasem, flask jest frameworkiem webowym ,request służy do do obsługi żądań HTTP a jsonify przekształca dane na serwerze do formatu JSON przez płytkę ESP.
 2.  Inicjalizujemy  obiekt flask o nazwie app. 
 3. Następnie tworzymy pusty słownik *'state'*.
 4. Definiujemy endpoint  *'/hooks'* obsługujący metody typu POST.
 5. Definiujemy funkcje *receive_date* obsługującej żądanie typu POST.
 6. Przypisujemy zmiennej *'lastUpdate'* aktualny czas.
 7. Przypisujemy zmiennej *'content'* treść żądania HTTP przekazaną w formacie Json.
 8. Przypisujemy zmiennej *'board_id'* wartość klucza w treści żądania.
 9. Przypisujmy wartość zmiennej *received_state* do klucza *'state'* w słowniku *state[board_id]*
``` phyton
	 {
	    state[board_id]['state'] =received_state	 
	 } 
```
 10. Przypisujemy wartość klucza *'place'* w treści żądania do klucza *'place'* w słowniku *state[board_id]*.
 ```phyton
	{
	   state[board_id]['state']=content['place']	 
	} 
```
 11. Przypisuje wartość zmiennej *'lastUpdate'* do klucza 'time' w słowniku *state[board_id]*
 ```phyton
	{
	    state[board_id]['time']=lastUpdate 
	} 
```
 12. Definiujemy endpoint *'/hooks'* obsługujący tylko metody GET.
 13. Definiujemy funkcję *check_state(),* która będzie obsługiwać żądania GET na endpoint  *'/hooks'*.
 14. Tworzymy pętle ,która będzie iterować po elementach słownika *'state'* przypisując wartości klucza do board_id i wartość do *board_state*.
 15. Sprawdzamy czy czas od ostatniej aktualizacji stanu jest większy od 2 godzin. Jeżeli tak to ustawiamy stan haczyka na *'offline'.
 16.  Sprawdzamy  czy czas od ostatniej aktualizacji stanu jest większy od 10 sekund. Jeżeli tak to ustawiamy stan haczyka na *'empty'*. 
 17. Uruchamiamy aplikacje


    

	 
 
    
        
     


