#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double option_price_call_european_binomial(const double& S, // spot price
	const double& K, // exercice price
	const double& r, // interest rate
	const double& sigma, // volatility
	const double& t, // time to maturity
	const int& steps)
{
	double R = exp(r*(t / steps)); // interest rate for each step
	double Rinv = 1.0 / R; // inverse of interest rate
	double u = exp(sigma*sqrt(t / steps)); // up movement
	double uu = u * u;
	double d = 1.0 / u;
	double p_up = (R - d) / (u - d);
	double p_down = 1.0 - p_up;
	vector<double> prices(steps + 1); // price of underlying
	prices[0] = S * pow(d, steps); // fill in the endnodes.
	for (int i = 1; i <= steps; ++i)
	{
		prices[i] = uu * prices[i - 1];
	}
	vector<double> call_values(steps + 1); // value of corresponding call
	for (int i = 0; i <= steps; ++i)
	{
		call_values[i] = max(0.0, (prices[i] - K)); // call payoffs at maturity
	}
	for (int step = steps - 1; step >= 0; --step)
	{
		for (int i = 0; i <= step; ++i)
		{
			call_values[i] = (p_up*call_values[i + 1] + p_down * call_values[i])*Rinv;
		};
	};
	return call_values[0];
}

double option_price_call_american_binomial(const double& S,
	const double& K,
	const double& r,
	const double& sigma,
	const double& t,
	const int& steps)
{
	double R = exp(r*(t / steps));
	double Rinv = 1.0 / R;
	double u = exp(sigma*sqrt(t / steps));
	double d = 1.0 / u;
	double p_up = (R - d) / (u - d);
	double p_down = 1.0 - p_up;
	vector<double> prices(steps + 1); // price of underlying
	prices[0] = S * pow(d, steps); // fill in the endnodes.
	vector<double> prices1(steps + 1); // price of underlying
	double uu = u * u;
	for (int i = 1; i <= steps; ++i)
	{
		prices[i] = uu * prices[i - 1];
		prices1[i] = prices[i];
	}
	vector<double> call_values(steps + 1); // value of corresponding call
	for (int i = 0; i <= steps; ++i)
	{
		call_values[i] = max(0.0, (prices[i] - K)); // call payoffs at maturity
	}
	for (int step = steps - 1; step >= 0; --step)
	{
		for (int i = 0; i <= step; ++i)
		{
			call_values[i] = (p_up*call_values[i + 1] + p_down * call_values[i])*Rinv;
			prices[i] = d * prices[i + 1];
			call_values[i] = max(call_values[i], prices[i] - K); // check for exercise
		};

	};
	
	return call_values[0];
}

void main()
{
	double S = 100.0; double K = 100.0;
	double r = 0.1; double sigma = 0.25;
	double time = 1.0; int no_steps = 100;
	cout << "European call = " << option_price_call_european_binomial(S, K, r, sigma, time, no_steps) << endl;
	cout << "American call = " << option_price_call_american_binomial(S, K, r, sigma, time, no_steps) << endl;

	/*for (int i = 0; i <= no_steps; ++i)
	{
		auto res = option_price_call_european_binomial(S, K, r, sigma, time, no_steps);
		time += 1;
		cout << "[" << i << ", " << res << "]," << endl;
	}*/
	system("pause");
}