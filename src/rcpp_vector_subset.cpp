#include <Rcpp.h>
using namespace Rcpp;

//Vector Subsetting in Rcpp
//source: http://gallery.rcpp.org/articles/subsetting/

// [[Rcpp::export]]
NumericVector positives(NumericVector x){
  return x[x>0];   //use grammar sugar
}

// [[Rcpp::export]]
List first_three(List x){
  IntegerVector idx = IntegerVector::create(0,1,2);
  return x[idx]; //Note: index from 0
}

// [[Rcpp::export]]
List with_names(List x,CharacterVector y){
  return x[y];
}

