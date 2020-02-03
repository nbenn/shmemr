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

#include <Rinternals.h>
#include <Rcpp.h>

// [[Rcpp::interfaces(r, cpp)]]

template <typename T>
Rcpp::XPtr<T> xptr(SEXP x)
{
  return Rcpp::XPtr<T>(x, R_ExternalPtrTag(x), R_ExternalPtrProtected(x));
}

Memory* create_mem(std::string name, double length, std::string type)
{
  auto len = static_cast<std::size_t>(length);

  // TODO: check whether len & length are identical
  // https://stackoverflow.com/q/33719132/3855417

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

  shmemr_debug("Successfully created <%s[%.0f]> object `%s`\n", type.c_str(),
      length, name.c_str());

  return res;
}

// [[Rcpp::export]]
Rcpp::List mem_reinit(SEXP x)
{
  auto lst = Rcpp::List(x);

  shmemr_debug("%s\n", "Recreating external pointer");

  auto mem = create_mem(lst["name"], lst["length"], lst["type"]);
  auto ptr = Rcpp::XPtr<Memory>(mem, true);
  lst["ptr"] = Rcpp::wrap(ptr);

  return lst;
}

Rcpp::XPtr<Memory> memptr(SEXP x)
{
  auto lst = Rcpp::List(x);

  if (TYPEOF(lst["ptr"]) != EXTPTRSXP)
  {
    std::runtime_error("Expecting an external pointer.");
  }

  auto res = xptr<Memory>(lst["ptr"]);

  if (!res)
  {
    lst = mem_reinit(x);
    res = xptr<Memory>(lst["ptr"]);
  }

  std::string name = lst["name"];

  shmemr_debug("Using external pointer at <%p> for `%s`.\n", res.get(),
      name.c_str());

  return res;
}

void mem_destroy(Memory* mem)
{
  shmemr_debug("Releasing memory segment `%s`", mem->get_id().c_str());

  mem->remove();
  delete mem;
}

// [[Rcpp::export]]
Rcpp::CharacterVector mem_types()
{
  return Rcpp::CharacterVector::create("SharedMemory", "FileMemory");
}

// [[Rcpp::export]]
Rcpp::List mem_init(std::string name, double length, std::string type)
{
  auto mem = create_mem(name, length, type);
  auto ptr = Rcpp::XPtr<Memory, Rcpp::PreserveStorage, mem_destroy, true>(mem,
      true);

  return Rcpp::List::create(
    Rcpp::Named("name") = Rcpp::wrap(name),
    Rcpp::Named("length") = Rcpp::wrap(length),
    Rcpp::Named("type") = Rcpp::wrap(type),
    Rcpp::Named("ptr") = Rcpp::wrap(ptr)
  );
}

// [[Rcpp::export]]
void mem_release(SEXP x)
{

  if (TYPEOF(x) != EXTPTRSXP)
  {
    std::runtime_error("Expecting an external pointer.");
  }

  auto ptr = xptr<Memory>(x);

  if (ptr)
  {
    shmemr_debug("Releasing memory segment `%s`", ptr->get_id().c_str());

    ptr->remove();
  }
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

  shmemr_debug("Releasing memory segment `%s`", ptr->get_id().c_str());

  ptr->remove();
}

// [[Rcpp::export]]
void mem_resize(SEXP x, double new_length)
{
  auto lst = Rcpp::List(x);
  auto ptr = memptr(x);

  shmemr_debug("Resizing (%.0f -> %.0f) memory segment `%s`",
      Rcpp::as<double>(lst["length"]), new_length, ptr->get_id().c_str());

  lst["length"] = Rcpp::wrap(new_length);

  ptr->resize(static_cast<std::size_t>(new_length));
}
