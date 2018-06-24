package cipherModes;

import java.io.Serializable;

public class BinaryGenerator implements Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = 2257274523780647696L;

    public String toBinary(char character)
    {
        String binaryCharString = Integer.toBinaryString(character);
        while(binaryCharString.length() < 8)
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.append("0").append(binaryCharString);
            binaryCharString = stringBuilder.toString();
        }
        return binaryCharString;
    }
    
    public String toLetter(String pBinaryChar)
    {
        int charCode = Integer.parseInt(pBinaryChar, 2);
        return new Character((char)charCode).toString();
    }
}
