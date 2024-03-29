#include <unistd.h>
#include <fstream>
#include <regex>

#include "SysInfo.hpp"

std::string SysInfo::getCpuName()
{
	std::ifstream fileStream(CPU_INFO_FILE_NAME);

	std::regex rgx("model name\t: (.+)");
	std::smatch match;

	std::string cpuName = "";

	if (fileStream.is_open())
	{
		std::string line;
		while (getline(fileStream, line))
		{
			if (std::regex_search(line, match, rgx))
			{
				cpuName = match[1];
				break;
			}
		}
	}

	fileStream.close();

	return cpuName;
}

std::string SysInfo::getHostname()
{
	std::ifstream hostnameFile(HOSTNAME_FILE_NAME);
	std::string hostname;

	if (hostnameFile.is_open())
	{
		getline(hostnameFile, hostname);
	}

	hostnameFile.close();

	return hostname;
}

int SysInfo::getCpuLoad()
{
	CpuStats prevCpuStats = getCpuStats();
	sleep(1);
	CpuStats cpuStats = getCpuStats();

	long prevIdle = prevCpuStats.idle + prevCpuStats.iowait;
	long idle = cpuStats.idle + cpuStats.iowait;

	long prevNonIdle = prevCpuStats.user + prevCpuStats.nice + prevCpuStats.system + prevCpuStats.irq + prevCpuStats.softirq + prevCpuStats.steal;
	long nonIdle = cpuStats.user + cpuStats.nice + cpuStats.system + cpuStats.irq + cpuStats.softirq + cpuStats.steal;

	long prevTotal = prevIdle + prevNonIdle;
	long total = idle + nonIdle;

	long totald = total - prevTotal;
	long idled = idle - prevIdle;

	double cpuLoad = (double)(totald - idled) / totald * 100;

	return (int)cpuLoad;
}

CpuStats SysInfo::getCpuStats()
{
	std::ifstream fileStream(CPU_STATS_FILE_NAME);

	std::regex rgx("cpu\\s*(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s(\\d*)");
	std::smatch match;

	CpuStats cpuStats;

	if (fileStream.is_open())
	{
		std::string line;
		while (getline(fileStream, line))
		{
			if (std::regex_search(line, match, rgx))
			{
				cpuStats.user = stol(match[1]);
				cpuStats.nice = stol(match[2]);
				cpuStats.system = stol(match[3]);
				cpuStats.idle = stol(match[4]);
				cpuStats.iowait = stol(match[5]);
				cpuStats.irq = stol(match[6]);
				cpuStats.softirq = stol(match[7]);
				cpuStats.steal = stol(match[8]);
				break;
			}
		}
	}

	fileStream.close();

	return cpuStats;
}
