#include "funkcijos.h"
#include <cwctype>

string koki_faila_nuskaityti()
{
	string failo_pavadinimas;
	cout << "Galimi failai aplanke '" << aplankalo_pavadinimas << "':\n";
	for (const auto &entry : std::filesystem::directory_iterator(aplankalo_pavadinimas))
	{
		if (entry.path().extension() == ".txt")
		{
			cout << "- " << entry.path().filename().string() << endl;
		}
	}
	while (true)
	{
		try
		{
			cout << "Iveskite failo pavadinima: ";
			cin >> failo_pavadinimas;

			string sukurti_faila_aplankale = aplankalo_pavadinimas + "/" + failo_pavadinimas;

			if (!std::filesystem::exists(sukurti_faila_aplankale))
			{
				throw std::invalid_argument("Tokio failo nera. Bandykite dar karta.");
			}

			return sukurti_faila_aplankale;
		}
		catch (const std::invalid_argument &e)
		{
			cout << e.what() << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

// std::string apdorok(const std::string &zodis)
// {
// 	// Sukuriam lokalę
// 	boost::locale::generator gen;
// 	std::locale lietuviska = gen("Lithuanian_Lithuania.1257");
// 	// arba "Lithuanian_Lithuania.1257" ant Windows
// 	std::locale::global(lietuviska);

// 	std::wstring rezultatas;

// 	// Konvertuojam į platus simbolius (UTF-16 Windows)
// 	std::wstring zodis_w = boost::locale::conv::to_utf<wchar_t>(zodis, "UTF-8");

// 	for (wchar_t c : zodis_w)
// 	{
// 		// Naudojam Boost locale-aware alpha tikrinimą
// 		if (boost::locale::isalpha(c, lietuviska) || c == L'-')
// 		{
// 			rezultatas += boost::locale::tolower(c, lietuviska);
// 		}
// 	}

// 	// Grąžinam atgal į paprastą UTF-8 string
// 	return boost::locale::conv::from_utf(rezultatas, "UTF-8");
// }

string skyrybos_zenklai(const string &zodis)
{
	string rezultatas{};
	for (const unsigned char c : zodis)
	{
		if (!std::ispunct(c) && !std::isdigit(c))
		{
			rezultatas += tolower(c);
		}
	}
	return rezultatas;
}

void suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(const string &failo_pavadinimas)
{
	ifstream failas(failo_pavadinimas);
	if (!failas)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti failo!");
		return;
	}
	stringstream buferis;
	buferis << failas.rdbuf();
	failas.close();

	map<string, int> zodziu_kiekis;
	string zodis;
	while (buferis >> zodis)
	{
		string svarus_zodis = skyrybos_zenklai(zodis);
		if (!svarus_zodis.empty())
		{
			zodziu_kiekis[svarus_zodis]++;
		}
	}
	ofstream rezultatai("zodziu_dazniai.txt");
	for (const auto &pora : zodziu_kiekis)
	{
		if (pora.second > 1)
		{
			rezultatai << pora.first << ": " << pora.second << "\n";
		}
	}

	cout << "Rezultatai įrašyti į 'zodziu_dazniai.txt'\n";
}