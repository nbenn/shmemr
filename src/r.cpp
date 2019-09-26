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

#include <shmemr/r.hpp>

Memory* create_mem(std::string name, double length, std::string type)
{
  auto len = static_cast<std::size_t>(length);
  Memory* res;

  if (type == "SharedMemory")
  {
    res = dynamic_cast<Memory*>(new SharedMemory(name, len));
  }
  else if (type == "FileMemory")
  {
    res = dynamic_cast<Memory*>(new FileMemory(name, len));
  }
  else
  {
    throw std::runtime_error("Unsupported memory type.");
  }

  return res;
}

Rcpp::XPtr<Memory> memptr(SEXP x)
{
  auto tag = Rcpp::List(R_ExternalPtrTag(x));
  auto res = Rcpp::XPtr<Memory>(x, tag);

  if (!res)
  {
    auto mem = create_mem(tag["name"], tag["length"], tag["type"]);
    R_SetExternalPtrAddr(x, mem);
    auto res = Rcpp::XPtr<Memory>(x, tag);
    res.setDeleteFinalizer();
  }

  return res;
}

Rcpp::List create_tag(std::string name, double length, std::string type)
{
  return Rcpp::List::create(
    Rcpp::Named("name") = Rcpp::wrap(name),
    Rcpp::Named("length") = Rcpp::wrap(length),
    Rcpp::Named("type") = Rcpp::wrap(type)
  );
}

// [[Rcpp::export]]
SEXP mem_init(std::string name, double length, std::string type)
{
  auto mem = create_mem(name, length, type);
  auto tag = create_tag(name, length, type);

  return Rcpp::XPtr<Memory>(mem, true, tag);
}

// [[Rcpp::export]]
void mem_attach(SEXP x)
{
  memptr(x)->attach();
}

// [[Rcpp::export]]
void mem_detach(SEXP x)
{
  memptr(x)->detach();
}

// [[Rcpp::export]]
bool is_mem_attached(SEXP x)
{
  return memptr(x)->is_attached();
}

void* get_mem_pointer(SEXP x)
{
  return memptr(x)->get_address();
}

// [[Rcpp::export]]
SEXP get_mem_address(SEXP x)
{
  return R_MakeExternalPtr(get_mem_pointer(x), R_NilValue, R_NilValue);
}

// [[Rcpp::export]]
double get_mem_length(SEXP x)
{
  return static_cast<double>(memptr(x)->get_size());
}

// [[Rcpp::export]]
std::string get_mem_id(SEXP x)
{
  return memptr(x)->get_id();
}

// [[Rcpp::export]]
void mem_remove(SEXP x)
{
  memptr(x)->remove();
}

// [[Rcpp::export]]
void mem_resize(SEXP x, double new_length)
{
  auto tag = Rcpp::List(R_ExternalPtrTag(x));
  tag["length"] = Rcpp::wrap(new_length);
  R_SetExternalPtrTag(x, tag);

  memptr(x)->resize(static_cast<std::size_t>(new_length));
}

// [[Rcpp::export]]
std::string mem_addr_str(SEXP x)
{
  std::stringstream ss;
  ss << memptr(x)->get_address();
  return ss.str();
}
