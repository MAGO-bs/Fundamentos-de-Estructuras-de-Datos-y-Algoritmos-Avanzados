#include <iostream>
#include <vector>
#include <string>
#include <random> //Para datos random
#include <fstream> //Para escritura y lectura de datos
#include <chrono> // Calculo del tiempo con alta precision

using namespace std;

string stringGenerator(int a);
int timeEvaluation(string str1, string str2);
int editDistance(string str1, string str2);
double prom(vector<int> vec, int n);
double desv_std (vector<int> vec, int n);

int main()
{
    ifstream input("secuencia_de_enteros.txt");
    if (!input.is_open())
        cerr << "No se pudo abrir el archivo" << endl;
    
    int n = 0;
    string line;

    while (getline(input, line)) {  // Obtenemos la cantidad de enteros que tenemos en nuestra secuencia
        n++;
    }

    input.clear();      // Reiniciamos el puntero para leer el archivo nuevamente desde 0 sin tener que cerrarlo
    input.seekg(0); 

    vector<int> vec(n);
    int k = 0;
    while (getline(input, line)) // Leemos para generar un vector con el que trabajaremos
    {
        vec[k] = stoi(line); // Convertimos de string a entero
        k++;
    }

    input.close();

    int exper = 50;
    vector<double> time_prom(n);
    vector<double> time_desv_std(n);
    vector<int> n_plus_m(n);
    vector<int> time_all(exper);

    string str1, str2;
    
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < exper; k++)
        {
            str1 = stringGenerator(vec[i]);     // Generamos 2 Strings aleatorios a partir de la secuencia de enteros ingresada (2 por cada entero)
            str2 = stringGenerator(vec[i]);
            time_all[k] = timeEvaluation(str1, str2); // Obtenemos el tiempo de Edit Distance dando uso de los strings del mismo largo
            cout << "El tiempo entre " << str1 << " y " << str2 << " de largo: " << str1.length() << " y " << str2.length() << " respectivamente "<< " es: " << time_all[k] << " microseg." << endl <<endl;
        }
        time_prom[i] = prom(time_all, exper);
        time_desv_std[i] = desv_std(time_all, exper);
        n_plus_m[i] = str1.length() + str2.length();
    }

    ofstream output("experimentacion.csv");
    output << "n_plus_m,time_prom[microseg.],time_desv_std[microseg.]" << endl;

    for (int i = 0; i < n; i++)
    {
        output << n_plus_m[i] << "," << time_prom[i] << "," << time_desv_std[i] << endl;
    }
    output.close();

    return 0;
}

string stringGenerator(int a)
{
    random_device rd;
    mt19937 gen(rd()); 
    string all_str("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"), result; // Generamos strings aleatorios con los caracteres descritos
    uniform_int_distribution<> distrib(0, all_str.size() - 1);

    for (int i = 0; i < a; i++)
        result += all_str[distrib(gen)];
    return result;
}

int timeEvaluation(string str1, string str2)
{   
    auto start_time = chrono::high_resolution_clock::now();     // Calculamos el tiempo total restando el tiempo posterior al edit distance menos el anterior
    int aux = editDistance(str1, str2);
    auto end_time = chrono::high_resolution_clock::now();
    double total = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout << "El minimo de operaciones es:" << aux << endl;
    return total;
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

double prom(vector<int> vec, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += vec[i];
    }   

    return sum / n; 
}

double desv_std (vector<int> vec, int n)
{
    double mean = prom(vec, n);
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (vec[i] - mean) * (vec[i] - mean);
    }   

    return sqrt(sum / (n - 1)); 
}