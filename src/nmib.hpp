#ifndef NDN_NMIB_HPP
#define NDN_NMIB_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <memory>

#include <ndn-cxx/face.hpp>
#include <boost/asio.hpp>

namespace ndnManage
{
namespace nmib
{
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;
using std::placeholders::_2;

class NDNMib:public ndn::noncopyable
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
	NDNMib(ndn::Name nmibPrefix):
	m_nmibPrefix(nmibPrefix)
	{}
	
	NDNMib(std::string nmibPrefix)
	{
		m_nmibPrefix=ndn::Name(nmibPrefix);
	}
	
	NDNMib(){}

    void read(ndn::Name& name){};
	void add(){};
	void update(){};
	void notify(){};
	~NDNMib(){};

private:
	ndn::Name m_nmibPrefix;
};
}
}
#endif
