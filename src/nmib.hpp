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
#include <ndn-cxx/util/scheduler.hpp>
#define DEFAULT_FRESH_PERIOD 100
#define DEFAULT_INTEREST_LIFETIME 4000
#define DEFAULT_CHECK_PERIOD 1000
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
	m_freshnessPeriod(DEFAULT_FRESH_PERIOD),
	m_timeout(-1),
	m_isFinished(false),
	m_checkPeriod(DEFAULT_CHECK_PERIOD),
	m_processId(0),
	m_scheduler(m_face.getIoService()),
	m_interestLifetime(DEFAULT_INTEREST_LIFETIME)
	{
		//this->start();
		sem_init(&semaphoreForRead, 0, 0);
		sem_init(&semaphoreForInsert, 0, 0);
	}
	
	NDNMib():		
	m_scheduler(m_face.getIoService()),
	m_interestLifetime(DEFAULT_INTEREST_LIFETIME)
	{}
	
    const uint8_t* read(ndn::Name& name, int&);
	void insert(ndn::Name&, const uint8_t*, int);
	void delt(ndn::Name&);
	void update(){}
	void notify(){}
	void start();
	~NDNMib()
	{
	};
private:
	void onInterest(const ndn::Name& prefix,
					const ndn::Interest& interest,
					const shared_ptr<ndn::Data> data);
	void onRegisterSuccess(const ndn::Name&);
	void onRegisterFailed(const ndn::Name&, const string);
	void onData(const ndn::Interest&, const ndn::Data&);
	void onTimeout(const ndn::Interest&);
	void startInsertCommand();
	void onInsertCommandResponse(const ndn::Interest& interest, ndn::Data& data);
	void onInsertCommandTimeout(const ndn::Interest& interest);
	
	void onDeleteData(const ndn::Interest& interest, ndn::Data& data);
	void onDeleteTimeout(const ndn::Interest& interest);	
	void startCheckDelete(const ndn::Interest& interest);

	void startCheckCommand();
	void onCheckCommandResponse(const ndn::Interest&, ndn::Data&);
	void onCheckCommandTimeout(const ndn::Interest&);
	
	void startProcessEvents();
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
	ndn::time::milliseconds m_freshnessPeriod;
	ndn::time::milliseconds m_timeout;
	bool m_isFinished;
	ndn::time::milliseconds m_checkPeriod;
	uint64_t m_processId;
	ndn::Scheduler m_scheduler;
	ndn::time::milliseconds m_interestLifetime;
};
}
}
#endif
