package cipherModeTest;

import static org.junit.Assert.*;

import org.junit.Test;

import cipherModes.BinaryGenerator;

public class BinaryGeneratorTest
{

    private BinaryGenerator binaryGenerator = new BinaryGenerator();
    
    @Test
    public void testCipherMode()
    {
        String letter = binaryGenerator.toLetter("01100001");
        assertEquals("a", letter);
    }
}
