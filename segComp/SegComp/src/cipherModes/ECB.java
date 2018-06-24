package cipherModes;

import java.io.Serializable;

import org.apache.commons.lang3.RandomStringUtils;

import encryptors.KeyGenerator;
import encryptors.SDes;

public class ECB implements CipherMode, Serializable
{
    String _initialBin = RandomStringUtils.random(10, "10");
    KeyGenerator keyGenerator = new KeyGenerator();
    String _key1 = keyGenerator.generateK1(_initialBin);
    String _key2 = keyGenerator.generateK1(_initialBin);

    /**
     * 
     */
    private static final long serialVersionUID = 4508965065827796481L;
    /**
     * 
     */
    SDes sDes = new SDes();
    BinaryGenerator binaryGenerator = new BinaryGenerator();

    @Override
    public String makeCipher(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

      
        
        for(char character : pString.toCharArray())
        {
            String plainText = binaryGenerator.toBinary(character);
            String cipherText = sDes.encrypt(plainText, _key1, _key2);
            String letter = binaryGenerator.toLetter(cipherText);
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }
    
    public String makePlainText(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        
        for(char character : pString.toCharArray())
        {
            String cipherText = binaryGenerator.toBinary(character);
            String plainText = sDes.decrypt(cipherText, _key1, _key2);
            String letter = binaryGenerator.toLetter(plainText);
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }


   

}
