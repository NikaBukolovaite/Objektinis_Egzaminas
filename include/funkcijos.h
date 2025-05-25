#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "santrauka.h"

const string aplankalo_pavadinimas = "NuskaitymoFailai";
string koki_faila_nuskaityti();
string skyrybos_zenklai(const string &zodis);
void suskaiciuoti_kiek_zodziu_ir_irasyti_rezultata(const string &failo_pavadinimas);
void cross_reference_lentele(const string &failo_pavadinimas);
string gauti_url_link(const string &zodis);
string pasalinti_galinius_skyrybos_zenklus(const string &zodis);
bool ar_zodis_yra_url(const string &zodis, const set<string> &url_linkai);
void rasti_visus_galimus_url(const string &teksto_failas, const string &url_sarasas);

#endif