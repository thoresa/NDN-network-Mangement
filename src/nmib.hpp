#ifndef NDN_NMIB_HPP
#define NDN_NMIB_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <memory>

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <boost/asio.hpp>
#include <semaphore.h>

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
	m_nmibRepoPrefix(nmibRepoPrefix),
	m_timeout(-1),
	m_pid(-1)
	{
		std::cout<<m_nmibRepoPrefix<<std::endl;
		this->start();
		sem_init(&semaphoreForRead, 0, 0);
		sem_init(&semaphoreForInsert, 0, 0);
	}
	
	NDNMib(){}
	
    const uint8_t* read(ndn::Name& name);
	void insert(ndn::Name&, const uint8_t*, int);
	void delt(){}
	void update(){}
	void notify(){}
	void start();
	~NDNMib()
	{
		if(m_pid!=-1)
		{
			pthread_kill(m_pid, SIGKILL);
		}
	};
private:
	void onInterest(const ndn::Name& prefix,
					const ndn::Interest& interest,
					const shared_ptr<ndn::Data> data);
	void onRegisterSuccess(const ndn::Name&);
	void onRegisterFailed(const ndn::Name&, const string);
	void onCheckCommandResponse(const ndn::Interest&, ndn::Data&);
	void onCheckCommandTimeout(const ndn::Interest&);
	void onData(const ndn::Interest&, const ndn::Data&);
	void onTimeout(const ndn::Interest&);
	void startInsertCommand();
	void startProcessEvents(void);
	static void* startProcessEventsHelper(void*);
private:
	sem_t semaphoreForRead;
	sem_t semaphoreForInsert;

	pthread_t m_pid;
	ndn::Name m_nmibRepoPrefix;
	ndn::KeyChain m_keyChain;
	ndn::Name m_dataPrefix;
	ndn::Face m_face;
	ndn::Block m_content;
	ndn::time::milliseconds m_interestLifetime;
	ndn::time::milliseconds m_timeout;


};
}
}
#endif
