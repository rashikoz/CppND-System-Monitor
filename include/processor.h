#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>
using std::string;
using std::vector;


class Processor {
 public:
    double Utilization();  // TODO: See src/processor.cpp
    void setProcessorValues(vector<string>);
 private:
    int user, nice, systemCpu, idle, iowait;
    int irq, softirq, steal, guest, guest_nice;
};

#endif