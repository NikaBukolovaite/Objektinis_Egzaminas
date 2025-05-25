# Objektinio programavimo priešegzamininė užduotis

# 📝 Programos aprašymas

Ši programa yra skirta analizuoti tekste esančių žodžių dažnumą, poziciją tekste (kurioje eilutėje tas tikras žodis yra) ir nuorodų radimą.

# 🛠️ Kompiliavimo instrukcijos

1. Atsiųsti [Visual Studio C++ kompiliatorių](https://visualstudio.microsoft.com/downloads/)
2. Atsisiųsti [CMake (Bent v. 3.25)](https://cmake.org/download/)
3. Klonuoti projekto direktoriją `git clone https://github.com/NikaBukolovaite/Objektinis_Egzaminas.git` (arba Download zip)
4. Atsidaryti komandinę eilutę (cmd arba powershell) ir į ją įvesti
   `cmake -G "Visual Studio 17 2022"; rm build -Recurse -Force ; cmake -B build -S . ; cmake --build build `
5. Atsidaryti komandinę eilutę projeto direktorijoje ir, kad paleisti programą įvesti: `.\build\Debug\main.exe`.

# 💻 Kompiuterio charakteristikos

| Komponentas |      Specifikacija      |
| :---------- | :---------------------: |
| CPU         | AMD Ryzen 5 4600H </br> |
| RAM         |     8GB DDR4 </br>      |
| DISK        |    SSD (NVMe) </br>     |

# 📃 Programos naudojimosi instrukcijos

1. Prieš paleidžiant programą, savo projekte reikia susikurti du aplankus:
   "NuskaitymoFailai" – į kurį keliami visi tekstai, kurie gali būti analizuojami.
   "OutputFailai" – į kurį bus automatiškai sukuriami rezultatų failai: "cross_reference.txt", "rastieji_url" ir "zodziu_dazniai".

2. Paleidus programą, bus pasiūlyta pasirinkti vieną iš failų esančių "NuskaitymoFailai" aplankale. Pasirinktas failas bus nuskaitytas ir automatiškai panaudotas žodžių dažnio, vietos bei nuorodų analizavimui.

3. Visų rezultatų failai atsiras "OutputFailai" aplankale.

# Programos funkcijos

## string koki_faila_nuskaityti()

Leidžia vartotojui pasirinkti vieną .txt failą iš aplankalo "NuskaitymoFailai".

## string skyrybos_zenklai(const string &zodis)

Pašalina skyrybos ženklus ir skaičius iš žodžio, kad galima būtų išvalyti tekstą ir palikti tik žodžius.

## void suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(const string &failo_pavadinimas)

Suskaičiuoja kiekvieno žodžio dažnį ir įrašo rezultatus į OutputFailai/zodziu_dazniai.txt.

## void cross_reference_lentele(const string &failo_pavadinimas)

Sugeneruoja lentelę, kur nurodoma, kuriose eilutėse pasikartoja žodžiai. Rezultatas saugomas OutputFailai/cross_reference.txt.

## string gauti_url_link(const string &zodis);

Bando ištraukti TLD galūnę iš žodžio (pvz., iš vu.lt gautų lt).

## string pasalinti_galinius_skyrybos_zenklus(const string &zodis);

Pašalina skyrybos ženklus nuo žodžio pabaigos (pvz., vu.lt, → vu.lt).

## bool ar_zodis_yra_url(const string &zodis, const set<string> &url_linkai);

Patikrina, ar žodis yra URL – pagal domeno galūnes ir struktūrą (pvz., http://, www. ir pan.).

## void rasti_visus_galimus_url(const string &teksto_failas, const string &url_sarasas)

Ieško visų galimų URL nuorodų iš teksto ir įrašo jas į OutputFailai/rastieji_url.txt.
