#include "endpointType.hpp"
namespace ndnManage
{
namespace chunkType
{

void
EndpointType::queryFaces(string filter)
{
	try
	{
		ndn::Name realName(ndn::Name(nfdPrefix).append(filter));
		std::cout<<realName<<std::endl;
		ndn::Interest interest(realName);
		m_face.expressInterest(interest,
				bind(&EndpointType::onData, this, _1, _2),
				bind(&EndpointType::onTimeout, this, _1));
		ndn::time::milliseconds timeout(0);
		m_face.processEvents();
	}
	catch(std::exception& e)
	{
		std::cout<<"exception"<<e.what()<<std::endl;
	}
}



void
EndpointType::onData(const ndn::Interest& interest, ndn::Data& data)
{
	const ndn::Block& content = data.getContent();
	std::cout<<"get Data"<<reinterpret_cast<const uint8_t*>(content.value());
	const uint8_t* buf = reinterpret_cast<const uint8_t*>(content.value());
	//call nmib to store it into the repo
	//name: dataType/data_name/objectInfo
	//name: /ndn/management/endpoint/localhost/nfd/faces
	ndn::Name name("/ndn/management/endpoint/localhost/nfd/faces");
	ndnMib.insert(name, buf, static_cast<int>(content.value_size()));

	return ;
}

void
EndpointType::onTimeout(const ndn::Interest& interest)
{
	//call collectfaces() for three times.
	return;
}

void
EndpointType::queryFib(string name)
{

}

void 
EndpointType::queryHostInfo(string name)
{

}


}
}
