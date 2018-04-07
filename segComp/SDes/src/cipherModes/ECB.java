package cipherModes;

import encryptors.KeyGenerator;
import encryptors.SDes;

public class ECB implements CipherMode
{

    SDes sDes = new SDes();
    BinaryGenerator binaryGenerator = new BinaryGenerator();

    @Override
    public String makeCipher(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        String key1 = keyGenerator.generateK1("1001100011");
        String key2 = keyGenerator.generateK2("1001100011");
        
        for(char character : pString.toCharArray())
        {
            String plainText = binaryGenerator.toBinary(character);
            String cipherText = sDes.encrypt(plainText, key1, key2);
            String letter = binaryGenerator.toLetter(cipherText);
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }
    
    public String makePlainText(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        String key1 = keyGenerator.generateK1("1001100011");
        String key2 = keyGenerator.generateK2("1001100011");
        
        for(char character : pString.toCharArray())
        {
            String cipherText = binaryGenerator.toBinary(character);
            String plainText = sDes.decrypt(cipherText, key1, key2);
            String letter = binaryGenerator.toLetter(plainText);
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }

   

}
