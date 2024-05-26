#include <iostream>
using namespace std;

class Kolejka {
private:
    int* tab;
    int poczatek, koniec, rozmiar, pojemnosc;

public:
    Kolejka(int max_rozmiar) {
        pojemnosc = max_rozmiar;
        tab = new int[pojemnosc];
        poczatek = 0;
        koniec = -1;
        rozmiar = 0;
    }

    ~Kolejka() {
        delete[] tab;
    }

    bool czyPusta() {
        return rozmiar == 0;
    }

    bool czyPelna() {
        return rozmiar == pojemnosc;
    }

    void dodaj(int wartosc) {
        if (!czyPelna()) {
            koniec = (koniec + 1) % pojemnosc;
            tab[koniec] = wartosc;
            rozmiar++;
        }
    }

    void usun() {
        if (!czyPusta()) {
            poczatek = (poczatek + 1) % pojemnosc;
            rozmiar--;
        }
    }

    int przod() {
        if (!czyPusta()) {
            return tab[poczatek];
        }
        return -1;
    }
};
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void merge2(int arr[], int arr2[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* L2 = new int[n1];
    int* R = new int[n2];
    int* R2 = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        L2[i] = arr2[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        R2[j] = arr2[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] > R[j]) { // Zmieniono na L[i] > R[j]
            arr[k] = L[i];
            arr2[k] = L2[i];
            i++;
        } else if (L[i] < R[j]) { // Zmieniono na L[i] < R[j]
            arr[k] = R[j];
            arr2[k] = R2[j];
            j++;
        } else {
            // Jeśli wartości są sobie równe, to mniejszy numer z drugiej tablicy
            // zostanie przypisany szybciej
            if (L2[i] < R2[j]) {
                arr[k] = L[i];
                arr2[k] = L2[i];
                i++;
            } else {
                arr[k] = R[j];
                arr2[k] = R2[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        arr2[k] = L2[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        arr2[k] = R2[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] L2;
    delete[] R;
    delete[] R2;
}

void mergeSort2(int arr[], int arr2[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort2(arr, arr2, left, mid);
        mergeSort2(arr, arr2, mid + 1, right);
        merge2(arr, arr2, left, mid, right);
    }
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    int* L = new int[n1];
    int* R = new int[n2];


    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];


    int i = 0;
    int j = 0;
    int k = left;


    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }


    delete[] L;
    delete[] R;
}


void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;


        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);


        merge(arr, left, mid, right);
    }
}
class Graf{
private:
    long long int rzadGrafu=0;
    int *sasiedzi = nullptr;
    int **wierzcholki= nullptr;
    int *odwiedzone = nullptr;
    long long int krawedzie=0;
    int* posortowaneWierzcholki = nullptr;
public:
    Graf(){
        cin >> rzadGrafu;
        sasiedzi = new int[rzadGrafu];
        wierzcholki = new int*[rzadGrafu];
        odwiedzone = new int[rzadGrafu];
        posortowaneWierzcholki = new int[rzadGrafu];
        for(int i=0;i<rzadGrafu;i++)
        {
            cin >> sasiedzi[i];
            wierzcholki[i]=new int[sasiedzi[i]];
            for(int j=0;j<sasiedzi[i];j++)
            {
                cin >> wierzcholki[i][j];
                wierzcholki[i][j]--;
                krawedzie++;
            }
            posortowaneWierzcholki[i]=i;
        }
        krawedzie/=2;

    }
    void liczeniegrafu(){
        ciag_stopniowy();
        liczba_skladowych_grafu();
        dwudzielnosc_grafu();
        acentrycznosc_wierzchokow();
        planarnosc_grafu();
        kolory_wierzcholkow_zachlanny();
        kolory_wierzcholkow_LF();
        kolory_wierzcholkow_SLF();
        liczba_roznych_podgrafow_C4();
        liczba_krawedzi_dopelniania_grafu();
    }
    void DFS(int wierzcholek){
        if(odwiedzone[wierzcholek]==0)
        {
            odwiedzone[wierzcholek]=1;
            for(int i=0;i<sasiedzi[wierzcholek];i++)
            {
                DFS(wierzcholki[wierzcholek][i]);
            }
        }
    }
    void ciag_stopniowy(){


        int* sasiedziKopia = new int[rzadGrafu];
        for(int i = 0; i < rzadGrafu; i++) {
            sasiedziKopia[i] = sasiedzi[i];
        }

        // Sortujemy posortowane wierzchołki rosnąco według ich numerów

        mergeSort2(sasiedziKopia,posortowaneWierzcholki, 0, rzadGrafu - 1);

        for(int i = 0; i < rzadGrafu; i++) {
            cout << sasiedziKopia[i] << " ";
        }
        cout << endl;
        delete [] sasiedziKopia;
    }
    void liczba_skladowych_grafu(){
        int wynik=0;
        for(int i=0;i<rzadGrafu;i++)
        {
            odwiedzone[i]=0;
        }
        for(int i=0;i<rzadGrafu;i++)
        {
            if(odwiedzone[i]==0) {



                wynik++;
            }
            DFS(i);
        }
        cout << wynik << endl;
    }
    void dwudzielnosc_grafu(){
        int* kolor = new int[rzadGrafu];
        for (int i = 0; i < rzadGrafu; i++) {
            kolor[i] = -1;
        }

        bool jestDwudzielny = true;

        for (int start = 0; start < rzadGrafu && jestDwudzielny; start++) {
            if (kolor[start] == -1) {
                Kolejka q(rzadGrafu);
                q.dodaj(start);
                kolor[start] = 0;

                while (!q.czyPusta() && jestDwudzielny) {
                    int v = q.przod();
                    q.usun();

                    for (int i = 0; i < sasiedzi[v]; i++) {
                        int sasiad = wierzcholki[v][i];
                        if (kolor[sasiad] == -1) {
                            kolor[sasiad] = 1 - kolor[v];
                            q.dodaj(sasiad);
                        } else if (kolor[sasiad] == kolor[v]) {
                            jestDwudzielny = false;
                            break;
                        }
                    }
                }
            }
        }

        cout << (jestDwudzielny ? "T" : "F") << endl;
        delete[] kolor;
    }
    void acentrycznosc_wierzchokow(){
        cout << "?"<< endl;
    }
    void planarnosc_grafu(){
        cout << "?"<< endl;
    }

    void kolory_wierzcholkow_zachlanny(){

        int* kolor = new  int[rzadGrafu];
        for (int i = 0; i < rzadGrafu; i++) {
            kolor[i] = 0;
        }


        for (int v = 0; v < rzadGrafu; v++) {

            bool* kategorie_uzyte = new bool[rzadGrafu];
            for (int i = 0; i < rzadGrafu; i++) {
                kategorie_uzyte[i] = false;
            }


            for (int i = 0; i < sasiedzi[v]; i++) {
                int sasiad = wierzcholki[v][i];
                if (kolor[sasiad] > 0) {
                    kategorie_uzyte[kolor[sasiad] - 1] = true;
                }
            }


            for (int i = 0; i < rzadGrafu; i++) {
                if (!kategorie_uzyte[i]) {
                    kolor[v] = i + 1;
                    break;
                }
            }

            delete[] kategorie_uzyte;
        }


        for (int i = 0; i < rzadGrafu; i++) {
            cout << kolor[i] << " ";
        }
        cout << endl;

        delete[] kolor;

    }

    void kolory_wierzcholkow_LF() {
        int* kolor = new int[rzadGrafu];
        for (int i = 0; i < rzadGrafu; i++) {
            kolor[i] = 0;
        }

        for (int index = 0; index < rzadGrafu; index++) {
            int v = posortowaneWierzcholki[index]; // Indeks wierzchołka do pokolorowania

            bool* kategorie_uzyte = new bool[rzadGrafu];
            for (int i = 0; i < rzadGrafu; i++) {
                kategorie_uzyte[i] = false;
            }

            for (int i = 0; i < sasiedzi[v]; i++) {
                int sasiad = wierzcholki[v][i];
                if (kolor[sasiad] > 0) {
                    kategorie_uzyte[kolor[sasiad] - 1] = true;
                }
            }

            for (int i = 0; i < rzadGrafu; i++) {
                if (!kategorie_uzyte[i]) {
                    kolor[v] = i + 1; // Kolorujemy wierzchołek v kolorem i+1
                    break;
                }
            }

            delete[] kategorie_uzyte;
        }

        // Wyświetlamy kolory wierzchołków
        for (int i = 0; i < rzadGrafu; i++) {
            cout << kolor[i] << " ";
        }
        cout << endl;

        // Zwolnienie pamięci
        delete[] kolor;
       
    }
    void kolory_wierzcholkow_SLF(){
        cout << "?" << endl;
    }
    void liczba_roznych_podgrafow_C4(){
        cout << "?" << endl;
    }
    void liczba_krawedzi_dopelniania_grafu(){
        long long int wynik;
        wynik = rzadGrafu*(rzadGrafu-1)/2 - krawedzie;
        cout << wynik << endl;

    }

    void print(){
        cout << rzadGrafu << endl;
        for(int i=0;i<rzadGrafu;i++)
        {
            cout << sasiedzi[i] << " ";
            for(int j=0;j<sasiedzi[i];j++)
            {
                cout << wierzcholki[i][j] << " ";
            }
            cout << endl;
        }
    }
    ~Graf(){
        for(int i=0;i<rzadGrafu;i++)
        {
            delete [] wierzcholki[i];
        }
        delete [] wierzcholki;
        delete [] sasiedzi;
    }

};
int main() {
    int liczbagrafow;
    cin >> liczbagrafow;
    for(int i=0;i<liczbagrafow;i++)
    {
        Graf graf;
        graf.liczeniegrafu();

    }

    return 0;
}
