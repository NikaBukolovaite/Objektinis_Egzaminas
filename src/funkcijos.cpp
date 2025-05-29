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

wstring skyrybos_zenklai(const wstring &zodis)
{
	wstring rezultatas{};
	wstring papildomi_skyrybos = L"–„′−";

	for (wchar_t c : zodis)
	{

		if (!std::iswpunct(c) && !std::iswdigit(c) && papildomi_skyrybos.find(c) == string::npos)
		{
			rezultatas += towlower(c);
		}
	}
	return rezultatas;
}

void suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(const string &failo_pavadinimas)
{
	wifstream failas(failo_pavadinimas);
	if (!failas)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti failo!");
		return;
	}
	wstringstream buferis;
	buferis << failas.rdbuf();
	failas.close();

	map<wstring, int> zodziu_kiekis;
	wstring zodis;
	while (buferis >> zodis)
	{
		wstring svarus_zodis = skyrybos_zenklai(zodis);
		if (!svarus_zodis.empty())
		{
			zodziu_kiekis[svarus_zodis]++;
		}
	}
	wofstream rezultatai("OutputFailai/zodziu_dazniai.txt");
	for (const auto &pora : zodziu_kiekis)
	{
		if (pora.second > 1)
		{
			rezultatai << pora.first << ": " << pora.second << "\n";
		}
	}

	cout << "Rezultatai įrašyti į 'OutputFailai/zodziu_dazniai.txt'\n";
}

void cross_reference_lentele(const string &failo_pavadinimas)
{
	wifstream failas(failo_pavadinimas);
	if (!failas)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti failo!");
		return;
	}
	wstringstream buferis;
	buferis << failas.rdbuf();
	failas.close();

	map<wstring, int> zodziu_kiekis;
	map<wstring, set<int>> zodziu_eilutes;

	wstring eilute;
	int eilutes_nr = 1;

	while (getline(buferis, eilute))
	{
		wstringstream ss(eilute);
		wstring zodis;
		while (ss >> zodis)
		{
			wstring svarus = skyrybos_zenklai(zodis);
			if (!svarus.empty())
			{
				zodziu_kiekis[svarus]++;
				zodziu_eilutes[svarus].insert(eilutes_nr);
			}
		}
		eilutes_nr++;
	}
	wofstream out("OutputFailai/cross_reference.txt");
	if (!out)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti failo!");
		return;
	}
	else
	{
		out << left << setw(30) << "Zodis" << "Eilutes\n";
		out << wstring(30, '-') << " " << wstring(40, '-') << "\n";
		for (const auto &[zodis, eilutes] : zodziu_eilutes)
		{
			if (zodziu_kiekis[zodis] > 1)
			{
				wstringstream eilutes_srautui;
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
	cout << "Cross-reference lentelė įrašyta į 'OutputFailai/cross_reference.txt'\n";
}

wstring gauti_url_link(const wstring &zodis)
{
	size_t paskutinis_taskas = zodis.rfind('.');
	if (paskutinis_taskas == wstring::npos || paskutinis_taskas + 1 >= zodis.size())
	{
		return L"";
	}
	wstring galune = zodis.substr(paskutinis_taskas + 1);
	size_t galas = 0;
	while (galas < galune.size() && isalpha(galune[galas]))
	{
		galas++;
	}
	return galune.substr(0, galas);
}

wstring pasalinti_galinius_skyrybos_zenklus(const wstring &zodis)
{
	size_t pabaiga = zodis.size();
	while (pabaiga > 0 && ispunct(zodis[pabaiga - 1]) && zodis[pabaiga - 1] != '/')
	{
		--pabaiga;
	}
	return zodis.substr(0, pabaiga);
}

bool ar_zodis_yra_url(const wstring &zodis, const set<wstring> &url_linkai)
{
	size_t tasko_pozicija = zodis.find('.');
	if (tasko_pozicija == wstring::npos || tasko_pozicija + 1 >= zodis.size())
	{
		return false;
	}

	wstring galune = zodis.substr(tasko_pozicija + 1);
	size_t end = 0;
	while (end < galune.size() && isalpha(galune[end]))
		end++;
	galune = galune.substr(0, end);
	transform(galune.begin(), galune.end(), galune.begin(), ::tolower);

	if (url_linkai.count(galune) == 0)
	{
		return false;
	}
	if (zodis.find(L"http://") == 0 || zodis.find(L"https://") == 0 || zodis.find(L"www.") == 0)
	{
		return true;
	}
	if (isalnum(zodis[0]) && zodis.find(' ') == wstring::npos)
	{
		return true;
	}
	return false;
}

void rasti_visus_galimus_url(const string &teksto_failas, const string &url_sarasas)
{
	// Ikeliu URL sarasa
	wifstream url_failas(url_sarasas);
	if (!url_failas)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti URL failo!");
		return;
	}
	set<wstring> url_linkai;
	wstring eilute;
	while (getline(url_failas, eilute))
	{
		if (!eilute.empty())
		{
			transform(eilute.begin(), eilute.end(), eilute.begin(), ::tolower);
			url_linkai.insert(eilute);
		}
	}
	url_failas.close();

	// Ikeliu nagrinejama teksta
	wifstream tekstas(teksto_failas);
	if (!tekstas)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti teksto failo!");
		return;
	}

	wstringstream buferis;
	buferis << tekstas.rdbuf();
	tekstas.close();

	// Tikrinu kiekviena zodi
	set<wstring> rasti_url;
	wstring zodis;
	while (buferis >> zodis)
	{
		wstring isvalytas = pasalinti_galinius_skyrybos_zenklus(zodis);
		if (ar_zodis_yra_url(isvalytas, url_linkai))
		{
			rasti_url.insert(isvalytas);
		}
	}

	// Irasome rezultatus i faila
	wofstream rezultatai("OutputFailai/rastieji_url.txt");
	if (!rezultatai)
	{
		throw std::ios_base::failure("Klaida: nepavyko atidaryti rezultatu failo!");
		return;
	}
	rezultatai << "Rasti URL'ai:\n"
			   << wstring(40, '-') << "\n";
	for (const auto &url : rasti_url)
	{
		rezultatai << url << "\n";
	}

	wcout << "Rasti URL'ai įrašyti į 'OutputFailai/rastieji_url.txt'\n";
}