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

package org.midibox.sidedit.gui.bassline;

import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JPanel;

import org.midibox.sidedit.SIDSysexInfo;
import org.midibox.sidedit.gui.controls.SIDSysexParameterControlGUI;
import org.midibox.sidedit.gui.controls.SIDSysexParameterControlKnob;
import org.midibox.sidedit.gui.controls.SIDSysexParameterControlSlider;
import org.midibox.sidedit.gui.controls.SIDSysexParameterControlToggleButton;

public class LfoGUI extends JPanel {

	protected LfoGUI(Vector lfoLGUIv, Vector lfoRGUIv, Vector envLGUIv,
			Vector envRGUIv) {
		setLayout(new BorderLayout());
		setOpaque(false);

		JPanel topPanel = new JPanel();
		topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.Y_AXIS));
		topPanel.setOpaque(false);

		JPanel panel1 = new JPanel();
		panel1.setOpaque(false);
		panel1.setLayout(new GridLayout(2, 2));
		panel1.add(createLFO(lfoLGUIv, "LFO 1 (left)", 0));
		panel1.add(createLFO(lfoRGUIv, "LFO 1 (right)", 0));
		panel1.add(createLFO(lfoLGUIv, "LFO 2 (left)", 11));
		panel1.add(createLFO(lfoRGUIv, "LFO 2 (right)", 11));

		JPanel panel2 = new JPanel();
		panel2.setLayout(new GridLayout(1, 2));
		panel2.add(createENV(envLGUIv, "Envelope 1 (left)"));
		panel2.add(createENV(envRGUIv, "Envelope 2 (right)"));
		panel2.setOpaque(false);

		topPanel.add(panel1);
		topPanel.add(panel2);
		add(topPanel, BorderLayout.NORTH);
	}

	protected JPanel createLFO(Vector midiParameterGUI, String s, int offset) {
		JPanel lfoPanel = new JPanel(new GridBagLayout());
		lfoPanel.setBorder(BorderFactory.createEtchedBorder());
		lfoPanel.setBorder(BorderFactory.createTitledBorder(s));
		lfoPanel.setOpaque(false);
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.HORIZONTAL;
		c.ipadx = 5;

		// Buttons
		c.gridx = 0;
		c.gridy = 0;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(0 + offset), c);
		c.gridx = 0;
		c.gridy = 1;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(2 + offset), c);
		c.gridx = 1;
		c.gridy = 0;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(3 + offset), c);
		c.gridx = 1;
		c.gridy = 1;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(1 + offset), c);

		// Waveform selector
		c.gridx = 2;
		c.gridy = 0;
		c.gridwidth = 5;
		c.gridheight = 2;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(4 + offset), c);

		// Knobs
		c.gridx = 7;
		c.gridy = 0;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(5 + offset), c);
		c.gridx = 8;
		c.gridy = 0;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(9 + offset), c);
		c.gridx = 9;
		c.gridy = 0;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(10 + offset), c);
		c.gridx = 7;
		c.gridy = 1;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(6 + offset), c);
		c.gridx = 8;
		c.gridy = 1;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(7 + offset), c);
		c.gridx = 9;
		c.gridy = 1;
		c.gridwidth = 1;
		c.gridheight = 1;
		lfoPanel.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(8 + offset), c);

		// Setup the 'rate'-knob behavior to be depending on the 'master sync'
		// switch
		((SIDSysexParameterControlKnob) midiParameterGUI.elementAt(6 + offset))
				.setSnapVals(new int[] { 245, 246, 247, 248, 249, 250, 251,
						252, 253, 254, 255 }, SIDSysexInfo.rates);
		((SIDSysexParameterControlToggleButton) midiParameterGUI
				.elementAt(2 + offset))
				.setSnapParameter((SIDSysexParameterControlGUI) midiParameterGUI
						.elementAt(6 + offset));

		return lfoPanel;
	}

	protected JPanel createENV(Vector midiParameterGUI, String s) {
		JPanel envTopPanel = new JPanel();
		envTopPanel.setLayout(new BoxLayout(envTopPanel, BoxLayout.Y_AXIS));
		envTopPanel.setBorder(BorderFactory.createEtchedBorder());
		envTopPanel.setBorder(BorderFactory.createTitledBorder(s));
		envTopPanel.setOpaque(false);

		JPanel envPanel = new JPanel();
		envPanel.setLayout(new BoxLayout(envPanel, BoxLayout.X_AXIS));
		envPanel.setOpaque(false);

		// SubPanel1
		JPanel subPanel1 = new JPanel();
		subPanel1.setLayout(new GridLayout(1, 4));
		subPanel1.setOpaque(false);
		subPanel1.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(7));
		((SIDSysexParameterControlSlider) midiParameterGUI.elementAt(7))
				.setHeight(120);
		subPanel1.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(8));
		((SIDSysexParameterControlSlider) midiParameterGUI.elementAt(8))
				.setHeight(120);
		subPanel1.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(9));
		((SIDSysexParameterControlSlider) midiParameterGUI.elementAt(9))
				.setHeight(120);
		subPanel1.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(10));
		((SIDSysexParameterControlSlider) midiParameterGUI.elementAt(10))
				.setHeight(120);

		envPanel.add(subPanel1);

		// SubPanel2
		JPanel subPanel2 = new JPanel();
		subPanel2.setLayout(new GridLayout(3, 5));
		subPanel2.setOpaque(false);
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(4));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(5));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(6));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(12));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(11));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(3));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(0));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(1));
		subPanel2.add((SIDSysexParameterControlGUI) midiParameterGUI
				.elementAt(2));
		envPanel.add(subPanel2);

		envTopPanel.add(envPanel);

		return envTopPanel;
	}
}