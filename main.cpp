#include "santrauka.h"
#include "funkcijos.h"

int main()
{
	std::locale::global(std::locale("lt_LT.UTF-8"));
	string failas = koki_faila_nuskaityti();
	suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(failas);
	cross_reference_lentele(failas);
}

// // rm build -Recurse -Force
// // cmake -B build -S . ; cmake --build build
// // .\build\Debug\main.exe
