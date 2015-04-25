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

void usage( char*progName )
{

	std::cerr << "Usage : " << progName << " [-i] [-p]  [-s]  [-c] [-m] [-c | -l] -v" << std::endl;
    std::cerr << "    -i <ip addr> :   Target server ip address" << std::endl;
    std::cerr << "    -s <name> :      Target server name, default webpi" << std::endl;
    std::cerr << "    -p <port> :      Target server JSON port, default 7004" << std::endl;
    std::cerr << "    -c <sensor> :    Sensor code (Mapped to location by server)" << std::endl;
    std::cerr << "    -l <location> :  Location name" << std::endl;
    std::cerr << "    -m <meas> :      Measurement name, default Temperature" << std::endl;
    std::cerr << "    -v <meas> :      Measurement name, default Temperature" << std::endl;
    exit( 1 );
}


int main( int argc, char ** argv)
{

   try
  {
    // initialize logging - this reads the file log.xml from the current directory
//    log_init();

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
      usage(argv[0]);
    }
    
//    std::cerr << "sensorId.isSet()=" << sensorId.isSet() << " measurement.isSet()=" << measurement.isSet() << std::endl;
    
    if ( (!sensorId.isSet() && !measurement.isSet()) || (sensorId.isSet() && measurement.isSet()) )
    {
      std::cerr << "Either -c for sensor Code or -l for location must be specified" << std::endl;
      usage(argv[0]);
    }

    eventNotifier notifier( port, serverName );
 
    if (sensorId.isSet())
       notifier.notifySensor( sensorId, measurement, value );
    else
       notifier.notifyLocation( location, measurement, value );
        
   }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

 return 0;
}
