#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double Prost_iter_x(double x)
{
	return pow(5. * x * x - 4. * x - 0.092, 1./3.);
}

double Relax_x(double x)
{
	return (pow(x, 3) - 5 * x * x + 4 * x + 0.092);
}

double Relax_poh_x(double x)
{
	return (3 * x * x - 10 * x + 4);
}

double Relax_iter_x(double x, double tay)
{
	return (x - tay * Relax_x(x));
}

void Prost_it(double poch)
{
	cout << "Метод простої iтерацiї" << endl;
	double ee = pow(10, -4);
	double iter = poch;
	cout << "._______________._______________." << endl;
	cout << "|" << setw(15) << "---" << "|"
		<< setw(15) << iter << "|" << endl;
	cout << "|" << setw(15) << fabs(iter - Prost_iter_x(iter)) << "|"
		<< setw(15) << Prost_iter_x(iter) << "|" << endl;
	iter = Prost_iter_x(iter);
	int i = 1;
	while (fabs(iter - Prost_iter_x(iter)) > ee)
	{
		cout << "|" << setw(15) << fabs(iter - Prost_iter_x(iter));
		iter = Prost_iter_x(iter);
		cout << "|" << setw(15) << iter << "|" << endl;
		i++;
	}
	cout << "|" << setw(15) << fabs(iter - Prost_iter_x(iter));
	iter = Prost_iter_x(iter);
	cout << "|" << setw(15) << iter << "|" << endl;
	i++;
	cout << "._______________._______________." << endl;
	double q = 0.792;
	double x0 = poch;
	int apriorna_ots = (log(fabs(Prost_iter_x(x0) - x0) /
		((1. - q) * ee)) / log(1. / q)) + 1;
	cout << "Апрiорна оцiнка = " << apriorna_ots << endl;
	cout << "Апостерiорна оцiнка = " << i << endl;
}

void Relax_it(double poch)
{
	cout << "Метод метод релаксацiї" << endl;
	double ee = pow(10, -4);
	double M = Relax_poh_x(3.5);
	double m = Relax_poh_x(4.5);
	double tay = (2 / (Relax_poh_x(3.5) +
		Relax_poh_x(4.5)));
	double iter = poch;
	cout << "._______________._______________." << endl;
	cout << "|" << setw(15) << "---" << "|"
		<< setw(15) << iter << "|" << endl;
	cout << "|" << setw(15) << fabs(iter - Relax_iter_x(iter, tay)) << "|"
		<< setw(15) << Relax_iter_x(iter, tay) << "|" << endl;
	iter = Relax_iter_x(iter, tay);
	int i = 1;
	while (fabs(iter - Relax_iter_x(iter, tay)) > ee)
	{
		cout << "|" << setw(15) << fabs(iter - Relax_iter_x(iter, tay));
		iter = Relax_iter_x(iter, tay);
		cout << "|" << setw(15) << iter << "|" << endl;
		i++;
	}
	cout << "|" << setw(15) << fabs(iter - Relax_iter_x(iter, tay));
	iter = Relax_iter_x(iter, tay);
	cout << "|" << setw(15) << iter << "|" << endl;
	i++;
	cout << "._______________._______________." << endl;
	double x_so_swo = max(fabs(poch - 4.5), fabs(poch - 3.5));
	double q0 = ((Relax_poh_x(4.5) -
		Relax_poh_x(3.5)) /
		(Relax_poh_x(3.5) +
			Relax_poh_x(4.5)));
	int apriorna_ots = (log(x_so_swo / ee) / log(1. / q0)) + 1;
	cout << "Апрiорна оцiнка = " << apriorna_ots << endl;
	cout << "Апостерiорна оцiнка = " << i << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double x0;
	cout << "Введiть початкову точку: ";
	cin >> x0;
	Prost_it(x0);
	cout << "-------------------------------------" << endl;
	Relax_it(x0);
	system("pause");
}