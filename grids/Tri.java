import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.event.*;

import java.awt.print.*;

public class Tri extends JPanel {
    static int N = 11;
    static int M = N;
    static boolean L = true; // number/letter labels
    static boolean RECT = false; // rectangular
    static final float R = (float) Math.sqrt(3) / 2;
    static final float F = 1.1f;
    static final Shape TRI = triShape();
    static Shape triShape() {
	GeneralPath path = new GeneralPath();
	path.moveTo(0, -1); /*path.lineTo(R, -.5f);*/ path.lineTo(R, .5f);
	/*path.lineTo(0, 1);*/ path.lineTo(-R, .5f); /*path.lineTo(-R, -.5f);*/
	path.closePath();
	return path;
    }
    public Tri() {
    }
    static void label(Graphics2D g, String s, float x, float y) {
	final float P = 32;
	g.scale(1 / P, 1 / P);
	g.drawString(s, x * P, y * P);
	g.scale(P, P);
    }
    static void triPaint(Graphics2D g, int r, int c) {
	g.translate(R * F * 1.7f, F * 1.25f);
	g.setStroke(new BasicStroke(0.02f));
	Line2D line = new Line2D.Double();
	for (int i = 0; i < r; ++i) {
	    for (int j = 0; j < c; ++j) {
		if (i == 0 && L) {
		    String l = "" + (char) ('A' + j % 26);
		    label(g, l, -.8f * R, -.8f);
		    int t = RECT ? 2 - r % 2 : r;
		    label(g, l, t * R * F - .4f * R, r * 1.5f * F - .3f);
		}
		if (j == 0 && L) {
		    String l = "" + (i + 1);
		    label(g, l, -1.4f * R - (i < 9 ? 0f : .2f), .1f);
		    label(g, l, c * 2 * R * F - .85f * R, .1f);
		}
		g.draw(TRI);
		g.translate(2 * R * F, 0);
	    }
	    g.translate(-c * 2 * R * F, 0);
	    g.translate(R * F, 1.5f * F);
	    if (i % 2 == 1 && RECT)
		g.translate(-2 * R * F, 0);
	}
	g.translate(-r * R * F, -r * 1.5f * F);
    }
    static void triScale(Graphics2D g, int r, int c, double w, double h) {
	double d1 = (c * 2 * R + r * R + 1.2f) * F;
	double d2 = (r * 1.5f + 1.2f) * F;
	if (RECT) d1 -= r * R - R;
	float min = (float) Math.min(w / d1, h / d2);
	g.translate((w - min * d1) / 2, (h - min * d2) / 2);
	g.scale(min, min);
    }
    public void paintComponent(Graphics gr) {
	super.paintComponent(gr);
	Graphics2D g = (Graphics2D) gr;
	Dimension d = getSize();
	triScale(g, N, M, d.getWidth(), d.getHeight());
	triPaint(g, N, M);
    }
    static class Window extends WindowAdapter {
	public void windowClosing(WindowEvent e) {
	    System.exit(0);
	}
    }
    static class TriPrint implements Printable {
	public int print(Graphics gr, PageFormat pf, int pageIndex) {
	    if (pageIndex == 0) {
		Graphics2D g = (Graphics2D) gr;
		g.translate(pf.getImageableX(), pf.getImageableY());
		g.translate(0, pf.getImageableHeight());
		g.rotate(-Math.PI / 2);
		triScale(g, N, M,
			 pf.getImageableHeight(), pf.getImageableWidth());
		triPaint(g, N, M);
		return PAGE_EXISTS;
	    }
	    else
		return NO_SUCH_PAGE;
	}
    }
    static void triSize(String[] args, int i) {
	if (args.length > i)
	    M = N = Integer.parseInt(args[i]);
	if (args.length > i + 1)
	    M = Integer.parseInt(args[i + 1]);
	if (args.length > i + 2 && args[i + 2].equals("nolabel"))
	    L = false;
	if (args.length > i + 3 && args[i + 3].equals("rect"))
	    RECT = true;
    }
    public static void main(String[] args) {
	if (args.length > 0 && args[0].equals("print")) {
	    PrinterJob job = PrinterJob.getPrinterJob();
	    job.setPrintable(new TriPrint());
	    if (args.length > 1 && args[1].equals("dialog")) {
		triSize(args, 2);
		if (!job.printDialog()) {
		    System.out.println("Printing cancelled");
		    System.exit(0); // !!
		    return;
		}
	    }
	    else
		triSize(args, 1);
	    try {
		System.out.println("Printing " + N + "x" + M + " tri board");
		job.print();
	    } catch (PrinterException e) {
		System.err.println("Printing error: " + e);
	    }
	    System.exit(0); // !!
	    return;
	}
	System.out.println("usage: " + 
			   "java Tri [print [dialog]] " +
			   "[N [M [[no]label [rect]]]]");
	triSize(args, 0);
	JFrame frame = new JFrame("Tri " + N + "x" + M);
	frame.addWindowListener(new Window());
	JPanel panel = new Tri();
	panel.setPreferredSize(new Dimension(600, 370));
	frame.getContentPane().add(panel);
	frame.pack();
	frame.setVisible(true);
    }
}
