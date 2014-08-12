#include <Rcpp.h>
using namespace Rcpp;

//this example from http://gallery.rcpp.org/articles/timing-normal-rngs/
//

// [[Rcpp::export]]
NumericVector rcppNormals(int n){
  RNGScope scope;   //set seed!! but it works without this 
  return rnorm(n);
}
