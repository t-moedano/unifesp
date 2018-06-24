package encryptors;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;

/**
 * @author Thauany Moedano, Henrique Haji  
 *         
 * This class contains the operations necessary to apply S-DES algorithm
 *
 */
public class Permutator implements Serializable
{
    /**
     * 
     */
    private static final long serialVersionUID = 1940587789306892730L;
    public static List<Integer> PERMUTATOR_STRING = Arrays.asList(1,5,2,0,3,7,4,6);
    public static List<Integer> PERMUTATOR_STRING_INVERSE = Arrays.asList(3,0,2,4,6,1,7,5); 
    public static List<Integer> EXPAND_PERMUT = Arrays.asList(3,0,1,2,1,2,3,0);
    public static List<Integer> PERMUTATOR_P4 = Arrays.asList(1,3,2,0);
    public static int[][] S0_BOX = {{1, 0, 3, 2},
                                    {3, 2, 1, 0},
                                    {0, 2, 1, 3},
                                    {3, 1, 3, 2}};
    
    public static int[][] S1_BOX = {{0, 1, 2, 3},
                                    {2, 0, 1, 3},
                                    {3, 0, 1, 0},
                                    {2, 1, 0, 3}};
    
    /**
     * Method to apply the initial permutation (function IP())
     * @param pString
     *          Initial binary string to permut
     * @return
     *      The binary string permuted
     */
    public String ip(String pString)
    {
        StringBuilder permuted = new StringBuilder();
        for(Integer integer : PERMUTATOR_STRING)
        {
            char value = pString.charAt(integer);
            permuted.append(value);
        }
        return permuted.toString();
    }
    
    /**
     * Method to apply the reversal ip (function IP^-1())
     * @param pString
     *          The binary string to be permuted
     * @return
     *          The permuted binary string
     */
    public String ipReverse(String pString)
    {
        StringBuilder permuted = new StringBuilder();
        for(Integer integer : PERMUTATOR_STRING_INVERSE)
        {
            char value = pString.charAt(integer);
            permuted.append(value);
        }
        return permuted.toString();
    }
    
    /**
     * This method expand to eight binary string one four binary string and permut it.
     * @param pString
     *          The string to be expanded and permuted.
     * @return
     *          The binary string expanded and permuted. 
     */
    public String expandPermute(String pString)
    {
        StringBuilder permuted = new StringBuilder();
        for(Integer integer : EXPAND_PERMUT)
        {
            char value = pString.charAt(integer);
            permuted.append(value);
        }
        return permuted.toString();
    }
    
    /**
     * This method apply the XOR operation between a binary string and a binary key.
     * @param pString
     *          The binary string
     * @param key
     *          The binary key
     * @return
     *         The string with XOR operation applied. 
     */
    public String applyXOR(String pString, String key)
    {
        StringBuilder permuted = new StringBuilder();
        for(int i = 0; i < pString.length(); i++)
        {
            permuted.append(pString.charAt(i) ^ key.charAt(i));
        }
        return permuted.toString();
    }
    
    /**
     * This method applies S0 box operation to the given four binary string. 
     * @param pString
     *          The binary string. 
     * @return
     *          The result of S0 box operation.
     */
    public String applyS0Box(String pString)
    {
        StringBuilder stringBuilderRow = new StringBuilder();
        String rowString = stringBuilderRow.append(pString.charAt(0)).append(pString.charAt(3)).toString();
        
        StringBuilder stringBuilderColumn = new StringBuilder();
        String columnString = stringBuilderColumn.append(pString.charAt(1)).append(pString.charAt(2)).toString();
        
        int decimalRightValue = Integer.parseInt(rowString, 2);
        int decimalLeftValue = Integer.parseInt(columnString, 2);
        
        int decimalBoxValue = S0_BOX[decimalRightValue][decimalLeftValue];
        
        if(decimalBoxValue < 2)
        {
            StringBuilder binaryString = new StringBuilder();
            binaryString.append("0").append(Integer.toBinaryString(decimalBoxValue));
            return binaryString.toString();
        }
        return Integer.toBinaryString(decimalBoxValue);
    }
    
    /**
     * This method applies S1 box operation to the given four binary string.
     * @param pString
     *          Four binary string to be operated.
     * @return
     *          The result of S1 box operation.
     */
    public String applyS1Box(String pString)
    {
        StringBuilder stringBuilderRow = new StringBuilder();
        String rowString = stringBuilderRow.append(pString.charAt(0)).append(pString.charAt(3)).toString();
        
        StringBuilder stringBuilderColumn = new StringBuilder();
        String columnString = stringBuilderColumn.append(pString.charAt(1)).append(pString.charAt(2)).toString();
        
        int decimalRightValue = Integer.parseInt(rowString, 2);
        int decimalLeftValue = Integer.parseInt(columnString, 2);
        
        int decimalBoxValue = S1_BOX[decimalRightValue][decimalLeftValue];
        
        if(decimalBoxValue < 2)
        {
            StringBuilder binaryString = new StringBuilder();
            binaryString.append("0").append(Integer.toBinaryString(decimalBoxValue));
            return binaryString.toString();
        }
        return Integer.toBinaryString(decimalBoxValue);
    }
    
    /**
     * @param pString
     * @return
     */
    public String permutP4(String pString)
    {
        StringBuilder permuted = new StringBuilder();
        for(Integer integer : PERMUTATOR_P4)
        {
            char value = pString.charAt(integer);
            permuted.append(value);
        }
        return permuted.toString();
    }
    
    /**
     * Apply switch operation
     * @param pString
     * @return
     */
    public String applySwitch(String pString)
    {
        String stringRight = pString.substring(4,8);
        String stringLeft = pString.substring(0,4);
        
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(stringRight).append(stringLeft);
        
        return stringBuilder.toString();
    }
}
