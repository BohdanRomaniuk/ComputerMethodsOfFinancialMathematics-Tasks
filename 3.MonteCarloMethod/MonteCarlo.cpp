#include <iostream>
#include <cmath> // standard mathematical functions
#include <algorithm> // define the max() function
#include "normdist.h"
using namespace std;

double random_uniform() 
{
	return double(rand()) / double(RAND_MAX);
};

double random_normal() 
{
	double U1, U2, V1, V2;
	double S = 2;
	while (S >= 1) 
	{
		U1 = random_uniform();
		U2 = random_uniform();
		V1 = 2.0*U1 - 1.0;
		V2 = 2.0*U2 - 1.0;
		S = pow(V1, 2) + pow(V2, 2);
	};
	double X1 = V1 * sqrt((-2.0*log(S)) / S);
	return X1;
};

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

double option_price_call_european_simulated(const double& S,
	const double& K,
	const double& r,
	const double& sigma,
	const double& time,
	const int& no_sims) {
	double R = (r - 0.5 * pow(sigma, 2))*time;
	double SD = sigma * sqrt(time);
	double sum_payoffs = 0.0;
	for (int n = 1; n <= no_sims; n++) {
		double S_T = S * exp(R + SD * random_normal());
		sum_payoffs += max(0.0, S_T-K);
	};
	return exp(r*time) * (sum_payoffs / double(no_sims));}

void main()
{
	double S = 100.0; double K = 100.0; double r = 0.1; double sigma = 0.25;
	double time = 1.0; int no_sims = 5000;
	cout << "call black scholes price = " << option_price_call_black_scholes(S, K, r, sigma, time) << endl;
	cout << "call simulated price     = " << option_price_call_european_simulated(S, K, r, sigma, time, no_sims) << endl;
	system("pause");
}