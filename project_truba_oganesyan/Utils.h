#pragma once
#include <iostream>

using namespace std;

template <typename T>
T GetCorrectData(T min, T max)
{
	T x;
	while ((cin >> x).fail() || (cin).peek() != '\n' || x < min || x > max)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nEnter the correct data! Type number (" << min << " - " << max << "):";
		cout << "\nEnter: ";
	}
	return x;
}

template <typename T>
void logging_cout(const T& output)
{
    ofstream log_file("logging.txt", ios::app);
    if (log_file.is_open())
    {
        log_file << output << endl;
        log_file.close();
    }
    cout << output << endl;
}

template <typename T>
void logging_cin(const T& output)
{
    ofstream log_file("logging.txt", ios::app);
    if (log_file.is_open())
    {
        log_file << output << endl;
        log_file.close();
    }
}