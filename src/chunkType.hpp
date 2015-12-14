#ifndef CHUNK_TYPE_HPP
#define CHUNK_TYPE_HPP

#include <ndn-cxx/face.hpp>
#include <boost/date_time.hpp>
#include <vector>
#include <string>
#include "nameTypes.hpp"
#include "nmib.hpp"

namespace ndnManage
{
using std::vector;
using std::string;

namespace chunkType
{
using nameType::NameType;
using std::placeholders::_1;
using std::placeholders::_2;
class ChunkType
{
public:
	ChunkType(){}

	ChunkType(string name):
	localNDNMibName(name)
	{}

	ChunkType(ndn::Name name, vector<ndn::Name> cacheNodes):
	m_manageName(name),
	m_totalSize(-1),
	m_cacheNodes(cacheNodes),
	m_isLive(true),
	m_bornTime(0),
	m_dieTime(0)
	{}
	
	bool isLive()
	{
		return m_isLive;
	}

	int getTotalSize();
	vector<ndn::Name> getCacheNodes();
	vector<ndn::Name> AddCacheNode(ndn::Name);
	

	virtual void collectInfoForChunk(NameType&, string& name, void*){};
	virtual std::shared_ptr<nameType::BaseType>
	queryInfoForChunk(NameType&, string& name, void*){return NULL;}

	virtual bool createChunk(){ return true;};
	virtual bool updateChunk(){ return true;};
	virtual bool deleteChunk(){ return true;};
	virtual bool changeOwner(){ return true;};
	
	virtual void collectBornTime(string name){};
protected:
	ndn::Name m_manageName;
	string localNDNMibName;
	int m_totalSize;
	vector<ndn::Name> m_cacheNodes;
	
	bool m_isLive;
	boost::gregorian::date m_bornTime;
	boost::gregorian::date m_dieTime;
};
}
}

#endif
