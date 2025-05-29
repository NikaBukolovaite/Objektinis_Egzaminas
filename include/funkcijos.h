#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "santrauka.h"

const string aplankalo_pavadinimas = "NuskaitymoFailai";
string koki_faila_nuskaityti();
wstring skyrybos_zenklai(const string &zodis);
void suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(const string &failo_pavadinimas);
void cross_reference_lentele(const string &failo_pavadinimas);
wstring gauti_url_link(const wstring &zodis);
wstring pasalinti_galinius_skyrybos_zenklus(const wstring &zodis);
bool ar_zodis_yra_url(const wstring &zodis, const set<wstring> &url_linkai);
void rasti_visus_galimus_url(const string &teksto_failas, const string &url_sarasas);

#endif