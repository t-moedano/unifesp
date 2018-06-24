//Thauanny Moedano
//Henrique Haji

package main;

import cipherModes.RC4;

import java.util.Arrays;

public class BruteForceRC4 {

    public static final  int BEGIN = 0;
    public static final  int END = 120;

    public static void main(String[] args) {
        String base[] = {"Ola", "Como vai?", "Bom dia!", "Boa Tarde.", "Tudo bem?", "Sim.", "Não.", "Adeus", "Ate logo", "lol",
        ":)",":(","ok","td bem","sem problemas", "tchau", "reuniao", "me liga", "obrigado!", "de nada", "muito obrigado", ":0"};

        RC4 rc4 = new RC4("padrao".getBytes());
        //System.out.println(Arrays.toString("padrao".getBytes()));//[112, 97, 100, 114, 97, 111]
        RC4 rc42;
        String msg = rc4.makeCipher(base[base.length-1]);
        //System.out.println("msg:" + Arrays.toString(msg));
        int flag = 0, count = 6;
        byte[] testKey;

        while(flag < 22) {
            testKey = new byte[count];
            startKey(testKey);
            rc42 = new RC4(testKey);
            String cipherStringRC4;

            //System.out.println(Arrays.toString(testKey));

            boolean stop = false;
            while(testKey[testKey.length-1] <= END && !stop) {
                for (int i = 0; flag < base.length && i < base.length; i++) {
                    //System.out.println(Arrays.toString(rc4.makeCipher(base[i].getBytes())));
                    cipherStringRC4 = rc42.makeCipher(base[i]);

                    if(Arrays.equals("padrao".getBytes(), testKey)) {
                        System.out.println("chave: " + new String(testKey));
                    }

                    if (msg.equals(cipherStringRC4)) {

                        for(int z=0;z<base.length;z++) {
                            cipherStringRC4 = rc42.makeCipher(base[z]);
                            if(rc42.makePlainText(cipherStringRC4).equals(base[z])) {
                                flag++;
                            }
                        }

                        if(flag == 22) {
                            System.out.println("Decifrou: " + Arrays.toString(testKey));
                        }
                    }
                }
                flag = 0;
                stop = iterate(testKey);
            }
            count++;
        }
    }
    public static void startKey(byte[] array) {
        //112, 97, 100, 114, 97, 111
        /*for(int i = 0; i < array.length; i++) {
            array[i] = BEGIN;
        }*/
        array[0] = 0;
        array[1] = 0;
        array[2] = 90;
        array[3] = 114;
        array[4] = 97;
        array[5] = 111;
    }
    public static boolean iterate(byte[] array) {
//        System.out.println(Arrays.toString(array));
        int aux = 1;

        if(array.length == 2) {
            if(array[0] == 110 && array[1] == 61) {
//                System.out.println("asd");
            }
        }

        for(int i = 0; aux == 1 && i < array.length; i++) {
            if(array[i] < END) {
                array[i]++;
                aux = 0;
            }
            else {
                array[i] = BEGIN;
                if(i == array.length -1)
                    return true;
            }
        }
        return false;
    }
}
