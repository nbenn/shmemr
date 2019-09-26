
#' @export
new_mem <- function(length, name = rand_name(),
                    type = c("SharedMemory", "FileMemory")) {

  type <- match.arg(type)

  assert_that(is_string(name), is_string(type), is_count(length))

  ptr <- mem_init(name, as.numeric(length), type)

  reg.finalizer(ptr, mem_remove, onexit = TRUE)

  structure(ptr, class = c(type, "Memory"))
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
  get_mem_address(x)
}

#' @export
str.Memory <- function(x, ...) {
  len <- big_mark(get_mem_length(x), digits = 0L, format = "f")
  cat("<Memory>\n",
      "name:    ", get_mem_id(x), "\n",
      "length:  ", len, "\n",
      "address: ", mem_addr_str(x), "\n",
      "type:    ", class(x)[1L], "\n", sep = "")
}

#' @export
print.Memory <- function(x, ...) {
  cat("<", class(x)[1L], "[", get_mem_length(x), "]> ", mem_addr_str(x),
      sep = "")
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

#' @export
is_mem <- function(x) inherits(x, "Memory")
