#include "santrauka.h"
#include "funkcijos.h"

int main()
{
	// std::locale::global(std::locale("lt_LT"));
	// std::locale::global(std::locale(::setlocale(LC_ALL, "lt_LT")));
	std::setlocale(LC_ALL, "Lithuanian");
	string failas = koki_faila_nuskaityti();
	suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(failas);
}

// // rm build -Recurse -Force
// // cmake -B build -S . ; cmake --build build
// // .\build\Debug\main.exe

// #include "santrauka.h"
// #include "funkcijos.h"

// int main()
// {
// 	try
// 	{
// 		boost::locale::generator gen;
// 		std::locale::global(gen("lt_LT.UTF-8"));
// 		std::cout.imbue(std::locale());
// 	}
// 	catch (const std::invalid_argument &e)
// 	{
// 		std::cout << "Nepavyko nustatyti lokalės. Lietuviškos raidės gali būti netvarkingos.\n";
// 	}

// 	std::string failas = koki_faila_nuskaityti();
// 	suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(failas);
// }
