#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <ndn-cxx/face.hpp>

#include "nameTypes.hpp"

namespace ndnManage
{
namespace nameType
{


using std::map;
using std::string;

template <class T>
class Serialization
{
public:
	/*static const char* 
	Serialize(const FaceStatusStruct& fs, int& size)
	{
		std::ostringstream os;
		os<<fs;
		std::string content = os.str();
		size = content.length();
		return content.c_str();
	}


	static FaceStatusStruct 
	DeSerialize(const char* buf)
	{
		string tmpBufStr(buf);
		FaceStatusStruct fs;
		std::istringstream is(tmpBufStr);
		is>>fs;
		return fs;
	}
	*/
	static const char* 
	Serialize(const T& fs, int& size)
	{
		std::ostringstream os;
		os<<fs;
		std::string content = os.str();
		size = content.length();
		return content.c_str();
	}


	static T
	DeSerialize(const char* buf)
	{
		string tmpBufStr(buf);
		T fs;
		std::istringstream is(tmpBufStr);
		is>>fs;
		return fs;
	}
	
	
};

}
}
#endif
