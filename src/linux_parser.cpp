#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include "linux_parser.h"

using namespace std;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      replace(line.begin(), line.end(), ' ', '_');
      replace(line.begin(), line.end(), '=', ' ');
      replace(line.begin(), line.end(), '"', ' ');
      istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
    //close the stream
    filestream.close();
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    getline(stream, line);
    istringstream linestream(line);
    linestream >> os >> version >>kernel;
    // close the stream
    stream.close();
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (all_of(filename.begin(), filename.end(), ::isdigit)) {
        int pid = stoi(filename);
        pids.emplace_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line, parameter, value, unit;
  float memUtilization;
  int memTotal, memFree;
  ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      istringstream linestream(line);
      linestream >> parameter >> value >> unit;
      if (parameter == "MemTotal:") {
        memTotal = stoi(value);
      }
      else if (parameter == "MemFree:")
      {
        memFree = stoi(value);
      }
    }
    // close the stream
    stream.close();
  }
  memUtilization = static_cast<float>(memTotal - memFree)/memTotal;
  return memUtilization;
}

// Done: Read and return the system uptime
long LinuxParser::UpTime() { 
  string systemUptime, idleTime;
  string line;
  ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    getline(stream, line);
    istringstream linestream(line);
    linestream >> systemUptime >> idleTime;
    // close the stream
    stream.close();
  }
  return stol(systemUptime);
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, parameter, theValues, theBuffer;
  ifstream stream(kProcDirectory + kStatFilename);
  vector<string> cpuValues;
  if (stream.is_open()) {
    while (getline(stream, line)) {
      istringstream linestream(line);
      linestream >> parameter;
      if (parameter == "cpu") {
        while(linestream >> theBuffer){
          cpuValues.emplace_back(theBuffer);
        }
      }     
    }
    // close the stream
    stream.close();
  }
  return cpuValues;
}

// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, parameter, value;
  int totalProcs;
  ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      istringstream linestream(line);
      linestream >> parameter >> value;
      if (parameter == "processes") {
        totalProcs = stoi(value);
      }
    }
    // close the stream
    stream.close();
  }
  return totalProcs;
}

// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, parameter, value;
  int runningProcs;
  ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      istringstream linestream(line);
      linestream >> parameter >> value;
      if (parameter == "procs_running") {
        runningProcs = stoi(value);
      }
    }
    // close the stream
    stream.close();
  }
  return runningProcs;
}

// Done: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string commandLine;
  ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    getline(stream, commandLine);
    // close the stream
    stream.close();
  }
  return commandLine;
}

// Done: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line, parameter, value, unit;
  float ramInMb = 0.0;
  stringstream ramStreamer;
  ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while ( getline(stream, line)) {
      istringstream linestream(line);
      linestream >> parameter >> value >> unit;
      if (parameter == "VmSize:") {
        ramInMb =  stof(value)/1024;
      }
    }
    // close the stream
    stream.close();
  }
  ramStreamer.precision(2);
  ramStreamer << fixed << ramInMb;
  return ramStreamer.str();
}

// Done: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line, parameter, uid;
  ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      istringstream linestream(line);
      linestream >> parameter;
      if (parameter == "Uid:") {
        linestream >> uid;     
      }
    }
    // close the stream
    stream.close();
  }
  return uid;
}

// Done: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line, userName, token;
  vector <string> tempBuf;
  string thisProcessUid = LinuxParser::Uid(pid);
  ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      istringstream linestream(line);
      tempBuf.clear();
      while( getline(linestream, token, ':')){
        tempBuf.emplace_back(token);
      }
      if (tempBuf[2] == thisProcessUid){
        userName = tempBuf[0];
        break;
      }
    }
    // close the stream
    stream.close();
  }
  return userName;
}

// Done: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  vector <string> tempBuf;
  string line, token;
  ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    getline(stream, line);
    istringstream linestream(line);
    while(linestream >> token){
      tempBuf.emplace_back(token);
    }
    // close the stream
    stream.close();
  }
  return  stol(tempBuf[21])/sysconf(_SC_CLK_TCK);
}

// process cpu utilisation
float LinuxParser::processCpuUtilization(int pid){
  float cpuUtil, seconds, hertz;
  float sysUptime, totalTime;  
  string line, token;
  vector <string> tempBuf;
  ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    getline(stream, line);
    istringstream linestream(line);
    while(linestream >> token){
      tempBuf.emplace_back(token);
    }
    // close the stream
    stream.close();
  }
  // now calc
  hertz = sysconf(_SC_CLK_TCK);
  sysUptime = LinuxParser::UpTime();
  totalTime = ( stof(tempBuf[13])
               +  stof(tempBuf[14])
               +  stof(tempBuf[15])
               +  stof(tempBuf[16]));
  seconds = sysUptime - (stof(tempBuf[21])/hertz);
  cpuUtil = ((totalTime/hertz)/seconds);
  return cpuUtil;
}