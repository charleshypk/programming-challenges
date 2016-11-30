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
    
}