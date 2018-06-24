package encryptorsTest;

import static org.junit.Assert.*;
import org.junit.Test;

import encryptors.Permutator;

/**
 * @author Thauany Moedano, Henrique Haji
 * Test Class to Permutator.
 *
 */
public class PermutatorTest
{
    Permutator permutator = new Permutator();
    
    /**
     * Test if permutation occurs correctly; 
     */
    @Test
    public void testPermut()
    {
        String toPermut = "01100110";
        String afterPermut = "11100001";
        String permuted = permutator.ip(toPermut);
        assertEquals(afterPermut, permuted);
    }
    
    /**
     * Test if reverse permutation occurs correctly. 
     */
    @Test
    public void testPermutReverse()
    {
        String toPermut = "10011010";
        String afterPermut = "11011000";
        String permuted = permutator.ipReverse(toPermut);
        assertEquals(afterPermut, permuted);
    }
    
    /**
     * Test if expand/permut operation occurs correctly.
     */
    @Test
    public void testExpandPermut()
    {
        String toExpandPermut = "0101";
        String afterExpandPermut = "10101010";
        String permuted = permutator.expandPermute(toExpandPermut);
        assertEquals(afterExpandPermut, permuted);
    }
    
    /**
     * Test if exclusive or operation works fine. 
     */
    @Test
    public void testExclusiveOr()
    {
        String key = "10000001";
        String subStringRight = "00101011";
        String afterPermut = "10101010";
        String permuted = permutator.applyXOR(subStringRight, key);
        assertEquals(afterPermut, permuted);
    }
    
    /**
     * Test if S0 Box operation works. 
     */
    @Test
    public void testS0BoxOperation()
    {
        String toOperate = "0010";
        String afterOperation = "00";
        String permuted = permutator.applyS0Box(toOperate);
        assertEquals(afterOperation, permuted);
    }
    
    /**
     * Tets if S1 Box Operation works. 
     */
    @Test
    public void testS1BoxOperation()
    {
        String toOperate = "1011";
        String afterOperation = "01";
        String permuted = permutator.applyS1Box(toOperate);
        assertEquals(afterOperation, permuted);
    }
    
    /**
     * Test if permut P4 works fine
     */
    @Test
    public void testPermutP4()
    {
        String toPermut = "0001";
        String afterPermut = "0100";
        String permuted = permutator.permutP4(toPermut);
        assertEquals(afterPermut, permuted);
    }
    
    /**
     * Test if switch operation works fine.
     */
    @Test
    public void testSwitch()
    {
        String toSwitch = "11011001";
        String afterSwitch = "10011101";
        String permuted = permutator.applySwitch(toSwitch);
        assertEquals(permuted, afterSwitch);
    }
}
