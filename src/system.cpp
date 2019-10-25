#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using namespace std;

// Done: Return the system's CPU
Processor& System::Cpu() {
    vector<string> cpuValues;
    cpuValues = LinuxParser::CpuUtilization();
    cpu_.setProcessorValues(cpuValues);  
    return cpu_;
}

// Done: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    // clear the process storage vector 
    processes_.clear();
    vector<int> pidVector = LinuxParser::Pids();
    for(size_t i=0; i < pidVector.size(); i++){
        processes_.emplace_back(Process(pidVector[i]));
    }
  	// sort based on greater cpu usuage
    sort(processes_.begin(), processes_.end(), greater<Process>()); 
    return processes_;
}

// Done: Return the system's kernel identifier (string)
string System::Kernel(){ return LinuxParser::Kernel(); }

// Done: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Done: Return the operating system name
string System::OperatingSystem(){ return LinuxParser::OperatingSystem(); }

// Done: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Done: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Done: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }