
new_mem <- function(name, length, init_fun) {

  assert_that(is.string(name), is.count(length))

  length <- as.numeric(length)

  ptr <- init_fun(name, length)

  reg.finalizer(ptr, mem_remove, onexit = TRUE)

  res <- list2env(
    list(name = name, length = length, ptr_or_null = ptr)
  )

  makeActiveBinding("ptr", local({
    env <- res
    fun <- init_fun
    function(x) {
      assert_that(missing(x))
      if (identical(methods::new("externalptr"), env[["ptr_or_null"]])) {
        env[["ptr_or_null"]] <- fun(env[["name"]], env[["length"]])
      }
      env[["ptr_or_null"]]
    }}),
    res
  )

  structure(res, class = "Memory")
}

#' @export
new_shared_mem <- function(name, length) {

  res <- new_mem(name, length, shared_mem_init)
  class(res) <- c("SharedMemory", class(res))

  res
}

#' @export
new_file_mem <- function(name, length) {

  res <- new_mem(name, length, file_mem_init)
  class(res) <- c("FileMemory", class(res))

  res
}

#' @export
length.Memory <- function(x) {
  res <- x[["length"]]
  assert_that(identical(res, get_mem_length(obj_ptr(x))))
  res
}

#' @export
`length<-.Memory` <- function(x, value) {

  assert_that(is.count(value))

  length <- as.numeric(value)

  mem_resize(obj_ptr(x), length)
  x[["length"]] <- length

  invisible(x)
}

#' @export
names.Memory <- function(x) name(x)

#' @export
name <- function(x) {
  res <- x[["name"]]
  assert_that(identical(res, get_mem_id(obj_ptr(x))))
  res
}

#' @export
obj_ptr <- function(x) x[["ptr"]]

#' @export
mem_ptr <- function(x) get_mem_address(obj_ptr(x))

#' @export
str.Memory <- function(x) {
  structure(c("name", "length", "ptr"), envir = x, mode = "any",
            class = "ls_str")
}

#' @export
print.Memory <- function(x) {
  subcl <- class(x)[which(class(x) == "Memory") - 1L]
  cat("<", subcl, "[", length(x), "]> ", mem_addr_str(obj_ptr(x)), sep = "")
}
