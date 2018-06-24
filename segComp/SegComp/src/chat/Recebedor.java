package chat;

import java.io.IOException;
import java.io.ObjectInputStream;

import javax.swing.JTextArea;

import cipherModes.CipherMode;

public class Recebedor implements Runnable {

    private ObjectInputStream servidor;
    private JTextArea _textArea;
    private CipherMode cipherMode;
    public Recebedor(ObjectInputStream servidor, JTextArea pJTextArea, CipherMode pCipherMode) 
    {
        this.servidor = servidor;
        _textArea = pJTextArea;
        cipherMode = pCipherMode;
    }

    public synchronized void run() {
        // recebe msgs do servidor e imprime na tela
        Message pmsg;
        try
        {
            while(true)
            {
                pmsg = (Message) servidor.readObject();
                if(pmsg != null)
                {
                    System.out.println("recebendo msg do servidor");
                    String line = pmsg.cipherMode.makePlainText(pmsg.msg);
                    _textArea.append(line);
                    _textArea.append("\n");
                }
            }
        } catch (Exception e)
        {
            // TODO Auto-generated catch block
            try
            {
                servidor.close();
            } catch (IOException e1)
            {
                // TODO Auto-generated catch block
                e1.printStackTrace();
            }
       
        }
        
    }
}
