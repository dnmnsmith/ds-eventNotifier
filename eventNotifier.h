/*
 * eventNotifier.h
 *
 *  Created on: 27 Mar 2015
 *      Author: ds
 */

#ifndef EVENTNOTIFIER_H_
#define EVENTNOTIFIER_H_


class eventNotifier
{

public:
	eventNotifier();
	eventNotifier(int jsonPort, const std::string &serverName);
	virtual ~eventNotifier();

	void notifySensor( const std::string &sensorId, const std::string &measurement, const std::string &value );

private:
	int m_jsonPort;
	std::string m_serverName;
};



#endif /* EVENTNOTIFIER_H_ */
