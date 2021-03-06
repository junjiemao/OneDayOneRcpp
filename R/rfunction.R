#'@importFrom  Rcpp  evalCpp 
#'@import RcppParallel
#'@useDynLib OneDayOneRcpp
NULL  #useDynLib is import!!!

#'@export
#'@title hello world
#'@author hatmatrix42
#'@description hello world
#'@keywords helloWorld
helloWorld <- function(){
  rcpp_hello_world()
}

#'@export
#'@title vector subsetting:positives
#'@description subsetting positive number in  vector
#'@keywords subsetting vector
#'@param vector,x
subset_positives <- function(x){
  positives(x)
}

#'@export
subset_first_three <- function(x){
  first_three(x)
}

#'@export
subset_with_names <- function(x,names){
  with_names(x,names)
} 

#'@export
rcpp_split_indices <- function(group,n=0){
  split_indices(group,n)
}

#'@export
rcpp_Normals <- function(n){
  rcppNormals(n)
}
