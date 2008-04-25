/*
 * @(#)SIDV2librarian.java	beta1	2008/01/21
 *
 * Copyright (C) 2008    Rutger Vlek (rutgervlek@hotmail.com)
 *
 * This application is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this application; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

package org.midibox.sidedit;

import java.util.Observable;
import java.lang.Math;
import javax.sound.midi.MidiMessage;
import javax.sound.midi.Receiver;
import javax.sound.midi.SysexMessage;

import org.midibox.sidlibr.Patch;


public class SIDSysexParameter extends Observable implements Receiver {

	public final static Object VALUE = new Object();

	protected Receiver receiver;

	protected int value;

	protected int address;
	
	protected int start_bit;

	protected int midimax, midimin;

	protected int resolution;
	
	protected String name;
	
	protected Patch patch;
		
	public SIDSysexParameter(Patch p, int address, int start_b, int reso, String name) {
		setReceiver(p.getReceiver());
		setMidiMaxMinValues(reso);
		setMidiValue(p.getParameter(address, start_b, reso), false);
		this.address = address;
		this.start_bit = start_b;
		this.patch = p;
		this.name = name;
	}
	
	public Receiver getReceiver() {
		return receiver;
	}
	protected void setReceiver(Receiver receiver) {
		this.receiver = receiver;
	}

	public int getMidiValue() {
		return limitMidiValue(value);
	}

	public void setMidiValue(int value, boolean forward) {
		this.value = limitMidiValue(value);

		if (forward) {
			createMessage();
		}
		
		setChanged();
		notifyObservers(VALUE);
		clearChanged();
	}
	
	public void setMidiMaxMinValues(int reso) {
		if (reso < 0) {
			midimax = (int) Math.floor((Math.pow(2,Math.abs(reso))-1)/2);
			midimin = -((int) Math.ceil((Math.pow(2,Math.abs(reso))-1)/2));
		}
		else {
			midimax = (int) Math.pow(2,reso)-1;
			midimin = 0;
		}
		resolution = reso;
	}

	public int getMidiMaxValue() {		
		return midimax;
	}
	
	public int getMidiMinValue() {		
		return midimin;
	}
	
	public String getMidiName() {
		return name;
	}

	public void createMessage() {
		patch.setParameter(address, value, start_bit, resolution);
	}

	public void send(MidiMessage message, long lTimeStamp) {
		
	}

	public void close() {
	}
	
	protected int limitMidiValue(int i) {
		if (i > midimax) {i=midimax;}
		if (i < midimin) {i=midimin;}
		return i;
	}
}