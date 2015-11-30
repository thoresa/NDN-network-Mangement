#include <iostream>
#include "nmib.hpp"
#include "../../src/repo-command-parameter.hpp"
#include "../../src/repo-command-response.hpp"


namespace ndnManage
{
namespace nmib
{

using std::placeholders::_1;
using std::placeholders::_2;

void 
NDNMib::insert(ndn::Name& objectName, uint8_t* buf, int& size)
{
	m_dataPrefix = objectName;
	shared_ptr<ndn::Data> data = make_shared<ndn::Data>(m_dataPrefix);
	data->setContent(buf, size);
	m_keyChain.signWithSha256(*data);
	m_face.setInterestFilter(m_dataPrefix,
							bind(&NDNMib::onInterest, this, _1, _2, data),
							bind(&NDNMib::onRegisterSuccess, this, _1),
							bind(&NDNMib::onRegisterFailed, this, _1, _2));
	//wait signal for insert
	sem_wait(&semaphoreForInsert);
	return;
}

const uint8_t*
NDNMib::read(ndn::Name& name)
{ 
	ndn::Interest interest(name);
    interest.setInterestLifetime(m_interestLifetime);
    interest.setMustBeFresh(true);

    m_face.expressInterest(interest,
                           bind(&NDNMib::onData, this, _1, _2),
                           bind(&NDNMib::onTimeout, this, _1));
	m_face.processEvents(m_timeout);
	//wait signal for read
	sem_wait(&semaphoreForRead);
	const uint8_t*  response = reinterpret_cast<const uint8_t*>(m_content.value());
	return response;
}

void
NDNMib::startProcessEvents()
{
	try
	{
		while(true)
		{
			m_face.processEvents();
		}
	}
	catch(std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
		startProcessEvents(); //not return
	}
}

void*
NDNMib::startProcessEventsHelper(void* args)
{
	((NDNMib*) args)->startProcessEvents();
	return NULL;
}

//may be put it into the constructure

void 
NDNMib::start()
{
	pthread_create(&m_pid, NULL, &NDNMib::startProcessEventsHelper, this);
}

void 
NDNMib::onInterest(const ndn::Name& prefix,
				const ndn::Interest& interest,
				const shared_ptr<ndn::Data> data)
{
	m_face.put(*data);
	//release signal for insert
	sem_post(&semaphoreForInsert);
}

void 
NDNMib::onData(const ndn::Interest& interest, const ndn::Data& data)
{
	const ndn::Block& content = data.getContent();
	m_content = content;
	//release signal for read
	sem_post(&semaphoreForRead);
}

void
NDNMib::onTimeout(const ndn::Interest& interest)
{
	//release signal for read
	sem_post(&semaphoreForRead);
}

void 
NDNMib::onRegisterSuccess(const ndn::Name&)
{
	startInsertCommand();	
}

void
NDNMib::startInsertCommand()
{
	repo::RepoCommandParameter parameters;
	parameters.setName(m_dataPrefix);

	ndn::Interest commandInterest(ndn::Name(m_nmibRepoPrefix.append("insert").append(parameters.wireEncode())));
	m_face.expressInterest(commandInterest,
						   bind(&NDNMib::onCheckCommandResponse, this, _1, _2),
						   bind(&NDNMib::onCheckCommandTimeout, this, _1));
	m_face.processEvents(m_timeout);
	
}

void 
NDNMib::onCheckCommandResponse(const ndn::Interest& interest, ndn::Data& data)
{
}
void 
NDNMib::onCheckCommandTimeout(const ndn::Interest& interest)
{
}
void 
NDNMib::onRegisterFailed(const ndn::Name& name, const string str)
{
	std::cout<<str<<std::endl;
	//release signal for insert
	sem_post(&semaphoreForInsert);
}
}
}