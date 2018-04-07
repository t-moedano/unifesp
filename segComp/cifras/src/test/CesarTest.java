package test;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import algorithms.Cesar;

public class CesarTest
{
    public Cesar cesar = new Cesar();

    /**
     * Test if the accents of the text is correctly removed. 
     */
    @Test
    public void testDeAccent()
    {
        String text = "Esse é o texto que não tem intenção de ser cheio de acentos";
        String deAccentText = "Esse e o texto que nao tem intencao de ser cheio de acentos";
        String result = cesar.deAccent(text);
        assertEquals(deAccentText, result);
    }

    /**
     * Test is the method gets the correct char using the Cesar algorithm.
     */
    @Test
    public void testFindCharLowerCase()
    {
        char letter = 'b';
        int key = 3;
        boolean isUppercase = false;
        char newLetter = cesar.findNewChar(letter, isUppercase, key);
        assertEquals('e', newLetter);
    }
    
    /**
     * Test is the method get the correct char when flag for uppercase is true.
     */
    @Test
    public void testFindCharUpperCase()
    {
        char letter = 'b';
        int key = 3;
        boolean isUppercase = true;
        char newLetter = cesar.findNewChar(letter, isUppercase, key);
        assertEquals('E', newLetter);
    }
 
    /**
     * Test if the text is correctly encrypt.
     */
    @Test
    public void testCesar()
    {
        String text = "Brasil Hexa é real";
        int key = 3;
        String encryptText = "Eudvlo Khad h uhdo";
        String result = cesar.encrypt(text, key);
        assertEquals(result, encryptText);
    }
}
