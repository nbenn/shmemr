// Copyright (C) 2019  Nicolas Bennett

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program. If not, see <http://www.gnu.org/licenses/>.

#include <shmemr/mem.hpp>

#include <Rcpp.h>

Rcpp::List create_tag(std::string name, double length, std::size_t type)
{
  return Rcpp::List::create(
    Rcpp::Named("mem_id", Rcpp::wrap(name)),
    Rcpp::Named("mem_type", Rcpp::wrap(type)),
    Rcpp::Named("length", Rcpp::wrap(length))
  );
}

template <typename T>
Rcpp::XPtr<T> xptr(SEXP x)
{
  return Rcpp::XPtr<T>(x, R_ExternalPtrTag(x), R_ExternalPtrProtected(x));
}

// [[Rcpp::export]]
SEXP mem_init(std::string name, double length, std::size_t type)
{
  auto tag = create_tag(name, length, type);
  auto len = static_cast<uintmax_t>(length);

  switch(type) {
    case 1: {
      auto res = new SharedMemory(name, len);
      return Rcpp::XPtr<SharedMemory>(res, true, Rcpp::wrap(tag));
    }
    case 2: {
      auto res = new FileMemory(name, len);
      return Rcpp::XPtr<FileMemory>(res, true, Rcpp::wrap(tag));
    }
    default: throw std::runtime_error("Cannot match memory type.");
  }
}

// [[Rcpp::export]]
void mem_attach(SEXP mem)
{
  xptr<Memory>(mem)->attach();
}

// [[Rcpp::export]]
void mem_detach(SEXP mem)
{
  xptr<Memory>(mem)->detach();
}

// [[Rcpp::export]]
bool is_mem_attached(SEXP mem)
{
  return xptr<Memory>(mem)->is_attached();
}

// [[Rcpp::export]]
SEXP get_mem_address(SEXP mem)
{
  auto ptr = xptr<Memory>(mem)->get_address();
  return R_MakeExternalPtr(ptr, R_NilValue, R_NilValue);
}

// [[Rcpp::export]]
double get_mem_length(SEXP mem)
{
  return static_cast<double>(xptr<Memory>(mem)->get_size());
}

// [[Rcpp::export]]
std::string get_mem_id(SEXP mem)
{
  return xptr<Memory>(mem)->get_id();
}

// [[Rcpp::export]]
void mem_remove(SEXP mem)
{
  xptr<Memory>(mem)->remove();
}

// [[Rcpp::export]]
void mem_resize(SEXP mem, double new_length)
{
  xptr<Memory>(mem)->resize(static_cast<uintmax_t>(new_length));
}
