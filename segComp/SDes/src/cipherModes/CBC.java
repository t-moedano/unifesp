package cipherModes;

import java.util.Random;

import encryptors.KeyGenerator;
import encryptors.Permutator;
import encryptors.SDes;

public class CBC implements CipherMode
{

    SDes sDes = new SDes();
    BinaryGenerator binaryGenerator = new BinaryGenerator();
    Permutator permutator = new Permutator();
    private String initializationVector;
    private static int VECTOR_LENGTH = 8;
    
    public CBC()
    {
        initializationVector = generateInitializationVector();
    }

    @Override
    public String makeCipher(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        String key1 = keyGenerator.generateK1("1001100011");
        String key2 = keyGenerator.generateK2("1001100011");
        
        String keyToMakeXOR = initializationVector;
        for(char character : pString.toCharArray())
        {
            String plainText = binaryGenerator.toBinary(character);
            String plainTextMixed = permutator.applyXOR(plainText, keyToMakeXOR);
            String cipherText = sDes.encrypt(plainTextMixed, key1, key2);
            String letter = binaryGenerator.toLetter(cipherText);
            keyToMakeXOR = cipherText;
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }

    @Override
    public String makePlainText(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        String key1 = keyGenerator.generateK1("1001100011");
        String key2 = keyGenerator.generateK2("1001100011");
        
        String keyToMakeXOR = initializationVector;
        for(char character : pString.toCharArray())
        {
            String cipherText = binaryGenerator.toBinary(character);
            String plainTextMixed = sDes.decrypt(cipherText, key1, key2);
            String plainText = permutator.applyXOR(plainTextMixed, keyToMakeXOR);
            String letter = binaryGenerator.toLetter(plainText);
            keyToMakeXOR = cipherText;
            stringBuilder.append(letter);
        }
        return stringBuilder.toString();
    }
    
    public String generateInitializationVector()
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
