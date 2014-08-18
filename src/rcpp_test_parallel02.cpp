// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace RcppParallel;
using namespace std;
using namespace Rcpp;

struct InnerProduct : public Worker
{   
   // 原始向量
   const RVector<double> x;
   const RVector<double> y;
   
   // 已经计算好的积（中间的值）
   double product;
   
   // constructors  构造函数后面的冒号起分割作用，是类给成员变量赋值的方法
   // 参考http://blog.csdn.net/zimingjushi/article/details/6549390
   InnerProduct(const NumericVector x, const NumericVector y) 
      : x(x), y(y), product(0) {}
   InnerProduct(const InnerProduct& innerProduct, Split) 
      : x(innerProduct.x), y(innerProduct.y), product(0) {}
   
   // 计算分割以后范围中的值
   // 这里重载了()
   void operator()(std::size_t begin, std::size_t end) {
      product += std::inner_product(x.begin() + begin, 
                                    x.begin() + end, 
                                    y.begin() + begin, 
                                    0.0);
   }
   
   // 把算到的值合并起来，这里join的用法
   void join(const InnerProduct& rhs) { 
     product += rhs.product; 
   }
};


//' @export
//' @title 内积的并行版本
//' @param x,向量x
//' @param y,向量y
//' @name parallelInnerProduct
// [[Rcpp::export]]
double parallelInnerProduct(NumericVector x, NumericVector y) {
   
   // 声明InnerProduct
   InnerProduct innerProduct(x, y);
   
   // 调用paralleReduce
   parallelReduce(0, x.length(), innerProduct);
   
   // return the computed product
   return innerProduct.product;
}
