package chat;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import cipherModes.CipherMode;

public class Cliente {
    
    CipherMode cipherMode;
    public static void main(String[] args) 
                throws UnknownHostException, IOException 
    {
        new Cliente().executa();
    }

    public synchronized void executa() throws UnknownHostException, IOException {
        
        GUI gui = new GUI();
        gui.createClientInterface();
        Socket cliente = new Socket(gui.getIp(), Integer.valueOf(gui.getClientPort()));
        setCipherMode(gui);
        ObjectOutputStream obj = new ObjectOutputStream(cliente.getOutputStream());
        gui.createChatScreen(obj, cliente);
        Recebedor r = new Recebedor(new ObjectInputStream(cliente.getInputStream()), gui.getTextArea(), cipherMode);
        new Thread(r).start();
    }

    public void setCipherMode(GUI gui)
    {
        if(gui.getCipherMode().equals("ECB"))
        {
            cipherMode = CipherSingleton.getInstance().getEcb();
        }
        else if(gui.getCipherMode().equals("CBC"))
        {
            cipherMode = CipherSingleton.getInstance().getCbc();
        }
        else if(gui.getCipherMode().equals("CTR"))
        {
            cipherMode = CipherSingleton.getInstance().getCtr();
        }
        else if(gui.getCipherMode().equals("RC4"))
        {
            cipherMode = CipherSingleton.getInstance().getRc4();
        }
        else if(gui.getCipherMode().equals("AES"))
        {
            cipherMode = CipherSingleton.getInstance().getAes();
        }
        else if(gui.getCipherMode().equals("DH"))
        {
            cipherMode = CipherSingleton.getInstance().getDhClient();
        }
        else if(gui.getCipherMode().equals("RSA"))
        {
            cipherMode = CipherSingleton.getInstance().getRSA();
        }
    }
}
