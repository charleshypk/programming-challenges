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

    // Question 5
    public static boolean isOneDistanceAway(String str1, String str2) {
        if (str1.length() > str2.length()) return isOneDistanceAway(str2, str1);

        int strLen1 = str1.length(), strLen2 = str2.length();
        if ((strLen2 - strLen1) > 1) return false;

        int index1 = 0, index2 = 0;
        boolean foundIntersection = false;
        while (index1 < strLen1 && index2 < strLen2) {
            if (str1.charAt(index1) != str2.charAt(index2)) {
                if (foundIntersection) return false;
                foundIntersection = true;

                if (strLen1 == strLen2) index1++;  // Shift both indices if edit by replacement
            } else {
                index1++;
            }
            index2++;
        }

        return true;
    }

    // Question 6
    public static String compressString(String str) {
        int strLen = str.length();
        if (strLen < 3) return str;

        StringBuffer compressed = new StringBuffer();
        int numRepeat = 0;
        for (int i = 0; i < strLen; i++) {
            numRepeat++;

            if (i == strLen - 1 || str.charAt(i) != str.charAt(i + 1)) {
                compressed.append(str.charAt(i));
                compressed.append(numRepeat);
                numRepeat = 0;
            }
        }

        return strLen < compressed.length() ? str : compressed.toString();
    }

    // Question 7
    public static void rotateMatrix(int[][] matrix, int size) {
        for (int layer = 0; layer < size / 2; layer++) {
            int first = layer;
            int last = size - layer - 1;

            for (int i = first; i < last; i++) {
                int offset = i - first;
                int top = matrix[first][i];

                // Rotate matrix clockwise by 90 degrees
                matrix[first][i] = matrix[last - offset][first];  // left -> top
                matrix[last - offset][first] = matrix[last][last - offset];  // bottom -> left
                matrix[last][last - offset] = matrix[i][last];  // right -> bottom
                matrix[i][last] = top;  // top -> right
            }
        }
    }

    // Question 8
    public static void zeroMatrix(int[][] matrix, int m, int n) {
        boolean[] rows = new boolean[m];
        boolean[] columns = new boolean[n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    rows[i] = true;
                    columns[j] = true;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            if (rows[i]) clearRow(matrix, n, i);
        }

        for (int j = 0; j < n; j++) {
            if (columns[j]) clearColumn(matrix, m, j);
        }
    }

    private static void clearRow(int[][] matrix, int n, int row) {
        for (int j = 0; j < n; j++) {
            matrix[row][j] = 0;
        }
    }

    private static void clearColumn(int[][] matrix, int m, int col) {
        for (int i = 0; i < m; i++) {
            matrix[i][col] = 0;
        }
    }

}