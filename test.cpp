#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string testo = "Il mio indirizzo email è mario.rossi@email.com, scrivimi!";
    // Regex per estrarre l'email (gruppo 0 è tutto il match, gruppo 1 è il nome, gruppo 2 è il dominio)
    std::regex pattern(R"(([a-zA-Z0-9._-]+)@([a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))");

    std::smatch matches; // Qui salveremo i risultati

    if (std::regex_search(testo, matches, pattern)) {
        std::cout << "Match completo trovato: " << matches[0] << std::endl;
        std::cout << "Nome utente (Gruppo 1): " << matches[1] << std::endl;
        std::cout << "Dominio (Gruppo 2): " << matches[2] << std::endl;
    }

    std::cout<<"my regex starts now"<<std::endl;
    std::smatch	found;
	std::string	word_to_check = "pippone57";
	std::regex	pattern2 = std::regex(R"(one\d+)");

	if (regex_search(word_to_check, found, pattern2))
		std::cout<<"found match "<<found[0]<<std::endl;

    return 0;
}
