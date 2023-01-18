#pragma once
#include <string>
namespace Forge {

	class FileSystem {

	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}