package main;

import cipherModes.CBC;
import cipherModes.CTR;
import cipherModes.ECB;

public class MainCipherModes
{

    public static void main(String[] args)
    {
        System.out.println("EBC");
        ECB ecb = new ECB();
        String string = "oloco";
        String cipherString = ecb.makeCipher(string);
        System.out.println(cipherString);
        String decrypt = ecb.makePlainText(cipherString);
        System.out.println(decrypt);
        
        System.out.println("CBC");
        CBC cbc = new CBC();
        String stringCBC = "lula la";
        String cipherStringCBC = cbc.makeCipher(stringCBC);
        System.out.println(cipherStringCBC);
        String decryptCBC = cbc.makePlainText(cipherStringCBC);
        System.out.println(decryptCBC);
        
        System.out.println("CTR");
        CTR ctr = new CTR();
        String stringCTR = "abcde";
        String cipherStringCTR = ctr.makeCipher(stringCTR);
        System.out.println(cipherStringCTR);
        String decryptCTR = ctr.makePlainText(cipherStringCTR);
        System.out.println(decryptCTR);
        
    }
}
