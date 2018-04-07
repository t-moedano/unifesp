package cipherModeTest;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.apache.commons.lang3.StringUtils;
import org.junit.Test;

import cipherModes.CBC;

public class CBCTest
{

    private CBC cbc = new CBC();

    @Test
    public void testCreateInitiliazionVector()
    {
      String initVector = cbc.generateInitializationVector();
      assertEquals(8, initVector.length());
      assertTrue(StringUtils.countMatches(initVector, "0") + StringUtils.countMatches(initVector, "1") == 8);
    }
}
