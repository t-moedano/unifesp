package encryptorsTest;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import encryptors.KeyGenerator;

/**
 * @author Thauany Moedano, Henrique Haji
 *
 */
public class KeyGeneratorTest
{

    public KeyGenerator keyGenerator = new KeyGenerator();
    
    @Test
    public void testK1Generation()
    {
        String key = "1010000010";
        String result = keyGenerator.generateK1(key);
        String expectedKey = "10100100";
        assertEquals(expectedKey, result);
    }
    
    @Test
    public void testK2Generation()
    {
        String key = "1010000010";
        String result = keyGenerator.generateK2(key);
        String expectedKey = "01000011";
        assertEquals(expectedKey, result);
    }
    
    
}
