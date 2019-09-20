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
#include <shmemr/utils.hpp>

// [[Rcpp::export]]
SEXP shared_mem_init(std::string name, double length)
{
  return create_memory<SharedMemory>(name, static_cast<uintmax_t>(length));
}

// [[Rcpp::export]]
SEXP file_mem_init(std::string name, double length)
{
  return create_memory<FileMemory>(name, static_cast<uintmax_t>(length));
}

// [[Rcpp::export]]
void mem_attach(SEXP mem)
{
  Rcpp::XPtr<Memory>(mem)->attach();
}

// [[Rcpp::export]]
void mem_detach(SEXP mem)
{
  Rcpp::XPtr<Memory>(mem)->detach();
}

// [[Rcpp::export]]
bool is_mem_attached(SEXP mem)
{
  return Rcpp::XPtr<Memory>(mem)->is_attached();
}

// [[Rcpp::export]]
SEXP get_mem_address(SEXP mem)
{
  auto ptr = Rcpp::XPtr<Memory>(mem)->get_address();
  return R_MakeExternalPtr(ptr, R_NilValue, R_NilValue);
}

// [[Rcpp::export]]
double get_mem_length(SEXP mem)
{
  return static_cast<double>(Rcpp::XPtr<Memory>(mem)->get_size());
}

// [[Rcpp::export]]
std::string get_mem_id(SEXP mem)
{
  return Rcpp::XPtr<Memory>(mem)->get_id();
}

// [[Rcpp::export]]
void mem_remove(SEXP mem)
{
  Rcpp::XPtr<Memory>(mem)->remove();
}

// [[Rcpp::export]]
void mem_resize(SEXP mem, double new_length)
{
  Rcpp::XPtr<Memory>(mem)->resize(static_cast<uintmax_t>(new_length));
}
