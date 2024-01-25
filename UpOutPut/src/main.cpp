#include <Rcpp.h>
#include "getUpAndOutPut.h"

using namespace Rcpp;
using namespace std;

//' Compute Up-and-Out Put Option price with a barrier
//'
//' @param Expiry Time to Maturity
//' @param Strike Strike price
//' @param Spot Spot price
//' @param b Barrier value
//' @param Vol Volatility
//' @param r Risk-free rate
//' @param NumberOfPaths Number of Monte-Carlo paths
//' @param LengthOfPath Number of Monte-Carlo paths
//' @export
//' @examples
//' getPutPrice(0.75, 150, 140, 160, 0.24, 0.07)
// [[Rcpp::export]]
double getPutPrice(
    double Expiry = 0.75,
    double Strike = 150,
    double Spot   = 140,
    double b      = 160,
    double Vol    = 0.24,
    double r      = 0.07,
    unsigned long NumberOfPaths = 10000,
    unsigned long LengthOfPath = 10000){
  double result = getUpAndOutPut(Expiry,
                                 Strike,
                                 Spot,
                                 b,
                                 Vol,
                                 r,
                                 NumberOfPaths,
                                 LengthOfPath);

	return result;
}
