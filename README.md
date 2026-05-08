# regexs and python to c++ convertion

## Infos regarding regexs in C++ 💻

Una stringa regex utilizza una sintassi particolare.
Innanzitutto devi dichiarare la libreria \<regex\> per usarla, il modo
migliore per usarle e' con stringhe raw delimitate dalla 'R' prima della dichiarazione

```cpp
#include <regex>

//creazione di una variabile regex

int main(void)
{
	//regex che nella pattern vuole un numero
	//seguito da un punto e subito dopo dei caratteri
	std::regex pattern = std::regex (R"(\d).(\w+))")

}
```

Notare come abbia usato le raw strings, cioè la 'R', questo perché altrimenti non sarebbe possibile utilizzare i caratteri speciali delle regex, (\d o \w sono solo un esempio), visto che una stringa non **raw** tratterebbe la \ come un escape sequence **SEMRPE**
c++ possiede anche un'altra tipologia di variabile utilizzabile per cercare e confermare patterns all'interno delle regex, la tipologia di variabile si chiama, smatch e viene usata essenzialmente come un'array che al suo interno salva i dati trovati, grazie ai metodi della classe regex.
Lo si può vedere utilzzato nei metodi regex_search o regex_match, viene usato come dato da loro per modificarlo e inserire la stringa conforme alla ricerca fatta dal metodo.

```cpp
#include <regex>

int main(void)
{
	smatch	found;
	string	word_to_check = "pippone57";
	std::regex	pattern = regex (R"(one\d)");

	if (regex_search(word_to_check, found, pattern))
		std::cout<<"found match "<<found[0]<<std::endl;
	//in caso di errore usa std::regex_error in try and catch
}
```

una piccola cosa, se utilizziamo una Raw string dobbiamo definire dei delimitatori insomma qualcosa all'inizio e alla fine della stringa, essa **NON VIENE PRESA** in considerazione dall regex pattern quindi non c'è bisogno di preoccuparsi. come vedi infatti nelle regex che ho dichiarato ho messo le due parantesi tonde (), loro sono i delimitatori che dicono al computer da dove inizia la regex.

## Problemi nel debugging

Bisogna caapire se ogni pattern e' fissa quindi "nome." con possibilità di essere "nome.index(1)."
perché se no semplicemente rischiamo che se arriva un dato con la virgola all'inizio rompe il codice
tipo "test,member.uttutuut" se c'è "test," la pattern estrapolata non funziona. Ma va bene anche cosi'

## todo for next tasks ✍️

* talk about smatch var
* revision of code, can it be shortened?
* doing wrapping for python
