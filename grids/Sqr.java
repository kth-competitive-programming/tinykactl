import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import javax.swing.event.*;

import java.awt.print.*;

public class Sqr extends JPanel {
    static int N = 30;
    static int M = 50;
    static boolean L = true; // number/letter labels
    static boolean G = false; // go perspective
    static boolean C = false; // go circles
    static final float R = .06f; // go circle radius
    static final float F = 1f;
    static final Shape SQR = sqrShape();
    static final Shape CIR = cirShape();
    static Shape sqrShape() {
	GeneralPath path = new GeneralPath();
	path.moveTo(-.5f, -.5f); path.lineTo(.5f, -.5f);
	path.lineTo(.5f, .5f); path.lineTo(-.5f, .5f);
	path.closePath();
	return path;
    }
    static Shape cirShape() {
	return new Ellipse2D.Float(F * -.5f - R, F * -.5f - R, 2 * R, 2 * R); 
    }
    public Sqr() {
    }
    static void label(Graphics2D g, String s, float x, float y) {
	final float P = 32;
	g.scale(1 / P, 1 / P);
	g.drawString(s, x * P, y * P);
	g.scale(P, P);
    }
    static boolean goCheck(int i, int l) {
	int d = l < 16 ? l < 10 ? 2 : 3 : 4;
	return i == d || i == l / 2 || i == l - d;
    }
    static void sqrPaint(Graphics2D g, int r, int c) {
	g.translate(F, F);
	g.setStroke(new BasicStroke(G ? 0.025f : 0.005f));
	for (int i = 0; i < r; ++i) {
	    for (int j = 0; j < c; ++j) {
		if (i == 0 && L) {
		    String l = "" + (j + 1);
		    label(g, l, -.05f - (j < 9 ? 0f : .2f), -.6f);
		    label(g, l, -.05f - (j < 9 ? 0f : .2f), r * F - .1f);
		}
		if (j == 0 && L) {
		    String l = "" + (char) ('A' + i % 26);
		    label(g, l, -0.9f, .1f);
		    label(g, l, c * F - .35f, .1f);
		}
		if (C && goCheck(i, r) && goCheck(j, c)) {
		    g.fill(CIR);
		}
		g.draw(SQR);
		g.translate(F, 0);
	    }
	    g.translate(-c * F, 0);
	    g.translate(0, F);
	}
	g.translate(0, -r * F);
    }
    static void sqrScale(Graphics2D g, int r, int c, double w, double h) {
	double d1 = (c + 1) * F * (G ? 13 : 1);
	double d2 = (r + 1) * F * (G ? 12 : 1);
	float min = (float) Math.min(w / d1, h / d2);
	g.translate((w - min * d1) / 2, (h - min * d2) / 2);
	g.scale(min * (G ? 13 : 1), min * (G ? 12 : 1));
    }
    public void paintComponent(Graphics gr) {
	super.paintComponent(gr);
	Graphics2D g = (Graphics2D) gr;
	Dimension d = getSize();
	sqrScale(g, N, M, d.getWidth(), d.getHeight());
	sqrPaint(g, N, M);
    }
    static class Window extends WindowAdapter {
	public void windowClosing(WindowEvent e) {
	    System.exit(0);
	}
    }
    static class SqrPrint implements Printable {
	public int print(Graphics gr, PageFormat pf, int pageIndex) {
	    if (pageIndex == 0) {
		Graphics2D g = (Graphics2D) gr;
		g.translate(pf.getImageableX(), pf.getImageableY());
		g.translate(0, pf.getImageableHeight());
		g.rotate(-Math.PI / 2);
		sqrScale(g, N, M,
			 pf.getImageableHeight(), pf.getImageableWidth());
		sqrPaint(g, N, M);
		return PAGE_EXISTS;
	    }
	    else
		return NO_SUCH_PAGE;
	}
    }
    static void sqrSize(String[] args, int i) {
	if (args.length > i)
	    M = N = Integer.parseInt(args[i]);
	if (args.length > i + 1)
	    M = Integer.parseInt(args[i + 1]);
	if (args.length > i + 2 && args[i + 2].equals("nolabel"))
	    L = false;
	if (args.length > i + 2 && args[i + 2].equals("go")) {
	    --M;
	    --N;
	    L = false;
	    G = true;
	    C = true;
	}
    }
    public static void main(String[] args) {
	if (args.length > 0 && args[0].equals("print")) {
	    PrinterJob job = PrinterJob.getPrinterJob();
	    job.setPrintable(new SqrPrint());
	    if (args.length > 1 && args[1].equals("dialog")) {
		sqrSize(args, 2);
		if (!job.printDialog()) {
		    System.out.println("Printing cancelled");
		    System.exit(0); // !!
		    return;
		}
	    }
	    else
		sqrSize(args, 1);
	    try {
		System.out.println("Printing " + N + "x" + M + " board");
		job.print();
	    } catch (PrinterException e) {
		System.err.println("Printing error: " + e);
	    }
	    System.exit(0); // !!
	    return;
	}
	System.out.println("usage: " + 
			   "java Sqr [print [dialog]] [N [M [nolabel|go]]]");
	sqrSize(args, 0);
	JFrame frame = new JFrame("Sqr " + N + "x" + M);
	frame.addWindowListener(new Window());
	JPanel panel = new Sqr();
	panel.setPreferredSize(new Dimension(600, 370));
	frame.getContentPane().add(panel);
	frame.pack();
	frame.setVisible(true);
    }
}
