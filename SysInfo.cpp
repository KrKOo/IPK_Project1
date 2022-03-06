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
	getline(hostnameFile, hostname);

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

	std::regex rgx("cpu[\\s+](.+)\\s(.+)\\s(.+)\\s(.+)\\s(.+)\\s(.+)\\s(.+)\\s(.+)\\s(.+)\\s(.+)");
	std::smatch match;

	CpuStats cpuStats;

	if (fileStream.is_open())
	{
		std::string line;
		while (getline(fileStream, line))
		{
			if (std::regex_search(line, match, rgx))
			{
				cpuStats.user = stoi(match[1]);
				cpuStats.nice = stoi(match[2]);
				cpuStats.system = stoi(match[3]);
				cpuStats.idle = stoi(match[4]);
				cpuStats.iowait = stoi(match[5]);
				cpuStats.irq = stoi(match[6]);
				cpuStats.softirq = stoi(match[7]);
				cpuStats.steal = stoi(match[8]);
				break;
			}
		}
	}

	fileStream.close();

	return cpuStats;
}