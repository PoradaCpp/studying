
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>


bool WriteTextAfter(std::string const& i_file_name, std::string const& i_what_to_find, std::string const& i_what_to_write);
auto GetOrCreateFile(std::string const& i_file_name, bool i_create_if_no_exists, bool i_read_only);


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
int main()
  {
	try
	{
		WriteTextAfter("D:\\temp.txt", "Test:", " passed");
	}
	catch (std::runtime_error &err)
	{
		std::cout << err.what() << '\n';
	}

  system("pause");
  return 0;
  }


//-----------------------------------------------------------------------------------
auto GetOrCreateFile(std::string const& i_file_name, bool i_create_if_no_exists, bool i_read_only)
  {
	auto HandleDeletor = [](HANDLE handle) { ::CloseHandle(handle); };
	std::unique_ptr<void, decltype(HandleDeletor)> p_handle(::CreateFileA(i_file_name.c_str(), i_read_only ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE,
		0, NULL, i_create_if_no_exists ? OPEN_ALWAYS : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL), HandleDeletor);

    return std::move(p_handle);
  }

//-----------------------------------------------------------------------------------
bool WriteTextAfter(std::string const& i_file_name, std::string const& i_what_to_find, std::string const& i_what_to_write)
  {
  if (i_what_to_write.empty())
    {
	throw std::runtime_error("Nothing to write");
    }

	auto p_handle = GetOrCreateFile(i_file_name.c_str(), !i_what_to_find.empty(), false);

	if (p_handle.get() == INVALID_HANDLE_VALUE)
	{
		auto er_code = ::GetLastError();
		throw std::runtime_error("GetOrCreateFile. Cannot open file. Error code is: " + std::to_string(er_code));
	}


  LARGE_INTEGER file_size = {};
  if (!::GetFileSizeEx(p_handle.get(), &file_size))
    {
	throw std::runtime_error("The function failed: file size cannot be calculated");
    }

  // If file is empty or new
  if (file_size.QuadPart == 0)
    {
    if (!i_what_to_find.empty())
      {
	  throw std::runtime_error("Cannot find the specified text in the file");
      }
    else
      {
      DWORD bytes_written = 0;
      auto res = ::WriteFile(p_handle.get(), i_what_to_write.c_str(), i_what_to_write.size(), &bytes_written, NULL);
      if (res == FALSE || bytes_written != i_what_to_write.size())
        {
		throw std::runtime_error("The function failed: cannot write to the file");
        }
      }
    }

  // try to find a sunstring
  std::unique_ptr<char[]> p_buffer(new char[file_size.QuadPart]);

  DWORD bytes_read = 0;
  if (!::ReadFile(p_handle.get(), p_buffer.get(), file_size.QuadPart, &bytes_read, NULL))
    {
	throw std::runtime_error("The function failed: cannot read file");
    }

  auto p_pos = strstr(p_buffer.get(), i_what_to_find.c_str());

  // write to the file
  LARGE_INTEGER pos_move = { p_pos - p_buffer.get() + strlen(i_what_to_find.c_str()) };
  ::SetFilePointerEx(p_handle.get(), pos_move, NULL, FILE_BEGIN);

  DWORD bytes_written = 0;
  auto res = ::WriteFile(p_handle.get(), i_what_to_write.c_str(), i_what_to_write.size(), &bytes_written, NULL);
  if (res == FALSE || bytes_written != i_what_to_write.size())
    {
	  throw std::runtime_error("The function failed: cannot write to the file");
    }

  return true;
  }