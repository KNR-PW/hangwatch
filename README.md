# hangwatch
To jest repozytorium projektu interaktywnego haczyka który podaje informacje czy ktoś znajduje się w sali kołowej. 
Projekt składa się z modelu wieszaka na klucze , kodu wgrywanego do płytki ESP oraz kodu prostej strony internetowej,
na której pojawiać się będzie informacja czy ktoś znajduje się w sali.

 ## Działanie strony
 Na stronie wyświetli się  informacja o sali ,w której znajduję się kluczyk oraz jego stan .

 Jeżeli w sali znajduje się ktoś i powiesił klucze na haczyku to na stronie internetowej pojawia się wartość 
 
    {
	    "name": "warsztat027",
        "state": "hanged"
    }

 natomiast jeżeli nikogo nie ma to pojawia się informacja 
	   
    {
	    "name": "warsztat027",
        "state": "empty"
    }
    
 Informacja ta pojawi się po 10 sekundach  od zdjęcia kluczy z wieszaka.
Możliwa jest również sytuacja kiedy pojawi się awaria. Wtedy na stronie pojawi się informacja
 
		{
	        "name": "warsztat027",
	        "state": "offline"
	    }
 

 ## Model
 Model haczyka składa się z: haczyka, dwóch diod LED, magnesu , korpusu, do którego przytwierdzone są mocowania na haczyk i ścianę ,wieczka, które zamyka całość od góry .
Mechanicznie haczyk ma działać tak, że po powieszeniu kluczyka na element pracujący, dołożony ciężar zmienia pozycję dźwigni krańcówki zamykając jej obwód,
o czym informacja dalej przekazywana jest do płytki ESP. Jedna dioda zapala się kiedy model podłączony jest do prądu ,a druga kiedy klucze zostaną powieszone na haczyku. 
Całość działa w ten sposób , że osoba przebywająca w pomieszczeniu musi powiesić klucze na haczyku ,żeby na stronie pojawiła się informacja. 
Żeby całość działała prawidłowo należy powiesić model na ścianie lub na magnesie , podłączyć do prądu o napięciu 5V.
## Endpointy 

 1.  **Endpoint  *"/hooks"***    
Obsługuje żądanie typu POST i aktualizuje *"state"*. 				Po otrzymaniu  żądania , endpoint pobiera dane JSON z żądania  i aktualizuje  zmienną *"state"* przechowująca informacje czy ktoś znajduje się w sali .Pobierze on również informacje w jakiej sali znajduje się dany haczyk.Informacja ta będzie przechowywana w zmiennej "name". Endpoint informuje nas w jakim miejscu znajduje się kluczyk oraz w jakim stanie się znajduje tzn czy ktoś jest w sali czy nie albo czy jest awaria haczyka. 
To również tutaj wysyłana będzie rutynowa  informacja od płytki sprawdzająca czy urządzenie działa.   
Przykładowo może wyglądać to tak

    {
        "name": "warsztat027",
        "state": "empty"
    },
    {
        "name": "boks_ITC",
        "state": "offline"
    }


 2.  **Endpoint *"/hook_state"***   
Obsługuje żądanie typu GET i służy do pokazywania 				aktualnego stanu haczyka. Jeżeli od ostatniej aktualizacji  minęło więcej niż 10 sekund  stan zostanie ustawiony na "empty". 
	
    {
        "state": "empty"
    },
    

	 
 3. **Endpoint"*/hook_offline*"**  
 Obsługuje żądanie typu GET i służy do pokazywania 				aktualnego stanu . Jeżeli od ostatniej aktualizacji  mineło więcej niż dwie godziny stan zostanie ustawiony na "offline". Wygląda to tak: 
 
    {
        
         "state": "offline"
    }
  


