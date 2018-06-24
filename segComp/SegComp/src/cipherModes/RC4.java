package cipherModes;


import java.io.Serializable;
import java.util.Arrays;

import org.apache.commons.lang3.RandomStringUtils;

public class RC4 implements CipherMode, Serializable {
    /**
     * 
     */
    private static final long serialVersionUID = -7842096387565796922L;
    private final int[] S = new int[256];
    private final byte[] T = new byte[256];
    byte[] key;
    private  int keylen;
 

    public RC4(byte[] pKey)
    {
        key = pKey;
        keylen = key.length;
    }
    public void reset() {
        Arrays.fill(S, 0);
    }


    public RC4()
    {
     key = RandomStringUtils.random(8, "abcedfghijklmnopqrstuvwzxy").getBytes();
       keylen = key.length;
    }
    public String makeCipher(String texto) {
        reset();
        initS();
        byte[] textoByte = texto.getBytes();
        final byte[] texto_cifrado = new byte[textoByte.length];
        int i = 0, j = 0, k, t;
        int aux;
        for (int cont = 0; cont < textoByte.length; cont++) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            aux = S[j];
            S[j] = S[i];
            S[i] = aux;
            t = (S[i] + S[j]) % 256;
            k = S[t];
            texto_cifrado[cont] = (byte) (k ^ textoByte[cont]);
        }
        return new String(texto_cifrado);
    }

    public String makePlainText(String texto_cifrado) {
        reset();
        initS();
        return makeCipher(texto_cifrado);
    }

    public void initS() {
        for (int i=0;i<256;i++) {
            S[i] = i;
            T[i] = key[i % keylen];
        }

        int j = 0;
        int aux;
        for (int i = 0; i < 256; i++) {
            j = (j + S[i] + T[i]) % 256;
            aux = S[j];
            S[j] = S[i];
            S[i] = aux;
        }
    }

}

