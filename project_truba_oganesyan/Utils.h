#pragma once
#include <iostream>

using namespace std;

//#define INPUT_LINE(in, str) getline(in>>ws, str); \
//						cerr << str << endl
//
//#define PRINT_PARAM(out, x) out<< #x << "=" << x << endl

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
    cerr << x << endl;
	return x;
}

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};