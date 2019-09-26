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

#ifndef INST_INCLUDE_SHMEMR_R_HPP_
#define INST_INCLUDE_SHMEMR_R_HPP_

#include <shmemr/mem.hpp>

#include <Rcpp.h>

SEXP mem_init(std::string, double, std::string)
void mem_remove(SEXP)
void mem_resize(SEXP, double);

void mem_attach(SEXP)
void mem_detach(SEXP)
bool is_mem_attached(SEXP)

void* get_mem_pointer(SEXP)
SEXP get_mem_address(SEXP)

double get_mem_length(SEXP)
std::string get_mem_id(SEXP)

#endif  // INST_INCLUDE_SHMEMR_R_HPP_
