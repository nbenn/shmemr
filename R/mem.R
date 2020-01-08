
#' @export
new_mem <- function(length, name = rand_name(),
                    type = c("SharedMemory", "FileMemory"),
                    auto_cleanup = TRUE) {

  type <- match.arg(type)

  assert_that(is_string(name), is_string(type), is_count(length))

  res <- mem_init(name, as.numeric(length), type)

  class(res) <- c(type, "Memory")

  if (auto_cleanup) {
    reg.finalizer(.subset2(res, "ptr"), mem_release, onexit = TRUE)
  }

  res
}

mem_name <- function(x) .subset2(x, "name")

mem_length <- function(x) .subset2(x, "length")

mem_type <- function(x) .subset2(x, "type")

#' @export
mem_ptr <- function(x) {
  assert_that(is_mem(x))
  get_mem_ptr(x)
}

is_name_consistent <- function(x) {
  identical(mem_name(x), get_mem_id(x))
}

is_length_consistent <- function(x) {
  identical(mem_length(x), get_mem_length(x))
}

is_type_consistent <- function(x) {

  cls <- class(x)

  if ("Memory" %in% cls) {
    ind <- which("Memory" == cls) - 1L
    if (ind < 0L) return(identical(mem_type(x), cls[ind]))
  }

  FALSE
}

#' @export
is_mem_consistent <- function(x) {
  is_mem(x) &&
    is_name_consistent(x) &&
    is_length_consistent(x) &&
    is_type_consistent(x)
}

mem_len_print <- function(x) {
  big_mark(mem_length(x), digits = 0L, format = "f")
}
