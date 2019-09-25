
#' @export
new_mem <- function(length, name = rand_name(),
                    type = c("SharedMemory", "FileMemory")) {

  type <- match.arg(type)

  assert_that(is.string(name), is.string(type), is.count(length))

  length <- as.numeric(length)

  ptr <- mem_init(name, length, type)

  reg.finalizer(ptr, mem_remove, onexit = TRUE)

  structure(ptr, class = c(type, "Memory"))
}

#' @export
length.Memory <- get_mem_length

#' @export
`length<-.Memory` <- function(x, value) {

  assert_that(is.count(value))

  mem_resize(x, as.numeric(value))

  invisible(x)
}

#' @export
names.Memory <- function(x) name(x)

#' @export
name <- get_mem_id

mem_ptr <- get_mem_address

#' @export
str.Memory <- function(x) {
  len <- big_mark(get_mem_length(x), digits = 0L, format = "f")
  cat("name:    ", get_mem_id(x), "\n",
      "length:  ", len, "\n",
      "address: ", mem_addr_str(x),
      "type:    ", class(x)[1L], sep = "")
}

#' @export
print.Memory <- function(x) {
  cat("<", class(x)[1L], "[", get_mem_length(x), "]> ", mem_addr_str(x),
      sep = "")
}

big_mark <- function(x, ...) {
  mark <- if (identical(getOption("OutDec"), ",")) "." else ","
  formatC(x, big.mark = mark, ...)
}

rand_name <- function(length = 15L, chars = c(letters, LETTERS, 0L:9L)) {

  assert_that(
    is.count(length), is.character(chars), length(chars) >= 1L
  )

  paste(sample(chars, length, replace = TRUE), collapse = "")
}
