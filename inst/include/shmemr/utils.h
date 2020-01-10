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

#ifndef INST_INCLUDE_SHMEMR_UTILS_H_
#define INST_INCLUDE_SHMEMR_UTILS_H_

#include <Rcpp.h>

#ifdef SHMEMR_DEBUG
  #define shmemr_debug(fmt, ...) do { \
    Rprintf("%s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__); \
  } while (0)
#else
  #define shmemr_debug(fmt, ...)
#endif

#endif  // INST_INCLUDE_SHMEMR_UTILS_H_
