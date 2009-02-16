package org.midibox.midi.xml;

import java.io.File;

import org.midibox.midi.MidiFilter;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.sun.org.apache.xerces.internal.parsers.DOMParser;

public class MidiFilterXMLFactory {
	
	public static void loadMidiFilter(MidiFilter midiFilter, File file) {
		
		DOMParser domParser = new DOMParser();
		
		try {
		
			domParser.parse(file.getPath());
		} catch (Exception e) {
			
			e.printStackTrace();
		}
		
		Document doc = domParser.getDocument();
		
		loadMidiFilter(midiFilter, doc);
	}
	
	public static void loadMidiFilter(MidiFilter midiFilter, Node node) {
		
		NodeList children = node.getChildNodes();
		
		for (int n = 0; n < children.getLength(); n++) {
			
			loadMidiFilter(midiFilter, children.item(n));
		}
		
		switch (node.getNodeType()) {
				
			case Node.ELEMENT_NODE: 
				parseElement(midiFilter, (Element) node);			
		}
	}
	
	protected static void parseElement(MidiFilter midiFilter, Element element) {
		
		String name = element.getNodeName();
		
		NamedNodeMap attributes = element.getAttributes();
		
		if (name == "channels") {
				
		} else if (name == "channel") {
			
			Node number = attributes.getNamedItem("number");
			
			Node enable = attributes.getNamedItem("enable");
			
			if (number != null && enable != null) {
				
				int n = Integer.parseInt(number.getTextContent());
				
				boolean e = Boolean.parseBoolean(enable.getTextContent());
				
				midiFilter.channel[n-1] = e;
			}
			
		} else if (name == "voiceMessages") {
			
		} else if (name == "voiceMessage") {
			
		} else if (name == "systemCommonMessages") {
			
		} else if (name == "systemCommonMessage") {
			
		} else if (name == "systemRealtimeMessages") {
			
		} else if (name == "systemRealtimeMessage") {
			
		}  else if (name == "sysexMessages") {
			
		} else if (name == "metaMessages") {
			
		} else if (name == "controlChangeMessages") {
			
		} else if (name == "controlChangeMessage") {
			
			Node number = attributes.getNamedItem("number");
			
			Node enable = attributes.getNamedItem("enable");
			
			if (number != null && enable != null) {
				
				int n = Integer.parseInt(number.getTextContent());
				
				boolean e = Boolean.parseBoolean(enable.getTextContent());
				
				midiFilter.cc[n] = e;
			}
		}		
	}
}
