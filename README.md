# regex and python to c++ convertion

## Infos regarding regex in C++ 💻

Una stringa regex utilizza una sintassi particolare.
Innanzitutto devi dichiarare la libreria \<regex\> per usarla, il modo
migliore per usarle e' con stringhe raw delimitate dalla 'R' prima della dichiarazione

compilare con:

```bash
g++ -Wall -Wextra -Werror -g -fconcepts -lre2 file.cpp -o regex++
```

per usare cython come bridge per il codice

```bash
python setup.py build_ext --inplace
```

```cpp
#include <regex>

//creazione di una variabile regex

int main(void)
{
	//regex che nella pattern vuole un numero
	//seguito da un punto e subito dopo dei caratteri
	std::regex pattern = std::regex (R"((\d).(\w+))")

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

Una piccola cosa: la sintassi di base delle Raw String in C++ usa le parentesi tonde per racchiudere il testo, in questo modo: R"(testo)". Queste parentesi non fanno parte della regex, ma sono solo una regola del C++ per segnare l'inizio e la fine del contenuto raw. Nel caso in cui la nostra regex dovesse contenere per sbaglio la sequenza di chiusura standard )", il C++ ci permette di definire un "delimitatore" personalizzato tra le virgolette e le parentesi, ad esempio R"mio_delimitatore(testo)"mio_delimitatore", per evitare errori di compilazione.

## Problemi nel debugging

Bisogna caapire se ogni pattern e' fissa quindi "nome." con possibilità di essere "nome.index(1)."
perché se no semplicemente rischiamo che se arriva un dato con la virgola all'inizio rompe il codice
tipo "test,member.uttutuut" se c'è "test," la pattern estrapolata non funziona. Ma va bene anche cosi'

## il problema delle regex NFA =! DFA e il funzionamento della classe std::regex

Ci sono Non-deterministic Finite Automation e Deterministic Finite Automation

* il primo è una pattern casuale che prova ad indovinare una pattern possibile che coincida con quella richiesta finché non raggiunge il risultato (std::regex pare lavorare così)
* Il secondo è l'opposto, il "guesser" sa precisamente quali step prendere per raggiungere il risultato finale.

la classe regex utilizzano essenzialmente un algoritmo che si affida ad una caratteristica chiamata backtracking, un tratto in comune che ha con il NFA. Esso prende vari percorsi per definire la pattern ricercata, la stringa in questo caso, un carattere alla volta. Questo cercare a caso però ha i suoi costi, nel caso della classe regex **ogni volta** che all'interno di una stringa richiesta il carattere trovato NON corrisponde, il  ricercatore deve tornare indietro e provare un'altra pattern di quelle proposte per la ricerca, questo fenomeno è chiamato "disatrous backtracking" disastroso perché comporta una perdita di tempo incredibile per il computer.

La cosa che ancora mi sfugge è come RE2 funziona con NFA o se usa DFA implicitamente.
l'algoritmo di thompson lavora a O(m * n) dove la complessità è proporzionale alla dimensione dell'input moltiplicata per la dimensione della regex, mentre quello classico lavorerebbe a O(2^n) insomma è esponenziale a causa del backtracking, questo significa che a lungo termine tende a perdere di efficienza o peggio a bloccarsi.
In più, thompson non usa, durante la costruzione del DFA, il backtracking, questo è stato fatto apposta per evitare eventuali ricadute esponenziali di performance.
Citando google:
"No, Thompson’s algorithm (often called Thompson's Construction) does not use backreferences. It was specifically designed to process "pure" or classical regular expressions to guarantee linear-time matching." Questo comporta un'esclusione di complessità nella ricerca, MA impedirebbe all'algortimo di lavorare con un range di possibilità più ampio.
Diciamo che per patttern troppo complesse sarebbe impossibile utilizzare l'algoritmo di thomposon con le finite automata.

Ricapitolando: la classe regex utilizza l'algoritmo originale creato principalmente nel linguaggo Perl, esso ha il backtracking.
Thompson invece ha definito un algoritmo per costruire un NFA (Non-definite Finite Automata), che principalmente è più veloce, diretto e NON utilizza il backtracking, questo algoritmo è utilizzato dalla libreria RE2

l'articolo parla molto bene di queste implementazioni e di come thompson per le regular expression classicche abbia applicato il suo algoritmo.
<https://swtch.com/~rsc/regexp/regexp1.html>

Il modo per ottimizzare effettivamente l'algoritmo, sarebbe quello di usare entrambi, se la regex è semplice e non utilizza in alcun modo il backtracking allora si può usare quella di thompson, ma non appena c'è bisogno del backtracking, allora lì si usa l'algoritmo di perl.

## Python libraries to wrap c++ code 🖥️

cython mmm, penso sia l'unica opzione, bisogna creare una libreria che wrappa il codice C++,
necessitiamo di una libreria.
Consiglia di utilizzare come regex re2 di google, presa e messa in locale. C++ lavora con delle flag quando compila del codice, per linkare le librerie .so:

* -L specifica la cartella dove si trova la libreria
* -l per la libreria

quando usi le flag rimuovi il suffisso "lib" e ".so" quindi libre2.so diventa re2.
Questi accorgimenti li fa cython in automatico.

### Come funziona cython

cython per funzionare deve utilizzare due tipologie di file particolari:

1. i file pxd (praticamente l'header)
2. i file pyx (l'implementazione)

il file pxd è dove mettiamo i tipi utilizzati dal file c++ che vogliamo utilizzare praticamente.
Oltre ai tipi delle variabili utilizzate, inseriamo anche il prototipo della funzione che ci farà da ponte per il codice c++ in python.

```python
# the header for the cython code

from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.unordered_map cimport unordered_map

cdef extern from "split_key.hpp":
	vector[unordered_map[string, string]] find_match_for_regex(string word_to_check)

```

nel file pyx implementiamo il codice dichiarato nel filke pxd, il file specificamente fa da ponte e ciò che ritorna dev'essere qualcosa di leggibile da python
il file ha più o meno questo aspetto:

```python
# the implementer of the cython code

from my_wrapper cimport find_match_for_regex

def parse_string(string_to_check):
	# c++ works with bytes string, when using std::string
	byte_string = string_to_check.encode("utf-8")
	cdef list c_result = find_match_for_regex(byte_string)

	python_result = []
	for dictionary in c_result:
		retrieved_dict = {}
		for k, v in dictionary.items():
			retrieved_dict[k.decode("utf-8")] = v.decode("utf-8")
			python_result.append(retrieved_dict)

	return python_result
```

dopo aver creato gli appositi file bisogna creare il file che fa da ponte, o comunque traduttore per i file cython e il file cpp.
Questo file ha il compito di far comunicare i file cpp con gli altri, è praticamente il file che creerà la libreria .so visto che siamo su linux, per permettere agli altri file python di utilizzare le funzioni cpp.

Questo è il file setup.py:

```python
from setuptools import setup, Extension
from Cython.Build import cythonize

#defining the extension module

ext = Extension(
	name="my_wrapper",
	sources=["my_wrapper.pyx", "split_key.cpp"],
	language="c++",
	libraries=["re2"],
	library_dirs=["."],
)

setup(ext_modules=cythonize(ext))

```

la libreria cythonize mi permette di creare la libreria stessa creando un collegamento tra il file cpp e il file cython
dopo aver finalmente creato il vero ponte tra i linguaggi dobbiamo compilare il file con:

```bash
python setup.py build_ext --inplace
```

da questo scaturisce la libreria che possiamo utilizzare per usare il codice c++. Per utilizzare i metodi cpp, dobbiamo importare la libreria definita in setup.py, il nome è "my_wrapper" quindi nel file dove invocheremo la funzione faremo come segue:

```python
# importing the cython code we made
import my_wrapper

string_to_check = "member.submember(2).subsubmember.element(4).finalmember.secret_member(7)"

print("using C++ code to get results")
parsed_data = my_wrapper.parse_string(string_to_check)

print("retrieved data {}".format(parsed_data))
```

Notare come abbiamo utilizzato la funzione "parse_string" di my wrapper dichiarata nel file .pxd, essa poi invocherà a sua volta "find_match_for_regex" la funzione cpp.

quindi il ponte sarebbe così:
file.py ---> prende da file.pyx ----- prende da file.cpp

## todo for next tasks ✍️

* readme review 😨

## precisazioni

Se vuoi compilare e usare lo standard c++11 devi cambiare e setup.py che utilizza di default quello che trova sulla macchina

```python
ext = Extension(
    name="my_wrapper",
    sources=["my_wrapper.pyx", "split_key.cpp"],
    language="c++",
    libraries=["re2"],
    library_dirs=["."],
    extra_compile_args=["-std=c++11"], # Forza lo standard C++11
)
```
