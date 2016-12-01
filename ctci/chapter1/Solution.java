import java.util.HashMap;
import java.util.Map;

public class Solution {

    public static void main(String args[]) {

    }

    // Question 1
    public static boolean isEachCharUnique(String str) {
        int strLen = str.length();
        if (strLen == 0 || strLen == 1) return true;
        if (strLen > 128) return false;

        boolean[] characters = new boolean[256];
        for (char c : str.toCharArray()) {
            if (characters[c]) return false;
            characters[c] = true;
        }
        return true;
    }

    // Question 2
    public static boolean isPermutation(String str1, String str2) {
        if (str1.length() != str2.length()) return false;

        int[] letters = new int[128];
        for (char c : str1.toCharArray()) {
            letters[c]++;
        }

        for (char c : str2.toCharArray()) {
            letters[c]--;
            if (letters[c] < 0) {
                return false;
            }
        }
        return true;
    }

    // Question 3
    public static String replaceSpace(String str) {
        StringBuffer strBuf = new StringBuffer();
        for (char c : str.toCharArray()) {
            if (c == ' ') strBuf.append("%20");
            else strBuf.append(c);
        }

        return strBuf.toString();
    }

    // Question 4
    public static boolean isPalindromePermutation(String str) {
        str = str.replaceAll("\\s", "");

        Map<Character, Boolean> charParity = new HashMap<>();
        for (char c : str.toCharArray()) {
            c = Character.toLowerCase(c);
            if (charParity.containsKey(c)) charParity.put(c, !charParity.get(c));  // Flipping value to match parity
            else charParity.put(c, true);  // Value equals true if parity is odd
        }

        int numOdd = 0;
        for (Character key : charParity.keySet()) {
            if (charParity.get(key)) numOdd++;
        }

        if (numOdd > 1) return false;
        if (str.length() % 2 == 0) return numOdd == 0;
        return numOdd == 1;
    }

}