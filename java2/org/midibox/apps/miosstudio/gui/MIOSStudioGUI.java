/*
 * @(#)MIOSStudioGUI.java	beta8	2006/04/23
 *
 * Copyright (C) 2008    Adam King (adamjking@optusnet.com.au)
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

package org.midibox.apps.miosstudio.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.net.URL;
import java.util.Vector;

import javax.swing.Box;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JComponent;
import javax.swing.JDesktopPane;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JInternalFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JSeparator;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.KeyStroke;
import javax.swing.UIManager;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

import org.midibox.apps.miosstudio.MIOSStudio;
import org.midibox.midi.MidiKeyboardControllerDevice;
import org.midibox.midi.SysexSendReceiveDevice;
import org.midibox.midi.gui.MidiDeviceRoutingGUI;
import org.midibox.midi.gui.MidiFilterGUI;
import org.midibox.midi.gui.MidiKeyboardControllerGUI;
import org.midibox.midi.gui.MidiMonitorFilteredGUI;
import org.midibox.mios.DebugFunctionDevice;
import org.midibox.mios.HexFileUploadDevice;
import org.midibox.mios.LCDMessageDevice;
import org.midibox.mios.gui.DebugFunctionGUI;
import org.midibox.mios.gui.HexFileUploadDeviceManagerGUI;
import org.midibox.mios.gui.LCDMessageGUI;
import org.midibox.utils.ResourceLoader;
import org.midibox.utils.gui.FontLoader;
import org.midibox.utils.gui.HelpPane;
import org.midibox.utils.gui.ImageLoader;

public class MIOSStudioGUI extends JPanel implements ActionListener,
		MouseListener, PropertyChangeListener, MenuListener {

	private MIOSStudio miosStudio;

	private JDesktopPane desktop;

	private HelpPane helpPane;

	private MIOSStudioInternalFrame helpWindow;

	private MidiDeviceRoutingGUI midiDeviceRoutingGUI;

	private MIOSStudioInternalFrame midiDeviceRoutingWindow;

	private MidiMonitorFilteredGUI midiOutPortMonitorGUI;

	private MIOSStudioInternalFrame midiOutPortMonitorWindow;

	private MidiMonitorFilteredGUI midiInPortMonitorGUI;

	private MIOSStudioInternalFrame midiInPortMonitorWindow;

	private MidiKeyboardControllerGUI midiKeyboardControllerGUI;

	private MIOSStudioInternalFrame midiKeyboardControllerWindow;

	/*
	 * private SysexSendReceiveDeviceManagerGUI
	 * sysexSendReceiveDeviceManagerGUI;
	 * 
	 * private MIOSStudioInternalFrame sysexSendReceiveDeviceManagerWindow;
	 */

	private HexFileUploadDeviceManagerGUI hexFileUploadDeviceManagerGUI;

	private MIOSStudioInternalFrame hexFileUploadDeviceManagerWindow;

	/*
	 * private MemoryReadWriteGUI memoryReadWriteGUI;
	 */

	private LCDMessageGUI lcdMessageGUI;

	private DebugFunctionGUI debugFunctionGUI;

	private MIOSStudioInternalFrame miosDebugWindow;

	private JDialog thruFilterProperties;

	/*
	 * private JDialog thruMapProperties;
	 */
	private JToolBar toolBar;

	private JPopupMenu toolBarMenu;

	private ExternalButtonProperties externalButtonProperties;

	private Vector externalCommands = new Vector();

	private JMenu fileMenu;

	private JMenuItem midiThruMenuItem;

	private JMenuItem showInternalMenuItem;

	private JMenu lookAndFeelMenu;

	private String lookAndFeel;

	private boolean defaultDecoratedFrames;

	private WindowMenu windowMenu;

	public MIOSStudioGUI(MIOSStudio miosStudio) {

		super(new BorderLayout());

		this.miosStudio = miosStudio;

		lookAndFeel = UIManager.getLookAndFeel().getClass().getName();
		defaultDecoratedFrames = JFrame.isDefaultLookAndFeelDecorated();

		add(createToolBar(), BorderLayout.NORTH);
		add(createMainPanel(), BorderLayout.CENTER);
		add(createCommentBar(), BorderLayout.SOUTH);
	}

	private JDesktopPane createMainPanel() {
		desktop = new JDesktopPane() {
			ImageIcon backgroundImage = ImageLoader
					.getImageIcon("logo_watermark.png");

			public void paintComponent(Graphics g) {
				super.paintComponent(g);
				backgroundImage
						.paintIcon(this, g, (this.getWidth() - backgroundImage
								.getIconWidth()) - 20,
								(this.getHeight() - backgroundImage
										.getIconHeight()) - 20);
			}
		}; // JDesktop pane with paint method overridden to display watermark

		desktop.setBackground(Color.WHITE);

		// Help Window

		helpPane = HelpPane.createSingleton(ResourceLoader
				.getResource("help/index.html"));
		helpPane.addPropertyChangeListener(this);

		helpWindow = new MIOSStudioInternalFrame("MIOS Studio Help", true,
				true, true, true, ImageLoader.getImageIcon("help.png"),
				helpPane);
		helpWindow.pack();

		// MIDI Device Routing

		Icon icon = ImageLoader.getImageIcon("midiDevices.png");
		midiDeviceRoutingGUI = new MidiDeviceRoutingGUI(miosStudio
				.getMidiDeviceRouting());

		midiDeviceRoutingWindow = new MIOSStudioInternalFrame(
				"MIDI Device Routing", true, // resizable
				true, // closable
				true, // maximizable
				true, icon, midiDeviceRoutingGUI);

		midiDeviceRoutingWindow.pack();

		icon = ImageLoader.getImageIcon("ucIcon.png");

		/*
		 * midiDeviceRoutingGUI.addMidiDeviceIcon(miosStudio
		 * .getMiosStudioInPort(), icon);
		 * 
		 * midiDeviceRoutingGUI.addMidiDeviceIcon(miosStudio
		 * .getMiosStudioOutPort(), icon);
		 */

		// MIDI OUT Port
		midiOutPortMonitorGUI = new MidiMonitorFilteredGUI(miosStudio
				.getMidiOutPortMonitorDevice().getMidiFilteredPortMonitor());

		icon = ImageLoader.getImageIcon("midiOut.png");

		midiOutPortMonitorWindow = new MIOSStudioInternalFrame(
				"MIDI Monitor: OUT", true, true, true, true, icon,
				midiOutPortMonitorGUI);

		midiOutPortMonitorWindow.pack();

		midiDeviceRoutingGUI.addMidiDeviceIcon(miosStudio
				.getMidiOutPortMonitorDevice(), icon);

		// MIDI IN Port
		midiInPortMonitorGUI = new MidiMonitorFilteredGUI(miosStudio
				.getMidiInPortMonitorDevice().getMidiFilteredPortMonitor());

		icon = ImageLoader.getImageIcon("midiIn.png");

		midiInPortMonitorWindow = new MIOSStudioInternalFrame(
				"MIDI Monitor: IN", true, true, true, true, icon,
				midiInPortMonitorGUI);

		midiInPortMonitorWindow.pack();

		midiDeviceRoutingGUI.addMidiDeviceIcon(miosStudio
				.getMidiInPortMonitorDevice(), icon);

		miosStudio.getMidiInPortMonitorDevice().getMidiFilteredPortMonitor()
				.getMidiPortMonitor().deleteObserver(midiInPortMonitorGUI);

		miosStudio.getMidiOutPortMonitorDevice().getMidiFilteredPortMonitor()
				.getMidiPortMonitor().deleteObserver(midiOutPortMonitorGUI);

		Thread t = new Thread() {

			public void run() {

				while (true) {

					midiInPortMonitorGUI.check();
					midiOutPortMonitorGUI.check();

					try {
						Thread.sleep(50);
					} catch (Exception e) {

					}
				}
			}

		};

		t.start();

		// MIDI Keyboard Controller

		icon = ImageLoader.getImageIcon("piano.png");

		midiKeyboardControllerGUI = new MidiKeyboardControllerGUI(miosStudio
				.getMidiKeyboardControllerDevice().getMidiKeyboardController());

		midiKeyboardControllerWindow = new MIOSStudioInternalFrame(
				"MIDI Keyboard Controller", false, // resizable
				true, // closable
				false, // maximizable
				true, icon, midiKeyboardControllerGUI);

		midiKeyboardControllerWindow.pack();

		midiDeviceRoutingGUI.addMidiDeviceIcon(
				MidiKeyboardControllerDevice.class, icon);

		// Sysex Send/Receive
		/*
		 * sysexSendReceiveDeviceManagerGUI = new
		 * SysexSendReceiveDeviceManagerGUI(
		 * miosStudio.getSysexSendReceiveDeviceManager());
		 * 
		 * icon = ImageLoader.getImageIcon("sysex.png");
		 * 
		 * sysexSendReceiveDeviceManagerWindow = new MIOSStudioInternalFrame(
		 * "Sysex Send/Receive", true, true, true, true, icon,
		 * sysexSendReceiveDeviceManagerGUI);
		 * 
		 * sysexSendReceiveDeviceManagerWindow.pack();
		 */
		midiDeviceRoutingGUI.addMidiDeviceIcon(SysexSendReceiveDevice.class,
				icon);

		// Hex Upload

		hexFileUploadDeviceManagerGUI = new HexFileUploadDeviceManagerGUI(
				miosStudio.getHexFileUploadDeviceManager());

		icon = ImageLoader.getImageIcon("hex.png");

		hexFileUploadDeviceManagerWindow = new MIOSStudioInternalFrame(
				"MIOS Hex File Upload", true, true, true, true, icon,
				hexFileUploadDeviceManagerGUI);

		hexFileUploadDeviceManagerWindow.pack();

		midiDeviceRoutingGUI.addMidiDeviceIcon(HexFileUploadDevice.class, icon);

		// Debug Window

		JTabbedPane tabbedPane = new JTabbedPane();

		// Read/Write
		/*
		 * icon = ImageLoader.getImageIcon("readWrite.png");
		 * 
		 * memoryReadWriteGUI = new MemoryReadWriteGUI(miosStudio
		 * .getMemoryReadWriteDevice().getMemoryReadWrite());
		 * 
		 * tabbedPane.addTab("MIOS Memory Read/Write", icon,
		 * memoryReadWriteGUI);
		 * midiDeviceRoutingGUI.addMidiDeviceIcon(MemoryReadWriteDevice.class,
		 * icon);
		 */
		// LCD Message
		icon = ImageLoader.getImageIcon("lcd.png");

		lcdMessageGUI = new LCDMessageGUI(miosStudio.getLcdMessageDevice()
				.getLCDMessage());

		tabbedPane.addTab("MIOS LCD Message", icon, lcdMessageGUI);
		midiDeviceRoutingGUI.addMidiDeviceIcon(LCDMessageDevice.class, icon);

		// MIOS Debug

		icon = ImageLoader.getImageIcon("functions.png");

		debugFunctionGUI = new DebugFunctionGUI(miosStudio
				.getDebugFunctionDevice().getDebugFunction());

		tabbedPane.addTab("MIOS Debug Functions", icon, debugFunctionGUI);

		tabbedPane.setOpaque(true);
		midiDeviceRoutingGUI.addMidiDeviceIcon(DebugFunctionDevice.class, icon);

		miosDebugWindow = new MIOSStudioInternalFrame("MIOS Debug Interface",
				true, true, true, true, ImageLoader.getImageIcon("debug.png"),
				tabbedPane);

		miosDebugWindow.pack();

		return desktop;
	}

	public void addExternalCommandButton(String commandName, String command) {
		ExternalCommandButton button = new ExternalCommandButton();
		button.setCommandName(commandName);
		button.setExternalCommand(command);
		externalCommands.add(button);
		toolBar.add(button);
		assignExternalButtonMnemonics();
		toolBar.setVisible(false);
		toolBar.setVisible(true);
	}

	protected void removeExternalCommandButton(ExternalCommandButton button) {
		externalCommands.remove(button);
		toolBar.remove(button);
		assignExternalButtonMnemonics();
		toolBar.setVisible(false);
		toolBar.setVisible(true);
	}

	protected void assignExternalButtonMnemonics() {
		for (int i = 0; i < externalCommands.size() && i < 9; i++) {
			((ExternalCommandButton) externalCommands.elementAt(i))
					.setMnemonic(0x31 + i);
		}
	}

	public JMenuBar createMenuBar() {
		JMenuBar menuBar = new JMenuBar();

		fileMenu = new JMenu("File");
		fileMenu.setMnemonic(KeyEvent.VK_F);
		menuBar.add(fileMenu);

		JMenu menu = new JMenu("MIDI");
		menu.setMnemonic(KeyEvent.VK_M);
		menuBar.add(menu);

		JMenuItem menuItem = new JMenuItem("MIDI Device Routing");
		menuItem.setMnemonic(KeyEvent.VK_R);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_R,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("midi_devices");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menuItem = new JMenuItem("MIDI Monitor: OUT");
		menuItem.setMnemonic(KeyEvent.VK_O);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("midi_out_port_monitor");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menuItem = new JMenuItem("MIDI Monitor: IN");
		menuItem.setMnemonic(KeyEvent.VK_I);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("midi_in_port_monitor");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menuItem = new JMenuItem("MIDI Keyboard Controller");
		menuItem.setMnemonic(KeyEvent.VK_P);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_P,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("piano_controller");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menuItem = new JMenuItem("Sysex Send/Recieve");
		menuItem.setMnemonic(KeyEvent.VK_S);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("sysex");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menu = new JMenu("MIOS");
		menu.setMnemonic(KeyEvent.VK_O);
		menuBar.add(menu);

		menuItem = new JMenuItem("MIOS Hex File Upload");
		menuItem.setMnemonic(KeyEvent.VK_U);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_U,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("open_hex_file");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menuItem = new JMenuItem("MIOS Debug Interface");
		menuItem.setMnemonic(KeyEvent.VK_D);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D,
				ActionEvent.CTRL_MASK));
		menuItem.setActionCommand("debug_window");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menu = new JMenu("Options");
		menu.setMnemonic(KeyEvent.VK_P);
		menuBar.add(menu);

		showInternalMenuItem = new JCheckBoxMenuItem("Show Internal Routing",
				miosStudio.isRouteIndividualDevices());
		showInternalMenuItem.setActionCommand("route_internal");
		showInternalMenuItem.addActionListener(this);
		menu.add(showInternalMenuItem);

		menuItem = new JMenuItem("Restore Default Internal Routing");
		menuItem.setActionCommand("restore_default");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menu.addSeparator();
		JMenu thruMenu = new JMenu("MIDI Thru");

		midiThruMenuItem = new JCheckBoxMenuItem("Enable MIDI Thru");
		midiThruMenuItem.setActionCommand("midi_thru");
		midiThruMenuItem.addActionListener(this);
		thruMenu.add(midiThruMenuItem);

		menuItem = new JMenuItem("Show MIDI Thru Filter");
		menuItem.setActionCommand("midi_thru_filter");
		menuItem.addActionListener(this);
		thruMenu.add(menuItem);

		/*
		 * menuItem = new JMenuItem("Show MIDI Thru Map");
		 * menuItem.setActionCommand("midi_thru_map");
		 * menuItem.addActionListener(this); thruMenu.add(menuItem);
		 */

		menu.add(thruMenu);
		menu.addSeparator();
		lookAndFeelMenu = new JMenu("Look & Feel");
		lookAndFeelMenu.addMenuListener(this);
		menu.add(lookAndFeelMenu);

		windowMenu = new WindowMenu(this);
		windowMenu.setMnemonic(KeyEvent.VK_W);
		menuBar.add(windowMenu);

		menu = new JMenu("Help");
		menu.setMnemonic(KeyEvent.VK_H);
		menuBar.add(menu);

		menuItem = new JMenuItem("MIOS Studio Help");
		menuItem.setMnemonic(KeyEvent.VK_I);

		menuItem.setActionCommand("help_index");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		menuItem = new JMenuItem("MIOS Function Reference");
		menuItem.setMnemonic(KeyEvent.VK_F);

		menuItem.setActionCommand("mios_fun");
		menuItem.addActionListener(this);
		menu.add(menuItem);

		return menuBar;
	}

	
	
	protected JToolBar createToolBar() {

		toolBar = new JToolBar("Tool Bar", JToolBar.HORIZONTAL);
		toolBar.setFloatable(true);
		toolBar.setRollover(true);

		JButton button;
		Insets insets = new Insets(2, 2, 2, 2);

		button = new JButton(ImageLoader.getImageIcon("midiDevices.png"));
		button.setToolTipText("MIDI Device Routing");
		button.setActionCommand("midi_devices");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		button = new JButton(ImageLoader.getImageIcon("midiOut.png"));
		button.setToolTipText("MIDI Monitor: OUT");
		button.setActionCommand("midi_out_port_monitor");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		button = new JButton(ImageLoader.getImageIcon("midiIn.png"));
		button.setToolTipText("MIDI Monitor: IN");
		button.setActionCommand("midi_in_port_monitor");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		button = new JButton(ImageLoader.getImageIcon("piano.png"));
		button.setToolTipText("MIDI Keyboard Controller");
		button.setActionCommand("piano_controller");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		/*
		 * button = new JButton(ImageLoader.getImageIcon("sysex.png"));
		 * button.setToolTipText("Sysex Send/Receive");
		 * button.setActionCommand("sysex"); button.addActionListener(this);
		 * button.setMargin(insets); toolBar.add(button);
		 */

		toolBar.addSeparator();

		button = new JButton(ImageLoader.getImageIcon("hex.png"));
		button.setToolTipText("MIOS Hex File Upload");
		button.setActionCommand("open_hex_file");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		button = new JButton(ImageLoader.getImageIcon("debug.png"));
		button.setToolTipText("MIOS Debug Interface");
		button.setActionCommand("debug_window");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		toolBar.addSeparator();

		button = new JButton(ImageLoader.getImageIcon("help.png"));
		button.setToolTipText("MIOS Studio Help");
		button.setActionCommand("help_window");
		button.addActionListener(this);
		button.setMargin(insets);
		toolBar.add(button);

		toolBar.addSeparator();

		toolBarMenu = new JPopupMenu();
		JMenuItem addButton = new JMenuItem("Add External Command Button");
		addButton.setActionCommand("add_command_button");
		addButton.addActionListener(this);
		toolBarMenu.add(addButton);

		toolBar.addMouseListener(this);
		toolBar.setVisible(true);
		return toolBar;
	}

	private void runExternalCommand(String command) {
		try {
			Runtime rt = Runtime.getRuntime();
			rt.exec(command);
		} catch (Exception e) {
			JOptionPane.showMessageDialog(this, "Cannot run command: "
					+ command + "\nReceived error: " + e.getLocalizedMessage(),
					"Cannot run command", JOptionPane.ERROR_MESSAGE);
		}
	}

	private JPanel createCommentBar() {
		JPanel commentBar = new JPanel(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridheight = 1;
		gbc.gridwidth = 1;

		gbc.fill = GridBagConstraints.BOTH;
		gbc.weightx = 1.0;
		commentBar.add(Box.createGlue(), gbc);
		gbc.gridx++;

		gbc.weightx = 0.0;
		gbc.insets = new Insets(2, 2, 2, 2);

		commentBar.add(new JSeparator(JSeparator.VERTICAL), gbc);
		gbc.gridx++;

		gbc.insets = new Insets(2, 10, 2, 20);

		commentBar.add(new JLabel("MIOS Studio beta8"), gbc);
		return commentBar;
	}

	private void showMidiThruFilter() {
		if (thruFilterProperties == null) {
			final MidiFilterGUI midiFilterGUI = new MidiFilterGUI(miosStudio
					.getMidiThruFilterDevice().getMidiFilter());

			thruFilterProperties = new JDialog();
			thruFilterProperties.setContentPane(midiFilterGUI);
			thruFilterProperties.setModal(false);
			thruFilterProperties.setTitle("MIDI Thru Filter");
			thruFilterProperties.pack();
			thruFilterProperties.setLocationRelativeTo(this);
			thruFilterProperties.setVisible(true);

			thruFilterProperties.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent we) {
					miosStudio.getMidiThruFilterDevice().deleteObserver(
							midiFilterGUI);
					thruFilterProperties = null;
				}
			});
		}
		thruFilterProperties.requestFocus();
	}

	/*
	 * private void showMidiThruMap() { if (thruMapProperties == null) { final
	 * MidiMapGUI midiMapGUI = new MidiMapGUI(miosStudio
	 * .getMidiThruMapDevice().getMidiMap());
	 * 
	 * thruMapProperties = new JDialog();
	 * thruMapProperties.setContentPane(midiMapGUI);
	 * thruMapProperties.setModal(false); thruMapProperties.setTitle("MIDI Thru
	 * Map"); thruMapProperties.pack();
	 * thruMapProperties.setLocationRelativeTo(this);
	 * thruMapProperties.setVisible(true);
	 * 
	 * thruMapProperties.addWindowListener(new WindowAdapter() { public void
	 * windowClosing(WindowEvent we) { miosStudio.getMidiThruMapDevice()
	 * .deleteObserver(midiMapGUI); thruMapProperties = null; } }); }
	 * thruMapProperties.requestFocus(); }
	 */

	protected void onHelpIndex() {
		URL currentURL = helpPane.getCurrentURL();
		if (currentURL != null) {
			if (!currentURL.equals(ResourceLoader
					.getResource("help/index.html"))) {
				helpPane.goToURL(ResourceLoader.getResource("help/index.html"));
			} else {
				showFrame(helpWindow);
			}
		} else {
			helpPane.goToURL(ResourceLoader.getResource("help/index.html"));
		}
	}

	protected void onMiosFun() {
		helpPane.goToURL(ResourceLoader.getResource("help/mios_fun.html"));
	}

	public void showFrame(JInternalFrame frame) {
		try {
			if (!frame.isVisible()) {
				frame.setVisible(true);
				desktop.add(frame);
				frame.moveToFront();
				frame.setSelected(true);
			} else if (frame.isIcon()) {
				frame.setIcon(false);
				frame.moveToFront();
				frame.setSelected(true);
			} else {
				frame.moveToFront();
				frame.setSelected(true);
			}
		} catch (java.beans.PropertyVetoException e) {
			System.out.println(e.toString());
		}
	}

	private void buildLookAndFeel() {

		JCheckBoxMenuItem item;

		for (int i = 0; i < UIManager.getInstalledLookAndFeels().length; i++) {
			final int l = i;
			item = new JCheckBoxMenuItem(
					UIManager.getInstalledLookAndFeels()[i].getName());
			lookAndFeelMenu.add(item);
			if (UIManager.getInstalledLookAndFeels()[i].getClassName().equals(
					lookAndFeel)) {
				item.setSelected(true);
			}
			item.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					try {
						lookAndFeel = UIManager.getInstalledLookAndFeels()[l]
								.getClassName();
						JOptionPane
								.showMessageDialog(
										MIOSStudioGUI.this,
										"The selected Look & Feel will be applied the next time you restart MIOS Studio",
										"ALERT", JOptionPane.ERROR_MESSAGE);
					} catch (Exception e) {
						System.out.println(e.toString());
					}
				}
			});
		}

		item = new JCheckBoxMenuItem("Include Frames/Dialogs",
				defaultDecoratedFrames);
		item.setActionCommand("dialogs");
		item.addActionListener(this);

		lookAndFeelMenu.addSeparator();
		lookAndFeelMenu.add(item);
	}

	public JMenu getFileMenu() {
		return fileMenu;
	}

	public boolean isDefaultDecoratedFrames() {
		return defaultDecoratedFrames;
	}

	public Vector getExternalCommands() {
		return externalCommands;
	}

	public String getLookAndFeel() {
		return lookAndFeel;
	}

	public JDesktopPane getDesktop() {
		return desktop;
	}

	public MIOSStudioInternalFrame getHelpWindow() {
		return helpWindow;
	}

	public MIOSStudioInternalFrame getHexFileUploadDeviceManagerWindow() {
		return hexFileUploadDeviceManagerWindow;
	}

	public MIOSStudioInternalFrame getMidiDeviceRoutingWindow() {
		return midiDeviceRoutingWindow;
	}

	public MIOSStudioInternalFrame getMidiInPortMonitorWindow() {
		return midiInPortMonitorWindow;
	}

	public MIOSStudioInternalFrame getMidiKeyboardControllerWindow() {
		return midiKeyboardControllerWindow;
	}

	public MIOSStudioInternalFrame getMidiOutPortMonitorWindow() {
		return midiOutPortMonitorWindow;
	}

	public MIOSStudioInternalFrame getMiosDebugWindow() {
		return miosDebugWindow;
	}

	public MIOSStudio getMiosStudio() {
		return miosStudio;
	}

	/*
	 * public MIOSStudioInternalFrame getSysexSendReceiveDeviceManagerWindow() {
	 * return sysexSendReceiveDeviceManagerWindow; }
	 */
	public void mousePressed(MouseEvent me) {
		Object source = me.getSource();

		if (source == toolBar) {
			if (me.getButton() == MouseEvent.BUTTON3) {
				toolBarMenu.show(toolBar, me.getX(), me.getY());
			}
		} else if (source instanceof ExternalCommandButton) {
			if (me.getButton() == MouseEvent.BUTTON3) {
				((ExternalCommandButton) source).popMenu.show(
						((ExternalCommandButton) source), me.getX(), me.getY());
			}
		}
	}

	public void mouseReleased(MouseEvent me) {

	}

	public void mouseClicked(MouseEvent me) {

	}

	public void mouseEntered(MouseEvent me) {

	}

	public void mouseExited(MouseEvent me) {

	}

	public void propertyChange(PropertyChangeEvent pce) {
		showFrame(helpWindow);
	}

	public void menuCanceled(MenuEvent e) {
	}

	public void menuDeselected(MenuEvent e) {
		Object source = e.getSource();

		if (source == windowMenu) {
			windowMenu.removeAll();
		} else if (source == lookAndFeelMenu) {
			lookAndFeelMenu.removeAll();
		}
	}

	public void menuSelected(MenuEvent e) {
		Object source = e.getSource();

		if (source == windowMenu) {
			windowMenu.buildChildMenus();
		} else if (source == lookAndFeelMenu) {
			buildLookAndFeel();
		}
	}

	public void actionPerformed(ActionEvent ae) {

		if (ae.getActionCommand().equals("open_hex_file")) {
			showFrame(hexFileUploadDeviceManagerWindow);

		} else if (ae.getActionCommand().equals("midi_devices")) {
			showFrame(midiDeviceRoutingWindow);

		} /*
			 * else if (ae.getActionCommand().equals("sysex")) {
			 * showFrame(sysexSendReceiveDeviceManagerWindow); }
			 */

		else if (ae.getActionCommand().equals("midi_in_port_monitor")) {
			showFrame(midiInPortMonitorWindow);

		} else if (ae.getActionCommand().equals("midi_out_port_monitor")) {
			showFrame(midiOutPortMonitorWindow);

		} else if (ae.getActionCommand().equals("piano_controller")) {
			showFrame(midiKeyboardControllerWindow);

		} else if (ae.getActionCommand().equals("debug_window")) {
			showFrame(miosDebugWindow);

		} else if (ae.getActionCommand().equals("route_internal")) {
			miosStudio.setRouteIndividualDevices(showInternalMenuItem
					.isSelected());

		} else if (ae.getActionCommand().equals("restore_default")) {
			miosStudio.connectDevices();

		} else if (ae.getActionCommand().equals("midi_thru_filter")) {
			showMidiThruFilter();

		} /*
			 * else if (ae.getActionCommand().equals("midi_thru_map")) {
			 * showMidiThruMap(); }
			 */

		else if (ae.getActionCommand().equals("midi_thru")) {
			miosStudio.setMidiThru(midiThruMenuItem.isSelected());

		} else if (ae.getActionCommand().equals("help_window")) {
			showFrame(helpWindow);

		} else if (ae.getActionCommand().equals("help_index")) {
			onHelpIndex();

		} else if (ae.getActionCommand().equals("mios_fun")) {
			onMiosFun();

		} else if (ae.getActionCommand().equals("externalCommand")) {
			runExternalCommand(((ExternalCommandButton) ae.getSource()).externalCommand);

		} else if (ae.getActionCommand().equals("add_command_button")) {
			addExternalCommandButton("[empty]", "");

		} else if (ae.getActionCommand().equals("dialogs")) {
			defaultDecoratedFrames = ((JCheckBoxMenuItem) ae.getSource())
					.isSelected();
		}
	}

	public class MIOSStudioInternalFrame extends JInternalFrame {
		public MIOSStudioInternalFrame(String name, boolean resizeable,
				boolean closeable, boolean maximizeable, boolean iconifiable,
				Icon icon, JComponent contentPane) {
			super(name, resizeable, closeable, maximizeable, iconifiable);
			setFrameIcon(icon);
			setContentPane(contentPane);
		}

		public Dimension getMinimumSize() {
			return getPreferredSize();
		}
	}

	public class ExternalCommandButton extends JButton implements
			ActionListener {

		public String externalCommand = "";

		public String commandName = "";

		public JPopupMenu popMenu;

		public ExternalCommandButton() {
			super(ImageLoader.getImageIcon("external.png"));

			Insets insets = new Insets(2, 2, 2, 2);

			setMargin(insets);
			setActionCommand("externalCommand");
			addActionListener(MIOSStudioGUI.this);
			setToolTipText(commandName);

			popMenu = new JPopupMenu();

			JMenuItem item = new JMenuItem("Properties");
			item.setActionCommand("show_properties");
			item.addActionListener(this);
			popMenu.add(item);

			item = new JMenuItem("Remove Button");
			item.setActionCommand("remove_command_button");
			item.addActionListener(this);
			popMenu.add(item);

			addMouseListener(MIOSStudioGUI.this);
		}

		public void actionPerformed(ActionEvent ae) {
			if (ae.getActionCommand().equals("remove_command_button")) {
				removeExternalCommandButton(this);
			} else {
				externalButtonProperties = new ExternalButtonProperties(this);
				externalButtonProperties.setSize(500, 150);
				externalButtonProperties
						.setLocationRelativeTo(MIOSStudioGUI.this);
				externalButtonProperties.setVisible(true);
			}
		}

		public void setExternalCommand(String externalCommand) {
			this.externalCommand = externalCommand;
		}

		public void setCommandName(String commandName) {
			this.commandName = commandName;
			setToolTipText(commandName);
		}

		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			Graphics2D g2d = (Graphics2D) g;
			g.setFont(FontLoader.getFont("uni05_53.ttf", 8f));
			String number = "" + (externalCommands.indexOf(this) + 1);
			FontMetrics fm = g2d.getFontMetrics();
			int offsetX = fm.stringWidth(number);
			g.drawString(number, getWidth() - offsetX - 4, getHeight() - 4);
		}
	}

	public class ExternalButtonProperties extends JDialog implements
			ActionListener {
		public ExternalCommandButton externalCommandButton;

		public JTextField commandName;

		public JTextField commandString;

		public JButton okButton;

		public ExternalButtonProperties(
				ExternalCommandButton externalCommandButton) {
			super();
			this.externalCommandButton = externalCommandButton;

			setTitle("External Command Button "
					+ (externalCommands.indexOf(externalCommandButton) + 1));

			setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);

			setLayout(new GridBagLayout());
			GridBagConstraints gbc = new GridBagConstraints();
			gbc.gridx = 0;
			gbc.gridy = 0;
			gbc.gridwidth = 1;
			gbc.gridheight = 1;

			gbc.insets = new Insets(4, 4, 4, 4);

			gbc.anchor = GridBagConstraints.WEST;
			JLabel label = new JLabel("Command Name: ");
			add(label, gbc);
			gbc.gridx++;

			gbc.anchor = GridBagConstraints.EAST;
			commandName = new JTextField(externalCommandButton.commandName, 30);
			add(commandName, gbc);
			gbc.gridx--;
			gbc.gridy++;

			gbc.anchor = GridBagConstraints.WEST;
			label = new JLabel("Command String: ");
			add(label, gbc);
			gbc.gridx++;

			gbc.anchor = GridBagConstraints.EAST;
			commandString = new JTextField(
					externalCommandButton.externalCommand, 30);
			add(commandString, gbc);
			gbc.gridx--;
			gbc.gridy++;

			okButton = new JButton("OK");
			okButton.addActionListener(this);
			gbc.gridwidth = 2;
			gbc.fill = GridBagConstraints.NONE;
			gbc.anchor = GridBagConstraints.CENTER;
			add(okButton, gbc);
		}

		public void actionPerformed(ActionEvent ae) {
			externalCommandButton.setCommandName(commandName.getText());
			externalCommandButton.setExternalCommand(commandString.getText());
			this.dispose();
		}
	}

	public class WindowMenu extends JMenu {

		private MIOSStudioGUI miosStudio;

		private JDesktopPane desktop;

		private JMenuItem cascadeMenuItem;

		public WindowMenu(MIOSStudioGUI miosStudio) {
			this.miosStudio = miosStudio;
			this.desktop = miosStudio.desktop;
			setText("Window");
			addMenuListener(MIOSStudioGUI.this);
		}

		private JInternalFrame[] getFrames() {
			return desktop.getAllFrames();
		}

		private void buildChildMenus() {
			int i;
			ChildMenuItem menuItem;
			JInternalFrame[] frames = getFrames();

			cascadeMenuItem = new JMenuItem("Cascade Windows");

			cascadeMenuItem.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent ae) {

					JInternalFrame[] frames = getFrames();

					for (int x = 0; x < frames.length; x++) {
						frames[frames.length - 1 - x].setLocation(x * 20,
								x * 20);
					}
				}
			});

			cascadeMenuItem.setEnabled(frames.length > 0);

			add(cascadeMenuItem);

			addSeparator();

			for (i = 0; i < frames.length; i++) {
				menuItem = new ChildMenuItem(frames[i]);
				menuItem.setState(i == 0);
				menuItem.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent ae) {
						JInternalFrame frame = ((ChildMenuItem) ae.getSource())
								.getFrame();
						miosStudio.showFrame(frame);
					}
				});
				menuItem.setIcon(frames[i].getFrameIcon());
				add(menuItem);
			}
		}

		public class ChildMenuItem extends JCheckBoxMenuItem {
			private JInternalFrame frame;

			public ChildMenuItem(JInternalFrame frame) {
				super(frame.getTitle());
				this.frame = frame;
			}

			public JInternalFrame getFrame() {
				return frame;
			}
		}
	}
}
