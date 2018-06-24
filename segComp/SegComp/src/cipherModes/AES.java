package cipherModes;

import java.io.Serializable;
import java.util.Base64;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.lang3.RandomStringUtils;

public class AES implements CipherMode, Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = 2217875748821409781L;
    String _initVector = RandomStringUtils.random(16, "abcedfghijklmnopqrstuvxwyz"); 
    String _key = RandomStringUtils.random(16, "abcedfghijklmnopqrstuvxwyz"); ;


    @Override
    public String makeCipher(String pString)
    {
        byte[] cipherString = null;
        try
        {
            IvParameterSpec iv = new IvParameterSpec(_initVector.getBytes("UTF-8"));
            SecretKeySpec skeySpec = new SecretKeySpec(_key.getBytes("UTF-8"), "AES");

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING");
            cipher.init(Cipher.ENCRYPT_MODE, skeySpec, iv);

            cipherString = cipher.doFinal(pString.getBytes());
        }
        catch(Exception e)
        {
            e.printStackTrace();
            System.out.println("Not possible to encode");
        }
        return Base64.getEncoder().encodeToString(cipherString);
    }

    @Override
    public String makePlainText(String pString)
    {
        byte[] plainText = null;
        try 
        {
            IvParameterSpec iv = new IvParameterSpec(_initVector.getBytes("UTF-8"));
            SecretKeySpec skeySpec = new SecretKeySpec(_key.getBytes("UTF-8"), "AES");

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING");
            cipher.init(Cipher.DECRYPT_MODE, skeySpec, iv);

            plainText = cipher.doFinal(Base64.getDecoder().decode(pString));

        } catch (Exception e) 
        {
            System.out.println("Not possible to decode");
        }
        return new String(plainText);
    }


}
