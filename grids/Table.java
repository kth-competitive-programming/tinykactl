import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.event.*;

import java.awt.print.*;

public class Table extends JPanel {
    static int N = 10;
    public Table() {
    }
    static void label(Graphics2D g, String s, double x, double y) {
	g.drawString(s, (float)x, (float)y);
    }
    static void tablePaint(Graphics2D g, int c, double w, double h) {
	g.setStroke(new BasicStroke(1f));
	g.drawLine(0, (int)(0.15*h), (int)w, (int)(0.15*h));
	for (int j = 0; j < c; ++j) {
	    String l = "" + (char)('A'+j);
	    double x = (double)j/c;
	    label(g, l, w*(x+0.5f/c), 10);
	    if (j > 0)
		g.drawLine((int)(x*w), 0, (int)(x*w), (int)h);
	}
    }
    public void paintComponent(Graphics gr) {
	super.paintComponent(gr);
	Graphics2D g = (Graphics2D) gr;
	Dimension d = getSize();
	tablePaint(g, N, d.getWidth(), d.getHeight());
    }
    static class Window extends WindowAdapter {
	public void windowClosing(WindowEvent e) {
	    System.exit(0);
	}
    }
    static class TablePrint implements Printable {
	public int print(Graphics gr, PageFormat pf, int pageIndex) {
	    if (pageIndex == 0) {
		Graphics2D g = (Graphics2D) gr;
		g.translate(pf.getImageableX(), pf.getImageableY());
		g.translate(0, pf.getImageableHeight());
		g.rotate(-Math.PI / 2);
		tablePaint(g, N,
			   pf.getImageableHeight(), pf.getImageableWidth());
		return PAGE_EXISTS;
	    }
	    else
		return NO_SUCH_PAGE;
	}
    }
    static void tableSize(String[] args, int i) {
	if (args.length > i)
	    N = Integer.parseInt(args[i]);
    }
    public static void main(String[] args) {
	if (args.length > 0 && args[0].equals("print")) {
	    PrinterJob job = PrinterJob.getPrinterJob();
	    job.setPrintable(new TablePrint());
	    if (args.length > 1 && args[1].equals("dialog")) {
		tableSize(args, 2);
		if (!job.printDialog()) {
		    System.out.println("Printing cancelled");
		    System.exit(0); // !!
		    return;
		}
	    }
	    else
		tableSize(args, 1);
	    try {
		System.out.println("Printing " + N + "-table");
		job.print();
	    } catch (PrinterException e) {
		System.err.println("Printing error: " + e);
	    }
	    System.exit(0); // !!
	    return;
	}
	System.out.println("usage: " + 
			   "java Table [print [dialog]] [N]");
	tableSize(args, 0);
	JFrame frame = new JFrame("Table " + N);
	frame.addWindowListener(new Window());
	JPanel panel = new Table();
	panel.setPreferredSize(new Dimension(600, 370));
	frame.getContentPane().add(panel);
	frame.pack();
	frame.setVisible(true);
    }
}
