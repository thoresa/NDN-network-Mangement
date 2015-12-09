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
using std::bind;
void 
NDNMib::insert(ndn::Name& objectName, const uint8_t* buf, int size)
{
	m_dataPrefix = objectName;
	shared_ptr<ndn::Data> data = make_shared<ndn::Data>(m_dataPrefix);
	
	data->setContent(buf, size);
	data->setFreshnessPeriod(m_freshnessPeriod);
	m_keyChain.signWithSha256(*data);
	
	const ndn::RegisteredPrefixId* filterId = m_face.setInterestFilter(m_dataPrefix,
										bind(&NDNMib::onInterest, this, _1, _2, data),
										bind(&NDNMib::onRegisterSuccess, this, _1),
										bind(&NDNMib::onRegisterFailed, this, _1, _2));
	m_face.processEvents();
	m_face.unsetInterestFilter(filterId);
	return;
}

const uint8_t*
NDNMib::read(ndn::Name& name, int& size)
{ 
	ndn::Interest interest(name);
    interest.setInterestLifetime(m_interestLifetime);
    interest.setMustBeFresh(false);
    m_face.expressInterest(interest,
                           bind(&NDNMib::onData, this, _1, _2),
                           bind(&NDNMib::onTimeout, this, _1));
	m_face.processEvents();
	const uint8_t* response = m_content.value();
	size = m_content.value_size();
	return response;
}

void
NDNMib::startProcessEvents()
{
	try
	{
		while(false)
		{	
			m_face.processEvents();
		}
	}
	catch(std::exception& e)
	{
		//	std::cout<<e.what()<<std::endl;
		//	startProcessEvents(); //not return
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
	m_isFinished = true;
}

void 
NDNMib::onData(const ndn::Interest& interest, const ndn::Data& data)
{
	const ndn::Block& content = data.getContent();
	m_content = content;
	//release signal for read
}

void
NDNMib::onTimeout(const ndn::Interest& interest)
{
	//release signal for read
	std::cout<<"onTimeout"<<interest.getName()<<std::endl;
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
	
	ndn::Interest commandInterest(ndn::Name(m_nmibRepoPrefix).append("insert").append(parameters.wireEncode()));
	
	commandInterest.setInterestLifetime(m_interestLifetime);
	m_keyChain.sign(commandInterest);
	m_face.expressInterest(commandInterest,
						   std::bind(&NDNMib::onInsertCommandResponse, this, _1, _2),
						   std::bind(&NDNMib::onInsertCommandTimeout, this, _1));
}


void
NDNMib::onInsertCommandResponse(const ndn::Interest& interest, ndn::Data& data)
{
	repo::RepoCommandResponse response(data.getContent().blockFromValue());
	int statusCode = response.getStatusCode();
	if(statusCode >= 400)
	{
		//error 
	}
	m_processId = response.getProcessId();
	m_scheduler.scheduleEvent(m_checkPeriod,
							std::bind(&NDNMib::startCheckCommand, this));
}

void
NDNMib::onInsertCommandTimeout(const ndn::Interest& interest)
{

}
void
NDNMib::startCheckCommand()
{
	repo::RepoCommandParameter parameters;
	parameters.setProcessId(m_processId);

	ndn::Interest checkInterest(ndn::Name(m_nmibRepoPrefix).append("insert check").append(parameters.wireEncode()));
	checkInterest.setInterestLifetime(m_interestLifetime);
	m_keyChain.sign(checkInterest);
	m_face.expressInterest(checkInterest,
                         bind(&NDNMib::onCheckCommandResponse, this, _1, _2),
                         bind(&NDNMib::onCheckCommandTimeout, this, _1));
}

void
NDNMib::onCheckCommandResponse(const ndn::Interest& interest, ndn::Data& data)
{
	repo::RepoCommandResponse response(data.getContent().blockFromValue());
	int statusCode = response.getStatusCode();
	if (statusCode >= 400)
	{
		//error
	}

	if (m_isFinished) 
	{
		uint64_t insertCount = response.getInsertNum();
		if(insertCount == 1)
		{
			m_face.getIoService().stop();
			return;
		}
	}
	m_scheduler.scheduleEvent(m_checkPeriod,
                           std::bind(&NDNMib::startCheckCommand, this));
}



void 
NDNMib::onCheckCommandTimeout(const ndn::Interest& interest)
{
	
}
void 
NDNMib::onRegisterFailed(const ndn::Name& name, const string str)
{
	//release signal for insert
	sem_post(&semaphoreForInsert);
}




}
}
