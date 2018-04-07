package algorithms;

import java.text.Normalizer;
import java.util.regex.Pattern;

public class Cesar
{
    public static String ALPHABETIC = "abcdefghijklmnopqrstuvwxyz";
    
    /**
     * @param pText
     * @param pKey
     * @return
     */
    public String encrypt(String pText, int pKey)
    {
        StringBuilder stringBuilder = new StringBuilder();
        String pNormalizedText = deAccent(pText);
        for(int i = 0; i < pNormalizedText.length(); ++i)
        {
            boolean isUppercase = false;
            char letter = pNormalizedText.charAt(i);
            if(!Character.isWhitespace(letter))
            {
                if(Character.isUpperCase(letter))
                {
                    letter = Character.toLowerCase(letter);
                    isUppercase = true;
                }
                char newLetter = findNewChar(letter, isUppercase, pKey);
                stringBuilder.append(newLetter);
            }
            else
            {
                stringBuilder.append(letter);
            }
        }
        return stringBuilder.toString();
    }
    
    /**
     * @param letter
     * @param pIsUppercase
     * @param pKey
     * @return
     */
    public char findNewChar(char letter, boolean pIsUppercase, int pKey)
    {
        int position = ALPHABETIC.indexOf(letter);
        int newPosition = position+pKey;
        if(position + pKey >= 26)
        {
            newPosition = 26 - position - pKey;
        }
        char newLetter = ALPHABETIC.charAt(newPosition);
        
        if(pIsUppercase)
        {
            newLetter = Character.toUpperCase(newLetter);
        }
        
        return newLetter;
    }
    
    /**
     * This method remove all the accents from the text and replace the character 'ç' for 'c'
     * @param pText
     *          The text to be processed.
     * @return
     *          The text without accents and 'ç'
     */
    public String deAccent(String pText) 
    {
        String nfdNormalizedString = Normalizer.normalize(pText, Normalizer.Form.NFD); 
        Pattern pattern = Pattern.compile("\\p{InCombiningDiacriticalMarks}+");
        return pattern.matcher(nfdNormalizedString).replaceAll("");
    }
}
    