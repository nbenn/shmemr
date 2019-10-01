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

#include <cstdio>

#include <boost/system/error_code.hpp>

namespace bip = boost::interprocess;

SharedMemory::SharedMemory(std::string id, std::size_t length)
{
  try
  {
    mem = bip::shared_memory_object(bip::create_only, id.c_str(),
        bip::read_write);
    mem.truncate(length);
  }
  catch(const bip::interprocess_exception& er)
  {
    if (er.get_native_error() == boost::system::errc::file_exists)
    {
      mem = bip::shared_memory_object(bip::open_only, id.c_str(),
          bip::read_write);
    }
    else
    {
      throw;
    }
  }

  if (get_size() != length)
  {
    throw std::runtime_error("Could not set up a shared memory segment of "
        "the requested size.");
  }

  if (get_size() > 0)
  {
    map = bip::mapped_region(mem, bip::read_write);
  }
  else
  {
    map = bip::mapped_region();
  }
}

void SharedMemory::attach()
{
  if (!is_attached() && get_size() > 0)
  {
    map = bip::mapped_region(mem, bip::read_write);
  }
}

void SharedMemory::detach()
{
  if (is_attached())
  {
    map = bip::mapped_region();
  }
}

bool SharedMemory::is_attached()
{
  return map.get_address() != nullptr;
}

void* SharedMemory::get_address()
{
  attach();
  return map.get_address();
}

std::size_t SharedMemory::get_size()
{
  bip::offset_t size;

  if (!mem.get_size(size))
  {
    throw std::runtime_error("Could not obtain size of shared memory "
        "segment.");
  }

  if (size < 0)
  {
    throw std::runtime_error("Determined size of shared memory segment to be "
        "negative.");
  }

  return size;
}

std::string SharedMemory::get_id()
{
  return std::string(mem.get_name());
}

void SharedMemory::remove()
{
  detach();

  if (!mem.remove(mem.get_name()))
  {
    throw std::runtime_error("Could not remove shared memory segment.");
  }

  mem = bip::shared_memory_object();
}

void SharedMemory::resize(std::size_t new_size)
{
  detach();
  mem.truncate(new_size);
}
