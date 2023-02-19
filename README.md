Inainte de main:

Am scris mai multe functii: elibereaza_data, add_last, add_at, printare_inturi, find,
delete_at, print, cast_int1, cast_int2, AlocaDate si distruge_arr.
Prima functie primeste ca parametru un pointer la o structura si elibereaza memoria 
ocupata de aceasta si campurile ei.
Cele doua functii cast_int1 si cast_int2 primesc un numar ca parametru si il casteaza
in functie de tipul vrut.
AlocaDate aloca dinamic o structura data_structure, un header si un vector data->data.
Ulterior introduce in vector doua nume si doua numere, returnand un data_structure.
distruge_arr elibereaza memoria ocupata de arr.
Functia add_last adauga un element la finalul vectorului arr. Elementul este 
reprezentat de o structura head si continutul vectorului data->data.
add_at cauta pozitia in vectorul arr unde vrem sa inseram un element. Ulterior
muta elementele catre dreapta facand loc noului nostru element.
Functia printare_inturi afiseaza pe ecran numere in functie de tipul acestora
(numarul de octeti ocupati in memorie).
find parcurge vectorul data_block si printeaza informatiile care se afla pe o 
pozitie data ca parametru.
Functia delete_at sterge un element din arr si elibereaza memoria ocupata de acesta.
print functioneaza precum functia find, numai ca de data aceasta se afiseaza toate
elementele vectorului arr.

In main:

Se citeste de la tastatura rand cu rand cate o comanda. Aceasta este fragmentata
si parcursa prin strtok, fiind identificate functiile ce trebuie folosite
pentru a manipula vectorul arr. 
