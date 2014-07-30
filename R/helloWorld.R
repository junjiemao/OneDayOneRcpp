#'@export
#'@title hello world
helloWorld <- function() {
  .Call('oneDoneRcpp_rcpp_hello_world', PACKAGE = 'oneDoneRcpp')
}
