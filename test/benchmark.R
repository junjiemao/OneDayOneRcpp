x <- runif(100000)
y <- runif(100000)

library(microbenchmark)
microbenchmark::microbenchmark(sum(x*y),
                               innerProduct(x, y),
                               parallelInnerProduct(x, y))


# create a matrix
n  = 1000
m = matrix(runif(n*10), ncol = 10)
m = m/rowSums(m)

js_distance <- function(mat) {
  kld = function(p,q) sum(ifelse(p == 0 | q == 0, 0, log(p/q)*p))
  res = matrix(0, nrow(mat), nrow(mat))
  for (i in 1:(nrow(mat) - 1)) {
    for (j in (i+1):nrow(mat)) {
      m = (mat[i,] + mat[j,])/2
      d1 = kld(mat[i,], m)
      d2 = kld(mat[j,], m)
      res[j,i] = sqrt(.5*(d1 + d2))
    }
  }
  res
}

# compare performance

microbenchmark(js_distance(m),
               parallelJsDistance(m),
               times = 10)

