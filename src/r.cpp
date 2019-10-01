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

#include <shmemr/mem.h>
#include <shmemr/utils.h>

#include <Rcpp.h>

// [[Rcpp::interfaces(r, cpp)]]

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

  shmemr_debug("Successfully created %s object <%s[%.0f]>\n",
               type.c_str(), name.c_str(), length);

  return res;
}

Rcpp::XPtr<Memory> memptr(SEXP x)
{
  auto lst = Rcpp::List(x);
  SEXP ptr = lst["ptr"];

  shmemr_debug("Using external pointer at <%p>\n", (void *)ptr);

  if (TYPEOF(ptr) != EXTPTRSXP)
  {
    std::runtime_error("Expecting an external pointer.");
  }

  auto res = Rcpp::XPtr<Memory>(ptr);

  if (!res)
  {
    shmemr_debug("%s\n", "Recreating external pointer");

    auto mem = create_mem(lst["name"], lst["length"], lst["type"]);
    res = Rcpp::XPtr<Memory>(mem, true);
    lst["ptr"] = Rcpp::wrap(res);
  }

  return res;
}

// [[Rcpp::export]]
Rcpp::List mem_init(std::string name, double length, std::string type)
{
  auto mem = create_mem(name, length, type);
  auto ptr = Rcpp::XPtr<Memory>(mem, true);

  return Rcpp::List::create(
    Rcpp::Named("name") = Rcpp::wrap(name),
    Rcpp::Named("length") = Rcpp::wrap(length),
    Rcpp::Named("type") = Rcpp::wrap(type),
    Rcpp::Named("ptr") = Rcpp::wrap(ptr)
  );
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

// [[Rcpp::export]]
SEXP get_mem_ptr(SEXP x)
{
  return R_MakeExternalPtr(memptr(x)->get_address(), R_NilValue, R_NilValue);
}

// [[Rcpp::export]]
std::string get_mem_str(SEXP x)
{
  std::stringstream ss;
  ss << memptr(x)->get_address();
  return ss.str();
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
  auto ptr = memptr(x);

  shmemr_debug("Deleting memory segment %s<%p>", ptr->get_id().c_str(),
      ptr->get_address());

  ptr->remove();
}

// [[Rcpp::export]]
void mem_resize(SEXP x, double new_length)
{
  auto lst = Rcpp::List(x);
  auto ptr = memptr(x);

  shmemr_debug("Resizing (%.0f -> %.0f) memory segment at %s<%p>",
      Rcpp::as<double>(lst["length"]), new_length, ptr->get_id().c_str(),
      ptr->get_address());

  lst["length"] = Rcpp::wrap(new_length);

  ptr->resize(static_cast<std::size_t>(new_length));
}
