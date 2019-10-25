#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using namespace std;

//constructor
Process::Process(int pid):pid_(pid) {}

// Done: Return this process's ID
int Process::Pid() { return pid_; }

// Done: Return this process's CPU utilization
float Process::CpuUtilization() const { return LinuxParser::processCpuUtilization(pid_); }

// Done: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Done: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_);}

// Done: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_);}

// Done: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// Done: Overload the "less than" comparison operator for Process objects based on CPU Usage
bool Process::operator<(Process const& a) const {
  return (CpuUtilization() < a.CpuUtilization());
}
// Done: Overload the "greater than" comparison operator for Process objects based on cpu Usage
bool Process::operator>(Process const& a) const {
  return (CpuUtilization() > a.CpuUtilization());
}