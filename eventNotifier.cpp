#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <utility>

#include <boost/lexical_cast.hpp>

#include <cxxtools/log.h>
#include <cxxtools/json/rpcclient.h>
#include <cxxtools/remoteprocedure.h>

#include "eventNotifier.h"


eventNotifier::eventNotifier() : m_jsonPort( 7004 ), m_serverName("webpi")
{

}

eventNotifier::eventNotifier(int jsonPort, const std::string &serverName) : m_jsonPort( jsonPort ), m_serverName(serverName)
{

}


eventNotifier::~eventNotifier()
{

}

void eventNotifier::notifySensor( const std::string &sensorId, const std::string &measurement, const std::string &value )
{
   std::cerr << "notify( " << sensorId << ", " << measurement << ", " << value << "); " << std::endl;    

   try
   {

//    std::cerr << "Create client " <<    m_serverName << " port " << m_jsonPort << std::endl;
   
    // and a json rpc client
    cxxtools::json::RpcClient client(m_serverName, m_jsonPort);

//    std::cerr << "Create rpc" << std::endl;

    // Define remote procedure with dobule return value and a 2 double
    // parameters.
    cxxtools::RemoteProcedure<int, std::string, std::string, std::string> logEventSensor(client, "logEventSensor");

    // and now call the remote function   

//    std::cerr << "Call it" << std::endl;

     int result = logEventSensor( sensorId, measurement,value );
 
     if (result != 0 )
     {
      std::cerr << "notify( " << sensorId << ", " << measurement << ", " << value << "); failed with " << result << std::endl;    
     }
   }
  catch (const std::exception& e)
  {
    std::cerr << "notify( " << sensorId << ", " << measurement << ", " << value << "); failed with " << e.what() << std::endl;
  }
  
}

void eventNotifier::notifyLocation( const std::string &location, const std::string &measurement, const std::string &value )
{
   std::cerr << "notify( " << location << ", " << measurement << ", " << value << "); " << std::endl;

   try
   {

//    std::cerr << "Create client " <<    m_serverName << " port " << m_jsonPort << std::endl;

    // and a json rpc client
    cxxtools::json::RpcClient client(m_serverName, m_jsonPort);

//    std::cerr << "Create rpc" << std::endl;

    // Define remote procedure with dobule return value and a 2 double
    // parameters.
    cxxtools::RemoteProcedure<int, std::string, std::string, std::string> logEventLocation(client, "logEventLocation");

    // and now call the remote function

//    std::cerr << "Call it" << std::endl;

     int result = logEventLocation( location, measurement,value );

     if (result != 0 )
     {
      std::cerr << "notify( " << location << ", " << measurement << ", " << value << "); failed with " << result << std::endl;
     }
   }
  catch (const std::exception& e)
  {
    std::cerr << "notify( " << location << ", " << measurement << ", " << value << "); failed with " << e.what() << std::endl;
  }

}

