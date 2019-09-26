
#' @importFrom assertthat assert_that on_failure<- is.string
NULL

is_integerish <- function(x) {
  is.integer(x) || (is.numeric(x) && all(x == trunc(x)) && !is.na(x))
}

is_count <- function(x) {
  if (length(x) != 1) return(FALSE)
  if (!is_integerish(x)) return(FALSE)

  # is.na() to handle NA_integer_
  x >= 0 && !is.na(x)
}

on_failure(is_count) <- function(call, env) {
  paste0(deparse(call$x), " is not a count (a single integer >= 0)")
}

is_string <- is.string
