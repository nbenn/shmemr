
#' @export
length.Memory <- function(x) mem_length(x)

#' @export
`length<-.Memory` <- function(x, value) {

  assert_that(is_count(value))

  mem_resize(x, as.numeric(value))

  invisible(x)
}

#' @export
names.Memory <- function(x) mem_name(x)

#' @export
`names<-.Memory` <- function(x, ...) {
  warning("Names of `Memory` objects are immutable.")
  invisible(x)
}

subset_assign <- function(x, ...) {
  warning("Indexing of `Memory` objects is not supported.")
  invisible(x)
}

#' @export
`[.Memory` <- subset_assign

#' @export
`[[.Memory` <- subset_assign

#' @export
`$.Memory` <- subset_assign

#' @export
`[<-.Memory` <- subset_assign

#' @export
`[[<-.Memory` <- subset_assign

#' @export
`$<-.Memory` <- subset_assign

#' @export
str.Memory <- function(x, ...) {
  cat("<", mem_type(x), ">\n",
      "name:    ", mem_name(x), "\n",
      "length:  ", mem_len_print(x), "\n",
      "address: ", get_mem_str(x), "\n", sep = "")
}

#' @export
print.Memory <- function(x, ...) {
  cat("<", mem_type(x), "[", mem_len_print(x), "]> ", get_mem_str(x), "\n",
      sep = "")
}
