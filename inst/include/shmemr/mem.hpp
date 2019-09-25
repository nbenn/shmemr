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

#ifndef INST_INCLUDE_SHMEMR_MEM_HPP_
#define INST_INCLUDE_SHMEMR_MEM_HPP_

#include <string>

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/file_mapping.hpp>

class Memory
{
public:
  virtual void attach() = 0;
  virtual void detach() = 0;
  virtual bool is_attached() = 0;

  virtual void* get_address() = 0;
  virtual std::size_t get_size() = 0;
  virtual std::string get_id() = 0;

  virtual void remove() = 0;

  virtual void resize(std::size_t) = 0;

  virtual ~Memory() {}
};

class SharedMemory: public Memory
{
public:
  SharedMemory() = default;
  SharedMemory(std::string, std::size_t);

  void attach();
  void detach();
  bool is_attached();

  void* get_address();
  std::size_t get_size();
  std::string get_id();

  void remove();

  void resize(std::size_t);

private:
  boost::interprocess::shared_memory_object mem;
  boost::interprocess::mapped_region map;
};

class FileMemory: public Memory
{
public:
  FileMemory() = default;
  FileMemory(std::string, std::size_t);

  void attach();
  void detach();
  bool is_attached();

  void* get_address();
  std::size_t get_size();
  std::string get_id();

  void remove();

  void resize(std::size_t);

private:
  boost::interprocess::file_mapping mem;
  boost::interprocess::mapped_region map;

  std::string file_path();
};

bool file_is_accessible(std::string);
std::size_t file_size(std::string);
void create_file(std::string);
void resize_file(std::string, std::size_t);

#endif  // INST_INCLUDE_SHMEMR_MEM_HPP_
