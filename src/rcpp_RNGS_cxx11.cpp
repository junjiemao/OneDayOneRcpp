#include <Rcpp.h>
#include <random>
using namespace Rcpp;

//this example from http://gallery.rcpp.org/articles/timing-normal-rngs/
//using cpp11



//' @export
//' @param n
//' @param seed default value is 42
//' @title cxx11Normal
//' @name cxx11Normal
// [[Rcpp::export]]
NumericVector cxx11Normals(int n,int seed = 42){
  
  std::mt19937 engine(seed);  //declare a generator 
  std::normal_distribution<> normal(0.0, 1.0);
  
  NumericVector V(n);
  
  for(int i = 0; i < n; i++){
    V[i] = normal(engine);
  }
  return V;
}
