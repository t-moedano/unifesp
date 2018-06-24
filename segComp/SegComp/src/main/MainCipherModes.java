package main;

import org.apache.commons.lang3.RandomStringUtils;

import cipherModes.AES;
import cipherModes.CBC;
import cipherModes.CTR;
import cipherModes.DH;
import cipherModes.ECB;
import cipherModes.RC4;
import cipherModes.RSA;

public class MainCipherModes
{

    public static void main(String[] args)
    {
        System.out.println("EBC");
        ECB ecb = new ECB();
        String string = "Time 02 melhor time 02";
        String cipherString = ecb.makeCipher(string);
        System.out.println(cipherString);
        String decrypt = ecb.makePlainText(cipherString);
        System.out.println(decrypt);

        System.out.println("CBC");
        CBC cbc = new CBC();
        String stringCBC = "Time 02 melhor time 02";
        String cipherStringCBC = cbc.makeCipher(stringCBC);
        System.out.println(cipherStringCBC);
        String decryptCBC = cbc.makePlainText(cipherStringCBC);
        System.out.println(decryptCBC);

        System.out.println("CTR");
        CTR ctr = new CTR();
        String stringCTR = "Time 02 melhor time 02";
        String cipherStringCTR = ctr.makeCipher(stringCTR);
        System.out.println(cipherStringCTR);
        String decryptCTR = ctr.makePlainText(cipherStringCTR);
        System.out.println(decryptCTR);

        System.out.println("RC4");
        String stringRC4 = "Time 02 melhor time 02";
        RC4 rc4 = new RC4();
        String cipherStringRC4 = rc4.makeCipher(stringRC4);
        System.out.println(cipherStringRC4);
        String decryptRC4 = rc4.makePlainText(cipherStringRC4);
        System.out.println(decryptRC4);
        
        System.out.println("AES");
        AES aes = new AES();
        String stringAES = "Time 02 melhor time 02";
        String cipherStringAES = aes.makeCipher(stringAES);
        System.out.println(cipherStringAES);
        String decryptAES = aes.makePlainText(cipherStringAES);
        System.out.println(decryptAES);

        System.out.println("DH");
        DH dh = new DH();
        String text = dh.makeCipher("Time 02 melhor time 02");
        System.out.println(text);
        String textDec = dh.makePlainText(text);
        System.out.println(textDec);

        System.out.println("RSA + SHA");
        RSA rsa = new RSA();
        String textRSA = "Time 02 melhor time 02";
        String codedRSA = rsa.makeCipher(textRSA);
        System.out.println(codedRSA);
        String decodedRSA = rsa.makePlainText(codedRSA);
        System.out.println(decodedRSA);
    }
}
