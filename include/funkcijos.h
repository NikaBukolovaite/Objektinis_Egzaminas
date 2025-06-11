#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "santrauka.h"

const string aplankalo_pavadinimas = "NuskaitymoFailai";
string koki_faila_nuskaityti();
wstring skyrybos_zenklai(const string &zodis);
void eilute(wstringstream &eilute);
wstring pasalinti_galinius_skyrybos_zenklus(const wstring &zodis);
void suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(const string &failo_pavadinimas);
void cross_reference_lentele(const string &failo_pavadinimas);
unordered_set<wstring> nuskaityti_tld(const string &failas);
bool ar_tai_yra_url(const wstring &zodis, const unordered_set<wstring> &tldSet);
void link(set<wstring> &linkai, wstringstream &eilute, const string &url_sarasas);
void rasti_visus_galimus_url(const string &teksto_failas, const string &url_sarasas);

#endif