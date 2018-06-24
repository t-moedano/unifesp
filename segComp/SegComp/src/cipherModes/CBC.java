package cipherModes;

import java.io.Serializable;
import java.util.Random;

import org.apache.commons.lang3.RandomStringUtils;

import encryptors.KeyGenerator;
import encryptors.Permutator;
import encryptors.SDes;

public class CBC implements CipherMode, Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = 247771904663159735L;
    SDes sDes = new SDes();
    BinaryGenerator binaryGenerator = new BinaryGenerator();
    KeyGenerator keyGenerator = new KeyGenerator();
    Permutator permutator = new Permutator();
    private String initializationVector;
    String _initialBin = RandomStringUtils.random(10, "10");
    String _key1 = keyGenerator.generateK1(_initialBin);
    String _key2 = keyGenerator.generateK1(_initialBin);
    private static int VECTOR_LENGTH = 8;
    
    public CBC()
    {
        initializationVector = generateInitializationVector();
    }

    @Override
    public synchronized String makeCipher(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        
        String keyToMakeXOR = initializationVector;
        for(char character : pString.toCharArray())
        {
            String plainText = binaryGenerator.toBinary(character);
            String plainTextMixed = permutator.applyXOR(plainText, keyToMakeXOR);
            String cipherText = sDes.encrypt(plainTextMixed, _key1, _key2);
            String letter = binaryGenerator.toLetter(cipherText);
            keyToMakeXOR = cipherText;
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }

    @Override
    public synchronized String makePlainText(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        String key1 = keyGenerator.generateK1(_initialBin);
        String key2 = keyGenerator.generateK2(_initialBin);
        
        String keyToMakeXOR = initializationVector;
        for(char character : pString.toCharArray())
        {
            String cipherText = binaryGenerator.toBinary(character);
            String plainTextMixed = sDes.decrypt(cipherText, _key1, _key2);
            String plainText = permutator.applyXOR(plainTextMixed, keyToMakeXOR);
            String letter = binaryGenerator.toLetter(plainText);
            keyToMakeXOR = cipherText;
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }
    
    public synchronized String generateInitializationVector()
    {
        StringBuilder stringBuilder = new StringBuilder();
        for(int i = 0; i < VECTOR_LENGTH; i++)
        {
            Random random = new Random();
            int number = random.nextInt(2);
            stringBuilder.append(String.valueOf(number));
        }
        return stringBuilder.toString();
    }


}
