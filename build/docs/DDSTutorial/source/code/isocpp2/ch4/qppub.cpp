// -- Std C/C++ Include
#include <iostream>
#include <gen/TempControl_DCPS.hpp>
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono> 
#include "util.hpp"


int
main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cout << "USAGE:\n\t qppub <sensor-id>" << std::endl;
        return -1;
    }

    int sid = atoi(argv[1]);
    const int N = 100;

   /*segment1-start*/
   dds::core::QosProvider qp("file://defaults.xml", "DDS DefaultQosProfile");

  // create a Domain Participant, -1 defaults to value defined in configuration file
   dds::domain::DomainParticipant dp(-1);

   dds::topic::qos::TopicQos topicQos = qp.topic_qos();

   dds::topic::Topic<tutorial::TempSensorType> topic(dp, "TempSensor", topicQos);

   dds::pub::qos::PublisherQos pubQos = qp.publisher_qos();
   dds::pub::Publisher pub(dp, pubQos);

   dds::pub::qos::DataWriterQos dwqos = qp.datawriter_qos();
   dds::pub::DataWriter<tutorial::TempSensorType> dw(pub, topic, dwqos);  
   /*segment1-end*/
 
    const float avgT = 25;
    const float avgH = 0.6;
    const float deltaT = 5;
    const float deltaH = 0.15;
    // Initialize random number generation with a seed
    srandom(clock());
    
    // Write some temperature randomly changing around a set point
    float temp = avgT + ((random()*deltaT)/RAND_MAX);
    float hum  = avgH + ((random()*deltaH)/RAND_MAX);

    tutorial::TempSensorType sensor( sid, temp, hum, tutorial::CELSIUS );

    // Write the data
    for (unsigned int i = 0; i < N; ++i) {
        dw.write(sensor);
        std::cout << "DW << " << sensor << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        temp = avgT + ((random()*deltaT)/RAND_MAX);
        sensor.temp(temp); 
        hum = avgH + ((random()*deltaH)/RAND_MAX);
        sensor.hum(hum);
    }
  
   return 0;
}
