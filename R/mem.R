
#' @export
new_mem <- function(length, name = rand_name(),
                    type = c("SharedMemory", "FileMemory")) {

  type <- match.arg(type)

  assert_that(is_string(name), is_string(type), is_count(length))

  res <- mem_init(name, as.numeric(length), type)

  reg.finalizer(res[["ptr"]], mem_remove, onexit = TRUE)

  structure(res, class = c(type, "Memory"))
}

#' @export
length.Memory <- get_mem_length

#' @export
`length<-.Memory` <- function(x, value) {

  assert_that(is_count(value))

  mem_resize(x, as.numeric(value))

  invisible(x)
}

#' @export
names.Memory <- function(x) get_mem_id(x)

#' @export
name <- function(x) {
  assert_that(is_mem(x))
  get_mem_id(x)
}

#' @export
mem_ptr <- function(x) {
  assert_that(is_mem(x))
  get_mem_ptr(x)
}

#' @export
str.Memory <- function(x, ...) {
  len <- big_mark(get_mem_length(x), digits = 0L, format = "f")
  cat("<Memory>\n",
      "name:    ", get_mem_id(x), "\n",
      "length:  ", len, "\n",
      "address: ", get_mem_str(x), "\n",
      "type:    ", class(x)[1L], "\n", sep = "")
}

#' @export
print.Memory <- function(x, ...) {
  len <- big_mark(get_mem_length(x), digits = 0L, format = "f")
  cat("<", class(x)[1L], "[", len, "]> ", get_mem_str(x), "\n", sep = "")
}
