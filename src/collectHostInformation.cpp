/*************************************************************************
	> File Name: build/tmp/collectCpuRate.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Mon 14 Dec 2015 07:27:17 PM CST
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
namespace ndnManage
{
namespace chunkType
{
float
collectCpuOccupyRate()
{
	struct CPUSTAT
	{
	private:
		string m_cpu;
		int m_user;
		int m_nice;
		int m_system;
		int m_idle;
		int m_iowait;
		int m_irq;
		int m_softirq;
		int m_stealstolen;
		int m_guest;
	public:
		int total()
		{
			return m_user+m_nice+m_system+m_idle+m_iowait+m_irq+m_softirq+m_stealstolen+m_guest;
		}
	
		int idle()
		{
			return m_idle;
		}
		void assign(istream& in)
		{
			in	>>this->m_cpu
				>>this->m_user
				>>this->m_nice
				>>this->m_system
				>>this->m_idle
				>>this->m_iowait
				>>this->m_irq
				>>this->m_softirq
				>>this->m_stealstolen
				>>this->m_guest;
		}
	};
	typedef struct CPUSTAT CpuStat;
	try
	{
		CpuStat cpuStat;
		char* path = "/proc/stat";
		ifstream stat(path);
		cpuStat.assign(stat);
		int totalJiffies_1 = cpuStat.total();
		int idleJiffies_1 = cpuStat.idle();
		stat.close();
		usleep(400*1000);
		stat.open(path);
		cpuStat.assign(stat);
		int totalJiffies_2 = cpuStat.total();
		int idleJiffies_2 = cpuStat.idle();
		int totalInterval = totalJiffies_2 - totalJiffies_1;
		int idleInterval = idleJiffies_2 - idleJiffies_1;
		stat.close();
		return 1.0*(totalInterval - idleInterval)/totalInterval;
	}
	catch(...)
	{

	}

}

float
collectMemoryOccupyRate()
{
	struct MEMORYINFO
	{
	private:
		int m_total;
		int m_free;
		int m_buffers;
		int m_cached;
	public:
		int total()
		{
			return m_total;
		}
	
		int free()
		{
			return m_free+m_buffers+m_cached;
		}
		void assign(istream& in)
		{
			string tmp;
			in	>>tmp
				>>this->m_total>>tmp
				>>tmp
				>>this->m_free>>tmp
				>>tmp
				>>this->m_buffers>>tmp
				>>tmp
				>>this->m_cached>>tmp;
		}
	};
	typedef struct MEMORYINFO MemInfo;
	try
	{
		MemInfo memInfo;
		char* path = "/proc/meminfo";
		ifstream info(path);
		memInfo.assign(info);
		int total = memInfo.total();
		int free = memInfo.free();
		info.close();
		return 1.0*(total - free)/total;
	}
	catch(...)
	{
	}
}

std::map<string, int>
collectIOBandwidth()
{
	struct NETDEV
	{
	private:
		string m_faceName;
		unsigned long m_receiveBytes;
		unsigned long m_receivePackets;
		unsigned long m_receiveErrs;
		unsigned long m_receiveDrop;
		unsigned long m_receiveFifo;
		unsigned long m_receiveFrame;
		unsigned long m_receiveCompressed;
		unsigned long m_receiveMulticast;
	
		unsigned long m_transmitBytes;
		unsigned long m_transmitPackets;
		unsigned long m_transmitErrs;
		unsigned long m_transmitDrop;
		unsigned long m_transmitFifo;
		unsigned long m_transmitColls;
		unsigned long m_transmitCarrier;
		unsigned long m_transmitCompressed;

	public:
		std::string faceName()
		{
			return m_faceName;
		}
		unsigned long receiveBytes()
		{
			return m_receiveBytes;
		}
		
		unsigned long transmitBytes()
		{
			return m_transmitBytes;
		}
		void assign(string& buffer)
		{
			int index = buffer.find(':');
			buffer[index] = ' ';
			istringstream is(buffer);
			is	>>m_faceName
				>>m_receiveBytes
				>>m_receivePackets
				>>m_receiveErrs
				>>m_receiveDrop
				>>m_receiveFifo
				>>m_receiveFrame
				>>m_receiveCompressed
				>>m_receiveMulticast

				>>m_transmitBytes
				>>m_transmitPackets
				>>m_transmitErrs
				>>m_transmitDrop
				>>m_transmitFifo
				>>m_transmitColls
				>>m_transmitCarrier
				>>m_transmitCompressed;
		}
	};

	typedef struct NETDEV NetDev;
	try
	{
		char* path = "/proc/net/dev";
		ifstream net(path);
		std::string buffer;
		getline(net, buffer);
		getline(net, buffer);	
		std::map<string, int> bytes_1;
		while(getline(net, buffer))
		{
			NetDev netDev;
			netDev.assign(buffer);
			bytes_1[netDev.faceName()] = netDev.receiveBytes()+netDev.transmitBytes();
		}
		net.close();
		
		int interval = 1;
		sleep(1);
		
		net.open(path);
		getline(net, buffer);
		getline(net, buffer);
		std::map<string, int> bytes_2;
		while(getline(net, buffer))
		{
			NetDev netDev;
			netDev.assign(buffer);
			bytes_2[netDev.faceName()] = netDev.receiveBytes()+netDev.transmitBytes();
		}
		net.close();
		
		std::map<string, int> allFacesBandwidth;
	//	for(std::map<string, int>::iterator iter1 = bytes_1.begin(), std::map<string, int>::iterator iter2 = bytes_2.begin();
		for(std::map<string, int>::iterator iter1 = bytes_1.begin(), iter2 = bytes_2.begin();
			iter1!=bytes_1.end(); iter1++, iter2++)
		{
			allFacesBandwidth[iter1->first] = iter2->second - iter1->second;
			allFacesBandwidth[iter1->first] /= interval;
		}

		return allFacesBandwidth;
	}
	catch(...)
	{
	}
}

int main()
{
	//float res = collectMemoryOccupyRate();
	std::map<string, int> res = collectIOBandwidth();
	for(std::map<string, int>::iterator iter = res.begin(); iter!=res.end(); iter++)
	{
		std::cout<<iter->first<<" "<<iter->second<<std::endl;
	}

}
}
}
/*
int main()
{
	ndnManage::chunkType::main();
}
*/
