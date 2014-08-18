x <- runif(100000)
y <- runif(100000)

library(microbenchmark)
microbenchmark::microbenchmark(sum(x*y),
                               innerProduct(x, y),
                               parallelInnerProduct(x, y))