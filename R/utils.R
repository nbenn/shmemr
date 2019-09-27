
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

#' @export
is_mem <- function(x) inherits(x, "Memory")

on_failure(is_mem) <- function(call, env) {
  paste0(deparse(call$x), " is not a Memory object")
}

big_mark <- function(x, ...) {
  mark <- if (identical(getOption("OutDec"), ",")) "." else ","
  formatC(x, big.mark = mark, ...)
}

rand_name <- function(length = 15L, chars = c(letters, LETTERS, 0L:9L)) {

  assert_that(
    is_count(length), is.character(chars), length(chars) >= 1L
  )

  paste(sample(chars, length, replace = TRUE), collapse = "")
}
