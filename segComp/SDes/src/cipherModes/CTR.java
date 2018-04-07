package cipherModes;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import encryptors.KeyGenerator;
import encryptors.Permutator;
import encryptors.SDes;

public class CTR implements CipherMode
{

    SDes sDes = new SDes();
    BinaryGenerator binaryGenerator = new BinaryGenerator();
    Permutator permutator = new Permutator();
    private String initializationVector;
    List<String> initVectors = new ArrayList<>();
    private static int VECTOR_LENGTH = 8;
    
    public CTR()
    {
        initializationVector = generateInitializationVector();
        initVectors.add(initializationVector);
    }
 
    @Override
    public String makeCipher(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        KeyGenerator keyGenerator = new KeyGenerator();
        String key1 = keyGenerator.generateK1("1001100011");
        String key2 = keyGenerator.generateK2("1001100011");
        
        String keyToMakeXOR = initializationVector;
        int count = 1;
        
        for(char character : pString.toCharArray())
        {
            String plainText = binaryGenerator.toBinary(character);
            String cipherResult = sDes.encrypt(keyToMakeXOR, key1, key2);
            String cipherText = permutator.applyXOR(plainText, cipherResult);
            String letter = binaryGenerator.toLetter(cipherText);
            
            String countString = binaryGenerator.toBinary(String.valueOf(count).charAt(0));
            keyToMakeXOR = Integer.toBinaryString(Integer.parseInt(countString, 2) + Integer.parseInt(keyToMakeXOR, 2));
            
            StringBuilder stringExpand = new StringBuilder();
            stringExpand.append(keyToMakeXOR);
            while(stringExpand.length() < 8)
            {
                stringExpand.append("0");
            }
            keyToMakeXOR = stringExpand.toString();
            keyToMakeXOR = keyToMakeXOR.substring(0, 8);
            
            
            count++;
            initVectors.add(keyToMakeXOR);
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
        
        String keyToMakeXOR = initVectors.get(0);
        for(char character : pString.toCharArray())
        {
            String cipherText = binaryGenerator.toBinary(character);
            String cipherResult = sDes.encrypt(keyToMakeXOR, key1, key2);
            String plainText = permutator.applyXOR(cipherText, cipherResult);
            String letter = binaryGenerator.toLetter(plainText);
            initVectors.remove(0);
            keyToMakeXOR = initVectors.get(0);
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
