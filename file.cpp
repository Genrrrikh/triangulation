#include <cstdlib>
#include <iostream>
#include <fstream> // работа с файлами
#include <iomanip> // манипуляторы ввода/вывода
#include <math.h>
using namespace std;
 
int main(int argc, char* argv[])
{



    	
	setlocale(LC_ALL, "rus");
 
    // связываем объект с файлом, при этом файл открываем в режиме записи, предварительно удаляя все данные из него
    ofstream fout("data_types.txt", ios_base::out | ios_base::trunc);
 
    if (!fout.is_open()) // если файл небыл открыт
    {
     cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщение
     return 1; // выполнить выход из программы
    }
 
 int randomDigit;

        for (int i = 0; i < 666; i++)
        {
                randomDigit = rand(); // запись случайного числа, которое вернет rand
        	fout << (randomDigit/100000000) << "." << (randomDigit % 10000) << endl;
	}
	
	for (int i = 0; i < 333; i++)
        {
                randomDigit = rand(); // запись случайного числа, которое вернет rand
                fout << (randomDigit/1000000000) << "." << (randomDigit % 10000) << endl;
        }


	

        
        fout.close(); 
    system("pause");
    return 0;


}
