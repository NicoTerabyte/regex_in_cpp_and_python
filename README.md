# Infos regarding regexs in C++

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
	std::regex r(R"(\d).(\w+))")
	
}
```
