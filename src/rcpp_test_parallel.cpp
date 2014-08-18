#include <Rcpp.h>
using namespace Rcpp;


// 例子来源http://gallery.rcpp.org/articles/parallel-inner-product/
// 测试并行特性



//' @export
//' @name innerProduct
//' @title 内积的cpp版本
//' @param x 向量x
//' @param y 向量y
// [[Rcpp::export]]
double innerProduct(NumericVector x,NumericVector y){
  //串行版本
  return std::inner_product(x.begin(), x.end(), y.begin(),0.0);
  //http://www.cplusplus.com/reference/numeric/inner_product/
}






