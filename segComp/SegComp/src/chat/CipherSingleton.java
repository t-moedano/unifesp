package chat;

import org.apache.commons.lang3.RandomStringUtils;

import cipherModes.AES;
import cipherModes.CBC;
import cipherModes.CTR;
import cipherModes.DH;
import cipherModes.ECB;
import cipherModes.RC4;
import cipherModes.RSA;

public class CipherSingleton
{

    RC4 rc4;
    AES aes;
    CBC cbc;
    ECB ecb;
    CTR ctr;
    DH client;
    RSA rsa;


    public RC4 getRc4()
    {
        return rc4;
    }

    public AES getAes()
    {
        return aes;
    }

    public CBC getCbc()
    {
        return cbc;
    }

    public ECB getEcb()
    {
        return ecb;
    }

    public CTR getCtr()
    {
        return ctr;
    }

    public DH getDhClient()
    {
        return client;
    }
    
    public RSA getRSA()
    {
        return rsa;
    }

    private static CipherSingleton instance = new CipherSingleton();

    private CipherSingleton()
    {
        rc4 = new RC4();
        aes = new AES();
        cbc = new CBC();
        ecb = new ECB();
        ctr = new CTR();
        client = new DH();
        rsa = new RSA();
    }
    
    public static CipherSingleton getInstance(){
        return instance;
    }
    
}
