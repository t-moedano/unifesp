package cipherModes;

import java.io.Serializable;
import java.math.BigInteger;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

import javax.crypto.Cipher;
import javax.crypto.interfaces.DHPrivateKey;
import javax.crypto.interfaces.DHPublicKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.lang3.RandomStringUtils;

public class DH implements CipherMode, Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = -3073441206114078835L;
    private int primeNumber;
    private int secretNumber;
    private int publicKey;
    private static final String word = RandomStringUtils.random(10, "abcdefghijklmnopqrsd");

    public DH()
    {
        KeyPairGenerator kpg = null;
        try
        {
            kpg = KeyPairGenerator.getInstance("DiffieHellman");
        } catch (NoSuchAlgorithmException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        kpg.initialize(512);
        KeyPair dkp = kpg.generateKeyPair();
        secretNumber = (((DHPrivateKey) dkp.getPrivate()).getX()).intValue();
        publicKey  = (((DHPublicKey) dkp.getPublic()).getY()).intValue();
        primeNumber = ((DHPublicKey) dkp.getPublic()).getParams().getP().intValue();
    }
    
    @Override
    public String makeCipher(String pString)
    {
        BigInteger publicKeyBig = new BigInteger(String.valueOf(publicKey));
        BigInteger res = publicKeyBig.modPow(new BigInteger(String.valueOf(secretNumber)), new BigInteger(String.valueOf(primeNumber)));
        int sharedNumber = res.intValue();
        String key = word;
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(key);
        while(stringBuilder.length() < 16)
        {
            stringBuilder.append(sharedNumber);
        }
        
        String finalKey = stringBuilder.toString().substring(0, 16);
        
        
        byte[] cipherString = null;
        try
        {
            IvParameterSpec iv = new IvParameterSpec("dtesteduhfgtdsrq".getBytes("UTF-8"));
            SecretKeySpec skeySpec = new SecretKeySpec(finalKey.getBytes("UTF-8"), "AES");

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
        BigInteger publicKeyBig = new BigInteger(String.valueOf(publicKey));
        BigInteger res = publicKeyBig.modPow(new BigInteger(String.valueOf(secretNumber)), new BigInteger(String.valueOf(primeNumber)));
        int sharedNumber = res.intValue();
        String key = word;
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(key);
        while(stringBuilder.length() <= 15)
        {
            stringBuilder.append(sharedNumber);
        }
        
        String finalKey = stringBuilder.toString().substring(0, 16);
        
        byte[] plainText = null;
        try 
        {
            IvParameterSpec iv = new IvParameterSpec("dtesteduhfgtdsrq".getBytes("UTF-8"));
            SecretKeySpec skeySpec = new SecretKeySpec(finalKey.getBytes("UTF-8"), "AES");

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
