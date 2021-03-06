/*
 *    scampl4cpp/engine
 *
 *    Copyright by European Southern Observatory, 2012
 *    All rights reserved
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 *    02111-1307 USA.
 */

/*
 * $Id: EventListener.h 1061 2015-07-13 15:03:59Z landolfa $
 */

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif


namespace scxml4cpp
{
    class Event;

    class EventListener
    {
	
      public:
	EventListener() {}
	virtual ~EventListener() {}

	virtual void notifyEvent(Event& e) = 0;

      private:
	EventListener(const EventListener&);             //! Disable copy constructor
	EventListener& operator= (const EventListener&); //! Disable assignment operator
    };
}

#endif
