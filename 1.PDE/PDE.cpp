#include <iostream>
#include <cmath>
#include "normdist.h"
using namespace std;

double option_price_call_black_scholes(const double& S, // spot (underlying) price
	const double& K, // strike (exercise) price,
	const double& r, // interest rate
	const double& sigma, // volatility
	const double& time) { // time to maturity
	double time_sqrt = sqrt(time);
	double d1 = (log(S / K) + r * time) / (sigma*time_sqrt) + 0.5*sigma*time_sqrt;
	double d2 = d1 - (sigma*time_sqrt);
	return S * N(d1) - K * exp(-r * time)*N(d2);
};

double option_price_put_black_scholes(const double& S, // spot (underlying) price
	const double& K, // strike (exercise) price,
	const double& r, // interest rate
	const double& sigma, // volatility
	const double& time) { // time to maturity
	double time_sqrt = sqrt(time);
	double d1 = (log(S / K) + r * time) / (sigma*time_sqrt) + 0.5*sigma*time_sqrt;
	double d2 = d1 - (sigma*time_sqrt);
	return K * exp(-r * time)*N(-d2) - S * N(-d1);
};

void main()
{
	double S = 50; double K = 50; double r = 0.10;
	double sigma = 0.30; double time = 0.50;
	cout << "Black Scholes call price = ";
	cout << option_price_call_black_scholes(S, K, r, sigma, time) << endl;
	cout << "Black Scholes put price = ";
	cout << option_price_put_black_scholes(S, K, r, sigma, time) << endl;

	/*for (int i = 0; i <= 100; ++i)
	{
		auto res = option_price_call_black_scholes(S, K, r, sigma, time);
		time += 1;
		cout << "[" << i << ", " << res << "]," << endl;
	}*/
	system("pause");
}



