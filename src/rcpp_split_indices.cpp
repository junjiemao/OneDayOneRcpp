#include <Rcpp.h>
using namespace Rcpp;

//this example from http://gallery.rcpp.org/articles/plyr-c-to-rcpp/
//this example original from package plyr
//using C++ replace c
//using Vector Container

// [[Rcpp::export]]
std::vector<std::vector<int> > split_indices(IntegerVector x, int n=0){
  if(n < 0) stop("n must be a positive integer");  //grammar surgar
  
  std::vector<std::vector<int> > ids(n); //declare a vector and its' length is n
  
  int nx = x.size();
  for(int i = 0; i < nx; ++i){
    if(x[i] > n){
      ids.resize(x[i]); //vector's capacity--resize
      //reference:http://www.cplusplus.com/reference/vector/vector/?kw=vector
    }
    ids[x[i]-1].push_back(i+1);
  }
  return ids;
}
