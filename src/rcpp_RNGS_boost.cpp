#include <Rcpp.h>
#include <random>

#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/normal_distribution.hpp>

using namespace Rcpp;
using namespace std;

//this example from http://gallery.rcpp.org/articles/timing-normal-rngs/
//using boost library
// 

//' @export
//' @param n 测试下中文呢
//' @title boostNormals 
//' @name boostNormals 
// [[Rcpp::export]]
NumericVector boostNormals(int n){
  typedef boost::mt19937 RNGType; //选择随机数生成器
  RNGType rng(42);  //set seed and instantiate
  
  boost::normal_distribution<> n01(0.0, 1.0);  
  boost::variate_generator< RNGType, boost::normal_distribution<> > rngNormal(rng,n01); 
  
  NumericVector V(n);
  for(int i = 0;i < n; i++){
    V[i] = rngNormal();
  }
   return V;
}


