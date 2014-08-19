// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
#include <Rcpp.h>
#include <cmath>
#include <algorithm>
using namespace RcppParallel;
using namespace std;
using namespace Rcpp;

// 注意模板的使用
// 主题inline关键字的使用
template <typename InputIterator1, typename InputIterator2>
inline double kl_divergence(InputIterator1 begin1, InputIterator1 end1, 
                            InputIterator2 begin2) {
  
   // value to return
   double rval = 0;
   
   // set iterators to beginning of ranges
   InputIterator1 it1 = begin1;
   InputIterator2 it2 = begin2;
   
   // for each input item
   while (it1 != end1) {
      
      // take the value and increment the iterator
      double d1 = *it1++;
      double d2 = *it2++;
      
      // accumulate if appropirate
      if (d1 > 0 && d2 > 0)
         rval += std::log(d1 / d2) * d1;
   }
   return rval;  
}

// helper function for taking the average of two numbers
inline double average(double val1, double val2) {
   return (val1 + val2) / 2;
}


struct  JsDistance : public Worker{
  
  //原始的矩阵
  const RMatrix<double> mat;
  
  //输出的矩阵
  RMatrix<double> rmat;
  
  //构造器
  JsDistance(const NumericMatrix mat, NumericMatrix rmat)
  :mat(mat),rmat(rmat){}
  
  void operator()(std::size_t begin, std::size_t end){
    for(std::size_t i = begin; i < end; i++){
      for(std::size_t j = 0; j < i; j++){
        //
        RMatrix<double>::Row row1 = mat.row(i);
        RMatrix<double>::Row row2 = mat.row(j);
        
        //
        std::vector<double> avg(row1.length());
        std::transform(row1.begin(),row1.end(),
                       row2.begin(),
                       avg.begin(),
                       average);
        //
        double d1 = kl_divergence(row1.begin(), row1.end(), avg.begin());
        double d2 = kl_divergence(row2.begin(), row2.end(), avg.begin());
        
        //
        rmat(i,j) = sqrt(0.5*(d1 + d2));
      }
    }
  }
};


//' @export
// [[Rcpp::export]]
NumericMatrix parallelJsDistance(NumericMatrix mat){
  //
  NumericMatrix rmat(mat.nrow(),mat.nrow());
  
  //JsDistance
  JsDistance jsDistance(mat,rmat);
  
  //调用parallelFor!!!
  parallelFor(0, mat.nrow(), jsDistance);
  
  return rmat;
}


