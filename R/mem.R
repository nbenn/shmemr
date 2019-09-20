
#' @export
new_shared_mem <- function(name, length) {

  cleanup <- function(x) {
    message("removing ", name)
    mem_remove(x)
  }

  assert_that(is.string(name), is.count(length))

  length <- as.numeric(length)
  ptr <- shared_mem_init(name, length)

  reg.finalizer(ptr, cleanup, onexit = TRUE)

  structure(
    list(name = name, length = length, ptr = ptr),
    class = c("SharedMemory", "Memory")
  )
}

#' @export
new_file_mem <- function(name, length) {

  cleanup <- function(x) {
    message("removing ", name)
    mem_remove(x)
  }

  assert_that(is.string(name), is.count(length))

  length <- as.numeric(length)
  ptr <- file_mem_init(name, length)

  reg.finalizer(ptr, cleanup, onexit = TRUE)

  structure(
    list(name = name, length = length, ptr = ptr),
    class = c("FileMemory", "Memory")
  )
}
