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

string skyrybos_zenklai(const string &zodis)
{
	string rezultatas{};
	string papildomi_skyrybos = "–„′−";

	for (const unsigned char c : zodis)
	{
		if (!std::ispunct(c) && !std::isdigit(c) && papildomi_skyrybos.find(c) == string::npos)
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

void cross_reference_lentele(const string &failo_pavadinimas)
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
	map<string, set<int>> zodziu_eilutes;

	string eilute;
	int eilutes_nr = 1;

	while (getline(buferis, eilute))
	{
		stringstream ss(eilute);
		string zodis;
		while (ss >> zodis)
		{
			string svarus = skyrybos_zenklai(zodis);
			if (!svarus.empty())
			{
				zodziu_kiekis[svarus]++;
				zodziu_eilutes[svarus].insert(eilutes_nr);
			}
		}
		eilutes_nr++;
	}
	ofstream out("cross_reference.txt");
	if (!out)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti failo!");
		return;
	}
	else
	{
		out << left << setw(30) << "Zodis" << "Eilutes\n";
		out << string(30, '-') << " " << string(40, '-') << "\n";
		for (const auto &[zodis, eilutes] : zodziu_eilutes)
		{
			if (zodziu_kiekis[zodis] > 1)
			{
				stringstream eilutes_srautui;
				bool pirma = true;
				for (int e : eilutes)
				{
					if (!pirma)
						eilutes_srautui << ", ";
					eilutes_srautui << e;
					pirma = false;
				}
				out << left << setw(30) << zodis << " " << left << eilutes_srautui.str() << "\n";
			}
		}
	}
	cout << "Cross-reference lentelė įrašyta į 'cross_reference.txt'\n";
}