#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <utility>

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <cxxtools/arg.h>
#include <cxxtools/log.h>

#include "eventNotifier.h"

int main( int argc, char ** argv)
{

   try
  {
    // initialize logging - this reads the file log.xml from the current directory
    log_init();

    // read the command line options

    // option -i <ip-address> defines the ip address of the interface, where the
    // server waits for connections. Default is empty, which tells the server to
    // listen on all local interfaces
    cxxtools::Arg<std::string> ip(argc, argv, 'i');

    // option -p <number> specifies the port, where jsonrpc requests are expected.
    // The default port is 7004 here.
    cxxtools::Arg<unsigned short> port(argc, argv, 'p', 7004);
    cxxtools::Arg<std::string> serverName(argc, argv, 's', "webpi");
    cxxtools::Arg<std::string> sensorId(argc, argv, 'c' );
    cxxtools::Arg<std::string> measurement(argc, argv, 'm', "Temperature" );
    cxxtools::Arg<std::string> location(argc, argv, 'l' );
    cxxtools::Arg<std::string> value(argc, argv, 'v' );
    
    if (!value.isSet())
    {
      std::cerr << "-v value must be specified" << std::endl;
      exit(1);
    }
    
    std::cerr << "sensorId.isSet()=" << sensorId.isSet() << " measurement.isSet()=" << measurement.isSet() << std::endl;
    
    if ( (!sensorId.isSet() && !measurement.isSet()) || (sensorId.isSet() && measurement.isSet()) )
    {
      std::cerr << "Either -c for sensor Code or -l for location must be specified" << std::endl;
      exit(1);
    }

    eventNotifier notifier( port, serverName );
 
    if (sensorId.isSet())
       notifier.notifySensor( sensorId, measurement, value );
        
   }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

 return 0;
}
