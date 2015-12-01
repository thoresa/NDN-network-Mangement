#ifndef CHUNK_TYPE_HPP
#define CHUNK_TYPE_HPP

#include <ndn-cxx/face.hpp>
#include <boost/date_time.hpp>
#include <vector>
#include <string>

namespace ndnManage
{
using std::vector;
using std::string;

namespace chunkType
{
using std::placeholders::_1;
using std::placeholders::_2;
class ChunkType
{
public:
	ChunkType(){}

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
	

	virtual bool createChunk(){ return true;};
	virtual void readChunk(){ return;};
	virtual bool updateChunk(){ return true;};
	virtual bool deleteChunk(){ return true;};
	virtual bool changeOwner(){ return true;};
	
	virtual void collectBornTime(string name){};
private:
	ndn::Name m_manageName;
	int m_totalSize;
	vector<ndn::Name> m_cacheNodes;
	
	bool m_isLive;
	boost::gregorian::date m_bornTime;
	boost::gregorian::date m_dieTime;
};
}
}

#endif
