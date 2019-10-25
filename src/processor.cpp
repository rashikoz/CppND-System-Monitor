#include "processor.h"

// Done: Return the aggregate CPU utilization
double Processor::Utilization() {
    double cpuUtil; // used double for grater precision
    int timeSinceBoot, idleTimeSinceBoot;
    timeSinceBoot = user + nice + systemCpu + idle + iowait + irq + softirq + steal;
    idleTimeSinceBoot = idle + iowait;
    cpuUtil = static_cast<double> (timeSinceBoot - idleTimeSinceBoot)/timeSinceBoot;
    return (cpuUtil);
}

void Processor::setProcessorValues(vector<string> cpuValues){
    user = std::stoi(cpuValues[0]);
    nice = std::stoi(cpuValues[1]);
    systemCpu = std::stoi(cpuValues[2]);
    idle = std::stoi(cpuValues[3]);
    iowait = std::stoi(cpuValues[4]);
    irq = std::stoi(cpuValues[5]);
    softirq = std::stoi(cpuValues[6]);
    steal = std::stoi(cpuValues[7]);
    guest = std::stoi(cpuValues[8]);
    guest_nice = std::stoi(cpuValues[9]);
}
