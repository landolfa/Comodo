import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.StringTokenizer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.commons.scxml.Context;
import org.apache.commons.scxml.Evaluator;
import org.apache.commons.scxml.EventDispatcher;
import org.apache.commons.scxml.SCXMLExecutor;
import org.apache.commons.scxml.SCXMLHelper;
import org.apache.commons.scxml.TriggerEvent;
import org.apache.commons.scxml.env.SimpleDispatcher;
import org.apache.commons.scxml.env.Tracer;
import org.apache.commons.scxml.env.jexl.JexlContext;
import org.apache.commons.scxml.env.jexl.JexlEvaluator;
import org.apache.commons.scxml.io.SCXMLParser;
import org.apache.commons.scxml.model.SCXML;

public class Application {
	static SCXMLExecutor exec = null;

	public static void main(String[] args) {
		new Application("model.xml");
	}

	public Application(String fileName) {

		// No custom actions

		URL scxmlurl = null;
		Log log = LogFactory.getLog(Application.class); // create logger
		Evaluator evaluator = new JexlEvaluator(); // Evaluator evaluator = new ELEvaluator();
		EventDispatcher ed = new SimpleDispatcher(); // create event dispatcher
		Tracer trc = new Tracer(); // create error tracer
		Context context = new JexlContext(); // set new context

		try {
			scxmlurl = this.getClass().getClassLoader().getResource(fileName);
			SCXML scxml = null;
			try {

				//parse scxml document without custom actions
				scxml = SCXMLParser.parse(scxmlurl, null);

			} catch (Exception e) {
				log.error(e.getMessage(), e);
			}

			exec = new SCXMLExecutor(evaluator, ed, trc);

			exec.addListener(scxml, trc);
			exec.setRootContext(context);
			exec.setStateMachine(scxml);
			exec.registerInvokerClass("java", JavaInvoker.class);
			exec.go();
			BufferedReader br = new BufferedReader(new InputStreamReader(
					System.in));
			String event = null;
			while ((event = br.readLine()) != null) {
				event = event.trim();
				if (event.equalsIgnoreCase("quit")) {
					break;
				} else if (event.equalsIgnoreCase("reset")) {
					exec.reset();
				} else if (event.indexOf('=') != -1) {
					int marker = event.indexOf('=');
					String name = event.substring(0, marker);
					String value = event.substring(marker + 1);
					context.setLocal(name, value);
					System.out.println("Set variable " + name + " to " + value);
				} else if (SCXMLHelper.isStringEmpty(event)
						|| event.equalsIgnoreCase("null")) {
					TriggerEvent[] evts = {new TriggerEvent(null,
							TriggerEvent.SIGNAL_EVENT, null)};
					exec.triggerEvents(evts);
					if (exec.getCurrentStatus().isFinal()) {
						System.out.println("A final configuration reached.");
					}
				} else {
					StringTokenizer st = new StringTokenizer(event);
					int tkns = st.countTokens();
					TriggerEvent[] evts = new TriggerEvent[tkns];
					for (int i = 0; i < tkns; i++) {
						evts[i] = new TriggerEvent(st.nextToken(),
								TriggerEvent.SIGNAL_EVENT, null);
					}
					exec.triggerEvents(evts);
					if (exec.getCurrentStatus().isFinal()) {
						System.out.println("A final configuration reached.");
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
