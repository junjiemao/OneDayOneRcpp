#include <Rcpp.h>
using namespace Rcpp;


// 本代码来源为http://gallery.rcpp.org/articles/simple-lambda-func-c++11/
// 主要是学习lamda函数
// 参考transform http://www.cplusplus.com/reference/algorithm/transform/
// 编译前设置Sys.setenv("PKG_CXXFLAGS"="-std=c++11")

// [[Rcpp::plugins("cpp11")]]

//' @export
//' @title 测试cpp中的lamda
//' @name lamda
//' @param x 需要转化的函数
// [[Rcpp::export]]
std::vector<double> transformEx(const std::vector<double>& x) {
    std::vector<double> y(x.size());
    std::transform(x.begin(), x.end(), y.begin(), 
                   [](double x) { return x*x; } );
    return y;
}


