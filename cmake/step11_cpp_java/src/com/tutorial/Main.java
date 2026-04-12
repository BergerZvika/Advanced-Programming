package com.tutorial;

import java.util.Arrays;

/**
 * Main entry point for the C++ + Java JNI demo.
 *
 * Demonstrates calling native C++ functions from Java across three categories:
 *   1. Arithmetic / number theory
 *   2. String manipulation
 *   3. Array operations
 */
public class Main {

    // ── Utility for pretty output ───────────────────────────────────────────
    private static void header(String title) {
        System.out.println("\n--- " + title + " ---");
    }

    private static void show(String label, Object value) {
        System.out.printf("  %-28s = %s%n", label, value);
    }

    // ── main ────────────────────────────────────────────────────────────────
    public static void main(String[] args) {
        System.out.println("============================================");
        System.out.println("  Step 11: C++ via JNI called from Java");
        System.out.println("============================================");

        // ── Arithmetic ──────────────────────────────────────────────────────
        header("Arithmetic (C++ implementation)");
        show("add(7, 5)",          NativeMath.add(7, 5));
        show("multiply(6, 7)",     NativeMath.multiply(6, 7));
        show("power(2.0, 10)",     NativeMath.power(2.0, 10));
        show("power(1.5, 4)",      NativeMath.power(1.5, 4));

        // ── Number theory ───────────────────────────────────────────────────
        header("Number Theory (C++ implementation)");
        show("factorial(0)",       NativeMath.factorial(0));
        show("factorial(10)",      NativeMath.factorial(10));
        show("factorial(20)",      NativeMath.factorial(20));
        show("isPrime(97)",        NativeMath.isPrime(97));
        show("isPrime(100)",       NativeMath.isPrime(100));
        show("fibonacci(10)",      NativeMath.fibonacci(10));
        show("fibonacci(20)",      NativeMath.fibonacci(20));

        // ── String operations ───────────────────────────────────────────────
        header("String Operations (C++ implementation)");
        show("reverseString(\"CMake\")",      NativeMath.reverseString("CMake"));
        show("reverseString(\"Hello JNI\")",  NativeMath.reverseString("Hello JNI"));
        show("isPalindrome(\"racecar\")",     NativeMath.isPalindrome("racecar"));
        show("isPalindrome(\"hello\")",       NativeMath.isPalindrome("hello"));
        show("countVowels(\"Hello World\")",  NativeMath.countVowels("Hello World"));
        show("countVowels(\"rhythms\")",      NativeMath.countVowels("rhythms"));

        // ── Array operations ────────────────────────────────────────────────
        header("Array Operations (C++ implementation)");
        double[] a = {1.0, 2.0, 3.0};
        double[] b = {4.0, 5.0, 6.0};
        show("dotProduct([1,2,3],[4,5,6])", NativeMath.dotProduct(a, b));

        double[] unsorted = {5.1, 2.3, 8.7, 1.0, 9.9, 3.4};
        double[] sorted   = NativeMath.sortDescending(unsorted);
        show("sortDescending([5.1,2.3,8.7,…])", Arrays.toString(sorted));

        System.out.println("\n============================================");
        System.out.println("  All native calls completed successfully!");
        System.out.println("============================================");
    }
}
