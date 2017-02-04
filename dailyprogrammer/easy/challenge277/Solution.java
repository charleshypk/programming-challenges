public class Solution {

    public static void main(String args[]) {

    }

    public static int[] simplifyFraction(int[] fraction) {
        if (fraction.length != 2) {
            return fraction;
        }

        int numerator = fraction[0];
        int denominator = fraction[1];
        int gcd = gcd(numerator, denominator);

        return new int[] {numerator / gcd, denominator / gcd};
    }

    // Euclid's algorithm
    private static int gcd(int a, int b) {
        return (a == 0 || b == 0) ? Math.max(a, b) : gcd(b, a % b);
    }

}