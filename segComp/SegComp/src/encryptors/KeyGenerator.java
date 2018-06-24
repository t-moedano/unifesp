package encryptors;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;

/**
 * This class generates P10 Keys for S-Des algorithm
 * @author Thauany Moedano, Henrique Haji 
 *
 */
public class KeyGenerator implements Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = -4324892545265889812L;
    public static List<Integer> P08_LIST = Arrays.asList(5, 2, 6, 3, 7, 4, 9, 8);
    public static List<Integer> P10_LIST = Arrays.asList(2, 4, 1, 6, 3, 9, 0, 8, 7, 5);
    
    /**
     * Makes a left bit rotation
     * @param pString
     *          String of bits to rotate
     * @param times
     *          The number of times that the bit must be shifted to left
     * @return
     *          The string of bits rotated
     */
    public String rotateLeft(String pString, int times)
    {
        String subStringLeft = pString.substring(0, 5);
        String subStringRight = pString.substring(5, 10);
        
        //left part
        String left = subStringLeft.substring(0, times);
        String right = subStringLeft.substring(times, subStringLeft.length());
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(right).append(left);
        String leftPart = stringBuilder.toString();
        
        //right part
        String left2 = subStringRight.substring(0, times);
        String right2 = subStringRight.substring(times, subStringRight.length());
        StringBuilder stringBuilder2 = new StringBuilder();
        stringBuilder2.append(right2).append(left2);
        String rightPart = stringBuilder2.toString();
        
        StringBuilder stringBuilderConcat = new StringBuilder();
        stringBuilderConcat.append(leftPart).append(rightPart);
        return stringBuilderConcat.toString();
    }

    /**
     * Generates P10 Key1 for S-Des algorithm
     * @param pString
     *          The given string to make P10 
     * @return
     *          Key1 for S-Des algorithm 
     */
    public String generateK1(String pString)
    {
        StringBuilder permuted = new StringBuilder();
        for(Integer integer : P10_LIST)
        {
            char value = pString.charAt(integer);
            permuted.append(value);
        }
        
        String concatKey = rotateLeft(permuted.toString(), 1);
        
        StringBuilder stringBuilderFinal = new StringBuilder();
        
        for(Integer integer : P08_LIST)
        {
            char value = concatKey.charAt(integer);
            stringBuilderFinal.append(value);
        }
        
        return stringBuilderFinal.toString();
    }
    
    /**
     * Generates P10 Key2 for S-Des Algorithm
     * @param pString
     *          The given string to make P10
     * @return
     *          Key2 for S-Des Algorithm 
     */
    public String generateK2(String pString)
    {
        StringBuilder permuted = new StringBuilder();
        for(Integer integer : P10_LIST)
        {
            char value = pString.charAt(integer);
            permuted.append(value);
        }
        
        String concatKey = rotateLeft(permuted.toString(), 1);
        
        String concatKey2 = rotateLeft(concatKey, 2);
        
        StringBuilder stringBuilderFinal = new StringBuilder();
        
        for(Integer integer : P08_LIST)
        {
            char value = concatKey2.charAt(integer);
            stringBuilderFinal.append(value);
        }
        
        return stringBuilderFinal.toString();
    }
}
