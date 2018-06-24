package cipherModes;

import java.io.Serializable;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.Signature;
import java.util.Base64;

import javax.crypto.Cipher;

public class RSA implements CipherMode, Serializable
{

    /**
     * 
     */
    private static final long serialVersionUID = 3498738258133944362L;
    KeyPair _keyPair;
    PrivateKey _privateKey;
    PublicKey _publicKey;

    public RSA()
    {
        KeyPairGenerator generator;
        try
        {
            generator = KeyPairGenerator.getInstance("RSA");
            generator.initialize(2048, new SecureRandom());
            _keyPair = generator.generateKeyPair();
            _privateKey = _keyPair.getPrivate();
            _publicKey = _keyPair.getPublic();
        } catch (NoSuchAlgorithmException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public String makeCipher(String pString)
    {
        Signature privateSignature;
        byte[] signature = null;
        byte[] cipherText = null;
        try
        {
            Cipher encryptCipher = Cipher.getInstance("RSA");
            encryptCipher.init(Cipher.ENCRYPT_MODE, _publicKey);

            cipherText = encryptCipher.doFinal(pString.getBytes("UTF-8"));

            privateSignature = Signature.getInstance("SHA256withRSA");
            privateSignature.initSign(_privateKey);
            privateSignature.update(pString.getBytes("UTF-8"));
            signature = privateSignature.sign();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
        return Base64.getEncoder().encodeToString(signature) + "|" + Base64.getEncoder().encodeToString(cipherText);
    }

    @Override
    public String makePlainText(String pString)
    {
        String msg[] = pString.split("[\\|]+");
        String signature = msg[0];
        String cipherText = msg[1];
        Signature publicSignature;
        try
        {
            byte[] bytes = Base64.getDecoder().decode(cipherText);
            
            Cipher decriptCipher = Cipher.getInstance("RSA");
            decriptCipher.init(Cipher.DECRYPT_MODE,_privateKey);
            
            String plainText = new String(decriptCipher.doFinal(bytes));
            publicSignature = Signature.getInstance("SHA256withRSA");
            publicSignature.initVerify(_publicKey);
            publicSignature.update(plainText.getBytes("UTF-8"));
            byte[] signatureBytes = Base64.getDecoder().decode(signature);
            if(publicSignature.verify(signatureBytes))
            {
               return plainText;
            }
        } catch (Exception e)
        {
            e.printStackTrace();
        }
        return null;
    }
}
