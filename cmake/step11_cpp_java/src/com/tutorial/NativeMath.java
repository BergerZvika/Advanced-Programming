package com.tutorial;

/**
 * NativeMath — a Java class whose methods are implemented in C++.
 *
 * The keyword 'native' tells the JVM: "the body of this method lives in a
 * native shared library (.so / .dll), not in bytecode."
 *
 * The static initialiser calls System.loadLibrary("nativemath") which tells
 * the JVM to load libnativemath.so from java.library.path at class-load time.
 */
public class NativeMath {

    static {
        // "nativemath" → the JVM prepends "lib" and appends ".so" on Linux,
        //                giving "libnativemath.so"
        System.loadLibrary("nativemath");
    }

    // ── Arithmetic ─────────────────────────────────────────────────────────
    public static native int    add(int a, int b);
    public static native int    multiply(int a, int b);
    public static native double power(double base, int exp);

    // ── Number theory ───────────────────────────────────────────────────────
    public static native long    factorial(int n);
    public static native boolean isPrime(int n);
    public static native long    fibonacci(int n);

    // ── String operations ───────────────────────────────────────────────────
    public static native String  reverseString(String s);
    public static native boolean isPalindrome(String s);
    public static native int     countVowels(String s);

    // ── Array operations ────────────────────────────────────────────────────
    public static native double   dotProduct(double[] a, double[] b);
    public static native double[] sortDescending(double[] arr);
}
