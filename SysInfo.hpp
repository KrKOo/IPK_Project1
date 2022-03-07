#include <string>

#define HOSTNAME_FILE_NAME "/proc/sys/kernel/hostname"
#define CPU_INFO_FILE_NAME "/proc/cpuinfo"
#define CPU_STATS_FILE_NAME "/proc/stat"

typedef struct
{
	long user;
	long nice;
	long system;
	long idle;
	long iowait;
	long irq;
	long softirq;
	long steal;
} CpuStats;

class SysInfo
{
private:
	static CpuStats getCpuStats();

public:
	static std::string getCpuName();
	static std::string getHostname();
	static int getCpuLoad();
};
