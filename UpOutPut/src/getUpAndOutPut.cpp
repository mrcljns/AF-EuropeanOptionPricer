#include "getUpAndOutPut.h"
#include "getOneGaussianByBoxMueller.h"
#include <cmath>
#include <vector>
#include <Rcpp.h>
#include<iostream>

// definition of the function
double getUpAndOutPut(double Expiry, // Time to maturity
                      double Strike, // Strike price
                      double Spot, // Spot price
                      double b, // Barrier
                      double Vol, // Annualized volatility rate
                      double r, // Annualized risk-free rate
                      unsigned long int NumberOfPaths, // Number of Monte Carlo Simulations
                      unsigned long int LengthOfPath // Length of one simulation
                      ){

	double variance = Vol * Vol * Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5 * variance;
	double thisDrift = (r * Expiry + itoCorrection)/double(LengthOfPath);
	std::vector<double> thisSpotArray;
	double cumSum;
	double runningSum = 0;
	double thisSpot;
	double thisGaussian;

	// Create each simulation in a loop
	for (unsigned long i = 0; i < NumberOfPaths; i++) {
	  thisSpotArray.push_back(Spot);
	  cumSum = 0;
	  thisSpotArray.clear();
	  // Generate movement of the spot price
	  for (unsigned long j = 0; j < LengthOfPath; j++){
	    thisGaussian = getOneGaussianByBoxMueller();
	    cumSum += thisDrift + rootVariance * sqrt(Expiry/double(LengthOfPath)) * thisGaussian;
	    thisSpotArray.push_back(Spot * exp(cumSum));
	  }
	  // Get the maximum value the spot price has reached
	  double maxSpot = *std::max_element(thisSpotArray.begin(), thisSpotArray.end());
	  // This is an European option, so it can only be exercised at exercise date
	  // The last spot value must be taken to calculate the payoff
	  thisSpot = thisSpotArray.back();
		double thisPayoff = Strike - thisSpot;
		// If at any point the spot price exceeded the barrier than the payoff is 0
		// If the payoff is lower than 0 then the option will not be exercised (so payoff is 0)
  	if (thisPayoff>0 && maxSpot <= b) runningSum += thisPayoff;
	}

	// Calculate the mean of all results
	double mean = runningSum / double(NumberOfPaths);
	mean = mean * exp(-r * Expiry);
	return mean;
}
