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
#include <fstream>

#include <boost/system/error_code.hpp>

#ifdef _WIN32
#undef Realloc
#undef Free
#include <windows.h>
#include <io.h>
#endif

namespace bip = boost::interprocess;

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

  if (get_size() > 0)
  {
    map = bip::mapped_region(mem, bip::read_write);
  }
  else
  {
    map = bip::mapped_region();
  }
}

void FileMemory::attach()
{
  if (!is_attached() && get_size() > 0)
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

  std::ofstream outfile;
  outfile.open(file_path, std::ofstream::out);
  outfile.close();
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
