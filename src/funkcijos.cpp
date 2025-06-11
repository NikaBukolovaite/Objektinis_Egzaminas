#include "funkcijos.h"
#include <cwctype>
#include <stdexcept>

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
	wstring rezultatas;
	for (wchar_t c : zodis)
	{

		if (iswalpha(c) || c == L'ė' || c == L'ų' || c == L'ū' || c == L'ą' || c == L'č' || c == L'ę' || c == L'į' || c == L'š' || c == L'ž' || c == L'ó')
		{
			rezultatas += towlower(c);
		}
	}
	return rezultatas;
}

void eilute(wstringstream &eilute)
{
	const set<wchar_t> skirybos_zenklai = {
		L'.', L',', L';', L':', L'!', L'?', L'-', L'(', L')', L'[', L']', L'{', L'}',
		L'\'', L'"', L'/', L'\\', L'|', L'@', L'#', L'$', L'%', L'^', L'&', L'*',
		L'_', L'+', L'=', L'<', L'>', L'`', L'~',
		L'—', L'–', L'−', L'‐', L'‒', L'―',
		L'„', L'“',
		L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'};

	wchar_t simbolis;
	wstring rezultatas;
	while (eilute.get(simbolis))
	{
		if (skirybos_zenklai.count(simbolis))
		{
			rezultatas += L' ';
		}
		else
		{
			rezultatas += towlower(simbolis);
		}
	}
	eilute.clear();
	eilute.str(rezultatas);
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

wstring pasalinti_galinius_skyrybos_zenklus(const wstring &zodis)
{
	size_t pabaiga = zodis.size();
	while (pabaiga > 0 && ispunct(zodis[pabaiga - 1]) && zodis[pabaiga - 1] != '/')
	{
		--pabaiga;
	}
	return zodis.substr(0, pabaiga);
}

unordered_set<wstring> nuskaityti_tld(const string &failas)
{
	unordered_set<wstring> tldSet;
	wifstream fin(failas);
	wstring eilute;
	while (getline(fin, eilute))
	{
		if (!eilute.empty() && iswalpha(eilute[0]))
		{
			transform(eilute.begin(), eilute.end(), eilute.begin(), ::towlower);
			tldSet.insert(eilute);
		}
	}
	return tldSet;
}

bool ar_tai_yra_url(const wstring &zodis, const unordered_set<wstring> &tldSet)
{
	vector<wstring> segmentai;
	wstring dabartinis;

	for (wchar_t c : zodis)
	{
		if (c == L'.')
		{
			if (!dabartinis.empty())
			{
				segmentai.push_back(dabartinis);
				dabartinis.clear();
			}
		}
		else if (!iswspace(c))
		{
			dabartinis += towlower(c);
		}
	}
	if (!dabartinis.empty())
		segmentai.push_back(dabartinis);

	if (segmentai.size() < 2)
		return false;

	for (int i = static_cast<int>(segmentai.size()) - 1; i >= 1; --i)
	{
		wstring galimasTLD = segmentai[i];
		for (int j = i - 1; j >= 0; --j)
		{
			galimasTLD = segmentai[j] + L"." + galimasTLD;
			if (tldSet.count(galimasTLD))
				return true;
		}
		if (tldSet.count(segmentai[i]))
			return true;
	}

	return false;
}

void link(set<wstring> &linkai, wstringstream &eilute, const string &url_sarasas)
{
	auto url_linkai = nuskaityti_tld(url_sarasas);

	wstring zodis;
	while (eilute >> zodis)
	{
		wstring originalus_zodis = zodis;

		while (!zodis.empty() && (zodis.back() == L'.' || zodis.back() == L','))
			zodis.pop_back();

		if (ar_tai_yra_url(zodis, url_linkai))
		{
			linkai.insert(zodis);
		}
	}
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
	unordered_set<wstring> url_linkai;
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
	link(rasti_url, buferis, url_sarasas);
	wstring zodis;
	while (buferis >> zodis)
	{
		wstring isvalytas = pasalinti_galinius_skyrybos_zenklus(zodis);
		if (ar_tai_yra_url(isvalytas, url_linkai))
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

	cout << "Rasti URL'ai įrašyti į 'OutputFailai/rastieji_url.txt'\n";
}