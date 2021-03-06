// CoinCalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>

using std::cout;
using std::endl;
using std::cin;

int checkDIFF(int cost, int base);

int main()
{
	std::string input;

	double cost;
	double change;

	int intcost = 0;
	int centcost = 0;

	struct
	{
		int b = 0;
		int q = 0;
		int d = 0;
		int n = 0;
		int c = 0;
	} pay;

	cout << "Enter cost: $";
	cin >> input;

	int l = input.length();
	for (int i = 0; i < l; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] != '\0')
				centcost += (input[i + 1] - '0') * 10;
			if (input[i + 2] != '\0')
			{
				centcost += (input[i + 2] - '0');
				if (input[i + 2] != 0)
					intcost /= 10;
			}
				
			i = l - 1;
		}
		else {
			int cur = input[i] - '0';
			intcost += (cur * pow(10, l - 2 - i)) * 10;
			if (input[i + 1] == '\0')
			{
				intcost *= 100;
			}
		}
	}
	intcost += centcost;

	cost = intcost;
	cost /= 100;

	cout << "Calculating optimal pay for $" << std::fixed << std::setprecision(2) << cost << "..." << endl << endl;

	if (intcost % 100 == 0)
	{
		pay.b = intcost / 100;
	}
	else if (intcost % 25 == 0)
	{
		if (centcost <= 50)
		{
			pay.b = intcost / 100;
			pay.q = centcost / 25;
		}
		else {
			pay.b = intcost / 100 + 1;
			pay.q = 4 - (centcost / 25);
		}
		
	}
	else if (intcost % 10 == 0)
	{
		if (checkDIFF(intcost, 25) <= 10)
		{
			pay.b = intcost / 100;
			pay.q = (centcost - checkDIFF(intcost, 25)) / 25;
			pay.d = checkDIFF(intcost, 25) / 10;
			pay.n = checkDIFF(intcost, 25) / 5 - (pay.d * 2);
		}
		else {
			pay.b = intcost / 100;
			if (centcost == 20)
				pay.d = 2;
			else
				pay.q = (centcost - checkDIFF(intcost, 25) / 25) + 1;
		}
	}

	if (pay.c == 5)
	{
		pay.n++;
		pay.c = 0;
	}
	if (pay.n == 2)
	{
		pay.d++;
		pay.n = 0;
	}
	if (pay.q == 4)
	{
		pay.b++;
		pay.q = 0;
	}
	
	



	//1.40, 1.5
	//0.91, 1.01 -> 0.10
	//15.50

	cout << "Optimal pay = ";

	if (pay.b > 0)
	{
		cout << pay.b << " bills, ";
	}
	if (pay.q > 0)
	{
		cout << pay.q << " quarters, ";
	}
	if (pay.d > 0)
	{
		cout << pay.d << " dimes, ";
	}
	if (pay.n > 0)
	{
		cout << pay.n << " nickels, ";
	}
	if (pay.c > 0)
	{
		cout << pay.c << " cents, ";
	}

	change = pay.b + pay.q*0.25 + pay.d*0.1 + pay.n*0.05 + pay.c*0.01 - cost;

	cout << "Change: $" << change << endl << endl;

	main();
    return 0;
}

int checkDIFF(int cost, int base)
{
	int int_cost = (cost / base)*base;
	return (cost - int_cost);
}


