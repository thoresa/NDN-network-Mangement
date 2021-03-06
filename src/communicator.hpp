#ifndef NDN_NMIB_HPP
#define NDN_NMIB_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <memory>

#include <ndn-cxx/face.hpp>
#include <boost/asio.hpp>

namespace nmib
{
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;
using std::placeholders::_2;

class nmib:public ndn::noncopyable
{
public:
	class Error : public std::runtime_error
	{
		public:
			explicit
				Error(const std::string& what)
				: std::runtime_error(what)
				{

				}
	};
	nmib();
	void read();
	void add();
	void update();
	void notify();
	virtual ~nmib(){};
private:
	std::string m_path;
	std::string m_prefix;
};
}

#endif
