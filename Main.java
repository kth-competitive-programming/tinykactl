// ACM-Contest, Location, Date
//
// Template for KTH-NADA, Ballons'R'Us, ACM 2001-2002
//   David Rydh, Mattias de Zalenski, Fredrik Niemelä
//
// Problem: _

import java.util.StringTokenizer;

class Main {
    static final int N = 0;
    public static void main(String[] args) {
	Main m = new Main();
	m.init();
	
	// simple-solve
	m.solve(0);
	
	// for-solve
	int n = Integer.parseInt(getLine(255));
	for (int i = 0; i < n; i++)
	    m.solve(i);
	
	// while-solve
	int n = 0;
	while (m.solve(n))
	    n++;
    }
    void init() {
    }
    boolean solve(int P) {
	String s = getLine(255);
	int n = Integer.parseInt(s == null ? "0" : s);
	if (n == 0) return false;
	StringTokenizer st = new StringTokenizer("this is a test");
	while (st.hasMoreTokens())
	    System.out.println(st.nextToken());
	return true;
    }
    static String getLine(int maxLength) {
        byte line[] = new byte[maxLength];
        int p = 0, c = -1;
        try {
	    while (p < maxLength) {
		c = System.in.read();
		if ((c < 0) || (c == '\n')) break;
		line[p++] = c;
	    }
	} catch (Exception e) { }
        if ((c < 0) && (p == 0)) return null;  // eof
        return new String(line, 0, p);
    }
}
