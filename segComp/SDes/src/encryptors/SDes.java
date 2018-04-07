package encryptors;

/**
 * @author Thauany Moedano, Henrique Haji 
 *
 */
public class SDes
{

    Permutator permutator = new Permutator();
    public static int START_INDEX_SUBSTRING_RIGHT = 4;
    public static int END_INDEX_SUBSTRING_RIGHT = 8;
    public static int START_INDEX_SUBSTRING_LEFT = 0;
    public static int END_INDEX_SUBSTRING_LEFT = 4;
    
    
    public String decrypt(String pString, String pKey1, String pKey2)
    {
        String stringPermuted = permutator.ip(pString);
        String processedRightSide = processRightSide(stringPermuted, pKey2);
        String processedLeftSide = processLeftSide(stringPermuted, processedRightSide);
        
        String firstFinalString = permutator.applySwitch(processedLeftSide);
        
        String secondProcessedRightSide = processRightSide(firstFinalString, pKey1);
        String secondProcessedLeftSide = processLeftSide(firstFinalString, secondProcessedRightSide);
        
        String decryptText = permutator.ipReverse(secondProcessedLeftSide);
        return decryptText;
    }
    
    public String encrypt(String pString, String pKey1, String pKey2)
    {
        String stringPermuted = permutator.ip(pString);
        String processedRightSide = processRightSide(stringPermuted, pKey1);
        String processedLeftSide = processLeftSide(stringPermuted, processedRightSide);
        
        String firstFinalString = permutator.applySwitch(processedLeftSide);
        
        String secondProcessedRightSide = processRightSide(firstFinalString, pKey2);
        String secondProcessedLeftSide = processLeftSide(firstFinalString, secondProcessedRightSide);
        
        String encryptText = permutator.ipReverse(secondProcessedLeftSide);
        return encryptText;
    }
   
    
    
    /**
     * Given the right substring from the given string, process this string.
     * @param pRightString
     * @param pKey
     * @return
     */
    public String processRightSide(String pString, String pKey)
    {
        String subStringRight = pString.substring(START_INDEX_SUBSTRING_RIGHT, END_INDEX_SUBSTRING_RIGHT);
        
        String permutedRight = permutator.expandPermute(subStringRight);
        String permutedXOR = permutator.applyXOR(permutedRight, pKey);
        
        String permutedXORRight = permutedXOR.substring(START_INDEX_SUBSTRING_RIGHT, END_INDEX_SUBSTRING_RIGHT);
        String permutedXORLeft = permutedXOR.substring(START_INDEX_SUBSTRING_LEFT, END_INDEX_SUBSTRING_LEFT);
        
        String s0BoxString = permutator.applyS0Box(permutedXORLeft);
        String s1BoxString = permutator.applyS1Box(permutedXORRight);
        
        String stringBoxesConcat = s0BoxString.concat(s1BoxString);
        String stringPermutP4 = permutator.permutP4(stringBoxesConcat);
        
        return stringPermutP4;
    }
    
    public String processLeftSide(String pString, String processedRightSide)
    {
        String subStringLeft = pString.substring(START_INDEX_SUBSTRING_LEFT, END_INDEX_SUBSTRING_LEFT);
        String subStringRight = pString.substring(START_INDEX_SUBSTRING_RIGHT, END_INDEX_SUBSTRING_RIGHT);
        
        String permutBoxXOR = permutator.applyXOR(processedRightSide, subStringLeft);
        
        String stringConcat = permutBoxXOR.concat(subStringRight);
        
        return stringConcat;
    }
}
