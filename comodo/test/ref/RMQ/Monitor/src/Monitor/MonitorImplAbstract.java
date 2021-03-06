/*******************************************************************************
 *    ESO - European Southern Observatory
 *
 *    (c) European Southern Observatory, 2011
 *    Copyright by ESO 
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
 * COMODO            -           Created.
 * 
 */

package Monitor;

import java.io.IOException;
import java.util.Properties;

import com.rabbitmq.client.ConnectionFactory;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.QueueingConsumer;

import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

import org.apache.commons.scxml.model.ModelException;
import org.apache.commons.scxml.TriggerEvent;

import Monitor.SMJavaInvoker;
import RMQCommons.SMEngine;
import RMQCommons.Message;

/**
 *
 * @author COMODO
 * @version $Id$
 */
public abstract class MonitorImplAbstract {
	private final static String CMD_QUEUE_NAME = "MONITORIMPL_CMD"; // for point to point commands
	private final static String DATA_EXCHANGE_NAME = "DATA"; // for data pub/sub  
	private final static String CMD_EXCHANGE_NAME = "CMD"; // for broadcasted commands

	private Logger mLogger = null;

	private SMEngine mEngine = null;

	private ConnectionFactory mFactory = null;
	private Connection mConnection = null;
	private Channel mChannel = null;
	private QueueingConsumer mConsumer = null;
	private boolean mIsRunning = false;

	public MonitorImplAbstract() {

		mLogger = Logger.getLogger("Monitor");
		PropertyConfigurator.configure("log4j.properties");

		try {
			mFactory = new ConnectionFactory();
			mFactory.setHost("localhost");
			mConnection = mFactory.newConnection();
			mChannel = mConnection.createChannel();

			/*
			 * Defines that messages in this queue are persistent (i.e. to be saved on disk) 	
			 * so that even if RabbitMQ server quits the messages is not lost.
			 * Note that when publishing a message, the msg itself has to be declared persistent.
			 */
			boolean durable = false; // for commands we don't want it!

			/*
			 * true if the server should consider messages acknowledged once delivered; 
			 * false if the server should expect explicit acknowledgements.
			 */
			boolean autoAck = true;

			// command queue		
			boolean exclusive = false; // restricted to this connection
			boolean autoDelete = false; // server will delete the queue when no longer in use
			mChannel.queueDeclare(CMD_QUEUE_NAME, durable, exclusive,
					autoDelete, null);

			// broadcasted commands (don't need to subscribe to a topic)
			mChannel.exchangeDeclare(CMD_EXCHANGE_NAME, "fanout", durable);
			String cmdFanoutQueueName = mChannel.queueDeclare().getQueue();
			mChannel.queueBind(cmdFanoutQueueName, CMD_EXCHANGE_NAME, "");

			// data topics to subscribe
			durable = true; // for data we want persistance!
			mChannel.exchangeDeclare(DATA_EXCHANGE_NAME, "topic", durable);
			String dataPubsubQueueName = mChannel.queueDeclare().getQueue();
			mChannel.queueBind(dataPubsubQueueName, DATA_EXCHANGE_NAME,
					"EncoderHealthSV");
			mChannel.queueBind(dataPubsubQueueName, DATA_EXCHANGE_NAME,
					"MotorHealthSV");
			mChannel.queueBind(dataPubsubQueueName, DATA_EXCHANGE_NAME,
					"NamedPositionSV");
			mChannel.queueBind(dataPubsubQueueName, DATA_EXCHANGE_NAME, "Goal");

			// define which queues to get the messages from 
			mConsumer = new QueueingConsumer(mChannel);
			mChannel.basicConsume(CMD_QUEUE_NAME, autoAck, mConsumer);
			mChannel.basicConsume(cmdFanoutQueueName, autoAck, mConsumer);
			mChannel.basicConsume(dataPubsubQueueName, autoAck, mConsumer);

		} catch (IOException e) {
			mLogger.error("Could not create RMQ channel: " + e.getMessage());
			return;
		}

		try {
			mEngine = new SMEngine(mLogger, SMJavaInvoker.class);
			// The context has to be created before the actions/activities are executed
			mEngine.setContextVar("CHANNEL", mChannel);
			mEngine.setContextVar("CMD_QUEUE_NAME", CMD_QUEUE_NAME);
			mEngine.setContextVar("CMD_EXCHANGE_NAME", CMD_EXCHANGE_NAME);
			mEngine.setContextVar("DATA_EXCHANGE_NAME", DATA_EXCHANGE_NAME);
			mEngine.loadModel("Monitor.xml");
			mEngine.startExecution();
		} catch (IOException e) {
			mLogger.error("Could not start SM execution: " + e.getMessage());
			return;
		}

		mIsRunning = true;
	}

	public Logger getLogger() {
		return mLogger;
	}

	public String getCmdQueueName() {
		return CMD_QUEUE_NAME;
	}

	public Channel getChannel() {
		return mChannel;
	}

	public QueueingConsumer getConsumer() {
		return mConsumer;
	}

	public boolean isRunning() {
		return mIsRunning;
	}

	public void closeConnections() {
		try {
			mChannel.close();
			mConnection.close();
		} catch (IOException e) {
			mLogger.error("Could not close RMQ connection: " + e.getMessage());
		}
	}

	/**
	 * Resets the StateMachine to initial state
	 */
	public void smReset() {
		try {
			mEngine.getEngine().reset();
			mLogger.info("Reset State Machine");
		} catch (ModelException e) {
			mLogger.error("Could not reset the enigne: " + e.getMessage());
		}
	}

	/**
	 * Loads a SCXML definition file.
	 * If given an empty string for file, it reloads the currently active file,
	 * otherwise it loads the file from the given path.
	 * @return true on success; false on error e.g. "file not found"
	 */
	public boolean smLoadDefinition(final String fileName) {

		String modelLoc = fileName;
		if (fileName.isEmpty()) {
			modelLoc = "Monitor.xml";
		}
		try {
			mEngine.loadModel(modelLoc);
			mEngine.startExecution();
			mLogger.info("Reloaded model: " + modelLoc);
		} catch (IOException e) {
			mLogger.error("Could not reload the model: " + modelLoc + "("
					+ e.getMessage() + ")");
		}

		return true;
	}

	/**
	 * Retrieve current state as string.
	 */
	public String smGetCurrentState() {
		return mEngine.getCurrentState();
	}

	public void smFireSignal(Message msg) {
		String signal = msg.getName();
		String[] params = msg.getParams();

		// update the SM context with the parameters of the message
		// which can be used in guards expressions
		msg.updateContext(mEngine);

		// save in the SM context as last message so that actions can retrieve 
		// the parameters ==> Probably obsolete due to msg.updateContext
		mEngine.setContextVar("LASTMSG", msg);

		mLogger.debug("Signal: " + signal);
		for (int i = 0; i < params.length; i++) {
			mLogger.debug(" Param[" + i + "] = " + params[i]);
		}

		/*
		 * Maintenance signals for state machine
		 */
		if (signal.toUpperCase().matches("SMSTATUS")
				|| signal.toUpperCase().matches("SMSTATE")) {
			mLogger.info("State: " + smGetCurrentState());
			return;
		} else if (signal.toUpperCase().matches("SMRESET")) {
			smReset();
			return;
		} else if (signal.toUpperCase().matches("SMRELOAD")) {
			smLoadDefinition("");
			return;
		} else if (signal.toUpperCase().matches("SMEXIT")) {
			mIsRunning = false; // force to quit
			return;
		} else if (signal.toUpperCase().matches("SMLOG")) {
			if (params.length == 2) {
				String property = params[0];
				String value = params[1];
				mLogger.info("smLog " + property + " " + value);
				Properties logProperties = new Properties();
				logProperties.put(property, value);
				PropertyConfigurator.configure(logProperties);
			}
		}

		TriggerEvent evnt = new TriggerEvent(signal, TriggerEvent.SIGNAL_EVENT,
				null);
		try {
			mEngine.getEngine().triggerEvent(evnt);
		} catch (ModelException e) {
			mLogger.error("Propagating event to the SM engine: "
					+ e.getMessage());
		}

		/*
		 * If final state is reached, the application can quit!
		 */
		mIsRunning = (mEngine.getEngine().getCurrentStatus().isFinal() == false);
	}
}
