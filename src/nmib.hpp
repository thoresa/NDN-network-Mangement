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
using std::string;

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
	NDNMib(ndn::Name nmibRepoPrefix):
	m_nmibRepoPrefix(nmibRepoPrefix)
	{
		std::cout<<m_nmibRepoPrefix<<std::endl;
	}
	
	NDNMib(){}

    void read(ndn::Name& name){};
	void insert(ndn::Name&, uint8_t*, int&);
	void update(){};
	void notify(){};
	~NDNMib(){};
private:
	void onInterest(const ndn::Name& prefix,
					const ndn::Interest& interest,
					const shared_ptr<ndn::Data> data);
	void onRegisterSuccess(const ndn::Name&);
	void onRegisterFailed(const ndn::Name&, const string);
	void onCheckCommandResponse(const ndn::Interest&, ndn::Data&);
	void onCheckCommandTimeout(const ndn::Interest&);
	void startInsertCommand();
private:
	ndn::Name m_nmibRepoPrefix;
	ndn::Name m_dataPrefix;
	ndn::Face m_face;
};
}
}
#endif
