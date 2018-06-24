package cipherModes;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.apache.commons.lang3.RandomStringUtils;

import encryptors.KeyGenerator;
import encryptors.Permutator;
import encryptors.SDes;

public class CTR implements CipherMode, Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = 4700334376751306191L;
    SDes sDes = new SDes();
    BinaryGenerator binaryGenerator = new BinaryGenerator();
    Permutator permutator = new Permutator();
    private String initializationVector;
    List<String> initVectors = new ArrayList<>();
    private static int VECTOR_LENGTH = 8;
    String _initialBin = RandomStringUtils.random(10, "10");
    KeyGenerator keyGenerator = new KeyGenerator();
    String _key1 = keyGenerator.generateK1(_initialBin);
    String _key2 = keyGenerator.generateK1(_initialBin);
    
    public CTR()
    {
        initializationVector = generateInitializationVector();
        initVectors.add(initializationVector);
    }
 
    @Override
    public String makeCipher(String pString)
    {
        StringBuilder stringBuilder = new StringBuilder();

        
        String keyToMakeXOR = initializationVector;
        int count = 1;
        
        for(char character : pString.toCharArray())
        {
            String plainText = binaryGenerator.toBinary(character);
            String cipherResult = sDes.encrypt(keyToMakeXOR, _key1, _key2);
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

        
        String keyToMakeXOR = initVectors.get(0);
        for(char character : pString.toCharArray())
        {
            String cipherText = binaryGenerator.toBinary(character);
            String cipherResult = sDes.encrypt(keyToMakeXOR, _key1, _key2);
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
