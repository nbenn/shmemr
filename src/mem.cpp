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

#include <cstdio>
#include <fstream>

#include <boost/system/error_code.hpp>

#ifdef _WIN32
#undef Realloc
#undef Free
#include <windows.h>
#include <io.h>
#endif

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

  map = bip::mapped_region(mem, bip::read_write);
}

void SharedMemory::attach()
{
  if (!is_attached())
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

FileMemory::FileMemory(std::string file_path, std::size_t length)
{
  if (!file_is_accessible(file_path))
  {
    create_file(file_path);
    resize_file(file_path, length);
  }

  if (file_size(file_path) != length)
  {
    throw std::runtime_error("File-size does not correspond to requested "
        "size.");
  }

  mem = bip::file_mapping(file_path.c_str(), bip::read_write);
  map = bip::mapped_region(mem, bip::read_write);
}

void FileMemory::attach()
{
  if (!is_attached())
  {
    map = bip::mapped_region(mem, bip::read_write);
  }
}

void FileMemory::detach()
{
  if (is_attached())
  {
    map = bip::mapped_region();
  }
}

bool FileMemory::is_attached()
{
  return map.get_address() != nullptr;
}

void* FileMemory::get_address()
{
  attach();
  return map.get_address();
}

std::size_t FileMemory::get_size()
{
  return file_size(file_path());
}

std::string FileMemory::get_id()
{
  return file_path();
}

void FileMemory::remove()
{
  detach();

  if (!mem.remove(file_path().c_str())) {
    throw std::runtime_error("Could not remove memory mapped file.");
  }

  mem = bip::file_mapping();
}

void FileMemory::resize(std::size_t new_size)
{
  detach();
  resize_file(file_path(), new_size);
}

std::string FileMemory::file_path()
{
  return std::string(mem.get_name());
}

bool file_is_accessible(std::string file_path)
{
  return std::ifstream(file_path).good();
}

std::size_t file_size(std::string file_path)
{
  std::ifstream file(file_path, std::ios::ate | std::ios::binary);

  if (!std::ifstream(file_path).good())
  {
    throw std::runtime_error("Can not determine file size.");
  }

  return file.tellg();
}

void create_file(std::string file_path)
{
  if (file_is_accessible(file_path))
  {
    throw std::runtime_error("File already exists.");
  }

  std::ofstream outfile(file_path);
}

void resize_file(std::string file_path, std::size_t new_size)
{
  if (!file_is_accessible(file_path))
  {
    throw std::runtime_error("Will not resize inaccessible file.");
  }

  auto file = std::fopen(file_path.c_str(), "r+");

  if (!file)
  {
    std::error_code ec(errno, std::system_category());
    throw std::system_error(ec, "Exception occurred opening file");
  }

#ifdef _WIN32

  HANDLE hand = (HANDLE)_get_osfhandle(_fileno(file));
  LARGE_INTEGER size = {new_size};

  if (!SetFilePointerEx(hand, size, NULL, FILE_BEGIN) ||
      !SetEndOfFile(hand))
  {
    DWORD err_val = GetLastError();
    std::error_code ec(err_val, std::system_category());
    throw std::system_error(ec, "Exception occurred resizing file");
  }

#else

  if (ftruncate(fileno(file), new_size) != 0)
  {
    std::error_code ec(errno, std::system_category());
    throw std::system_error(ec, "Exception occurred resizing file");
  }

#endif

  std::fclose(file);
}
