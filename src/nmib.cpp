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

	m_face.setInterestFilter(m_dataPrefix,
							bind(&NDNMib::onInterest, this, _1, _2, data),
							bind(&NDNMib::onRegisterSuccess, this, _1),
							bind(&NDNMib::onRegisterFailed, this, _1, _2));
	std::cout<<"insert"<<std::endl;
	m_face.processEvents();
}

void 
NDNMib::onInterest(const ndn::Name& prefix,
				const ndn::Interest& interest,
				const shared_ptr<ndn::Data> data)
{
	std::cout<<"onInterest"<<prefix<<std::endl;	
	m_face.put(*data);
}

	//ndn::Name m_nmibPrefix;

void 
NDNMib::onRegisterSuccess(const ndn::Name&)
{
	std::cout<<"onRegisterSuccess"<<std::endl;
	startInsertCommand();	
}

void
NDNMib::startInsertCommand()
{
	repo::RepoCommandParameter parameters;
	parameters.setName(m_dataPrefix);

	ndn::Interest commandInterest(ndn::Name(m_nmibRepoPrefix.append("insert").append(parameters.wireEncode())));
	std::cout<<commandInterest.getName()<<std::endl;
	m_face.expressInterest(commandInterest,
						   bind(&NDNMib::onCheckCommandResponse, this, _1, _2),
						   bind(&NDNMib::onCheckCommandTimeout, this, _1));
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
}
}
}
