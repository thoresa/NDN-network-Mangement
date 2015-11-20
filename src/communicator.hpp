#ifndef NDN_NMIB_HPP
#define NDN_NMIB_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <memory>

#include <ndn-cxx/face.hpp>
#include <boost/asio.hpp>
namespace nmib
{
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;
using std::placeholders::_2;

class nmib:public ndn::noncopyable
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
	nmib();
	void read();
	void add();
	void update();
	virtual ~nmib(){};
private:
	std::string path;
};
}

#endif
/*
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/util/scheduler.hpp>
#include <ndn-cxx/util/command-interest-generator.hpp>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/read.hpp>

namespace nmib {

using namespace ndn::time;

using std::shared_ptr;
using std::make_shared;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

static const uint64_t DEFAULT_BLOCK_SIZE = 1000;
static const uint64_t DEFAULT_INTEREST_LIFETIME = 4000;
static const uint64_t DEFAULT_FRESHNESS_PERIOD = 10000;
static const uint64_t DEFAULT_CHECK_PERIOD = 1000;
static const size_t PRE_SIGN_DATA_COUNT = 11;

class Communicator : ndn::noncopyable
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

  Communicator()
    , freshnessPeriod(DEFAULT_FRESHNESS_PERIOD)
    , interestLifetime(DEFAULT_INTEREST_LIFETIME)
    , hasTimeout(false)
    , timeout(0)

    , m_scheduler(m_face.getIoService())
    , m_timestampVersion(toUnixTimestamp(system_clock::now()).count())
  {
  }

  void
  prepareNextData(uint64_t referenceSegmentNo);

  template <typename T> void
  add(const ndn::Name& identifier, const T data);

  template <typename T> void
  update(const ndn::Name& identifier, const T data);
  
  template <typename T> void
  dlt(const ndn::Name& identifier);

private:
  milliseconds freshnessPeriod;
  milliseconds interestLifetime;
  bool hasTimeout;
  milliseconds timeout;
  ndn::Name repoPrefix;

  ndn::Face m_face;
  ndn::Scheduler m_scheduler;
  ndn::KeyChain m_keyChain;
  uint64_t m_timestampVersion;

};
*/

