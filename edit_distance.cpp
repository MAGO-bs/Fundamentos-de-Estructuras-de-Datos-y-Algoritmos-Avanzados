#include <iostream>
#include <string>

using namespace std;

int editDistance(string n, string m);

int main()
{
    string str1 = "BAJA";
    string str2 = "JOTA";
    int min = editDistance(str1, str2);
    cout << "La distancia minima es: " << min << endl;
}

int editDistance(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();

    // Casos base
    if (n == 0 || m == 0) 
        return n + m;
    else 
    {
        // Si el ultimo caracter es igual, bajamos ambos indices
        if (str1[n - 1] == str2[m - 1])
        {
            return editDistance(str1.substr(0, n - 1), str2.substr(0, m - 1));
        }
        else //En caso contrario, realizamos las operaciones y encontramos el minimo
        {
            // Caso caracteres diferentes, Insert, Delete y Replace
            int ins = editDistance(str1, str2.substr(0, m - 1));
            int del = editDistance(str1.substr(0, n - 1), str2);
            int rep = editDistance(str1.substr(0, n - 1), str2.substr(0, m - 1));

            return 1 + min(ins, min(del, rep));
        }   
    }
}