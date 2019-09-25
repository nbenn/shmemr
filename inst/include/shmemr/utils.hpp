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

#ifndef INST_INCLUDE_SHMEMR_UTILS_HPP_
#define INST_INCLUDE_SHMEMR_UTILS_HPP_

#include <Rcpp.h>

template<class T, typename ...Ar>
SEXP create_memory(Ar&&... rg)
{
  static_assert(std::is_base_of<Memory, T>::value,
    "Only classes that are derived from Memory are allowed."
  );

  auto mem = new T(std::forward<Ar>(rg)...);
  return Rcpp::XPtr<Memory>(dynamic_cast<Memory*>(mem), true);
}

#endif  // INST_INCLUDE_SHMEMR_UTILS_HPP_
