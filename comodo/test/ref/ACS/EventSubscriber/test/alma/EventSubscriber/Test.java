/*******************************************************************************
 *    ALMA - Atacama Large Millimiter Array
 *
 *    (c) European Southern Observatory, 2002
 *    Copyright by ESO (in the framework of the ALMA collaboration)
 *    and Cosylab 2002, All rights reserved
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
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * "@(#) $Id$" 
 *
 * who                when       what
 * ----------------  ----------  ----------------------------------------------
 * COMODO                        Created.
 * 
 */

package alma.EventSubscriber;

import static org.junit.Assert.*;
import org.junit.Before;

import java.util.List;
import java.util.logging.Logger;

import alma.acs.logging.ClientLogManager;
import alma.acs.component.client.ComponentClientTestCase;

import alma.EventSubscriber.*;
import alma.EventSubscriber.EventSubscriberImpl;

import alma.ACS.*;

public class EventSubscriberImplTest extends ComponentClientTestCase {
	private Logger logger;
	private String componentName = "testInstanceEventSubscriberImpl";
	private EventSubscriberImpl component;

	/////////////////////////////////////////////////////////////
	// Lifecycle
	/////////////////////////////////////////////////////////////

	public EventSubscriberImplTest(String name) throws Exception {
		super("EventSubscriberImpl");
	}//

	protected void setUp() throws Exception {
		super.setUp();
		logger = ClientLogManager.getAcsLogManager().getLoggerForApplication(
				getClass().getSimpleName(), false);
		this.component = (EventSubscriberImpl) this.getContainerServices()
				.getComponent(this.componentName);
	}//

	@Override
	protected void tearDown() throws Exception {
		super.tearDown();
		this.getContainerServices().releaseComponent(this.componentName);
	}//

}
