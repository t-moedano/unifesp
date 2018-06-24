package chat;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.Socket;

import javax.swing.JTextField;

import cipherModes.CipherMode;

public class ButtonSendListener implements ActionListener
{

    ObjectOutputStream _client;
    JTextField _textMessage;
    String _clientName;
    CipherMode _cipherMode;
    
    public ButtonSendListener(ObjectOutputStream pClient, JTextField pTextMessage, JTextField pClientName, String pCipherMode)
    {
        _client = pClient;
        _textMessage = pTextMessage;
        _clientName = pClientName.getText();
        setCipherMode(pCipherMode);
    }
    
    public void setCipherMode(String pCipherMode)
    {
        if(pCipherMode.equals("ECB"))
        {
            _cipherMode = CipherSingleton.getInstance().getEcb();
        }
        else if(pCipherMode.equals("CBC"))
        {
            _cipherMode = CipherSingleton.getInstance().getCbc();
        }
        else if(pCipherMode.equals("CTR"))
        {
            _cipherMode = CipherSingleton.getInstance().getCtr();
        }
        else if(pCipherMode.equals("RC4"))
        {
            _cipherMode = CipherSingleton.getInstance().getRc4();
        }
        else if(pCipherMode.equals("AES"))
        {
            _cipherMode = CipherSingleton.getInstance().getAes();
        }
        else if(pCipherMode.equals("DH"))
        {
            _cipherMode = CipherSingleton.getInstance().getDhClient();
        }
        else if(pCipherMode.equals("RSA"))
        {
            _cipherMode = CipherSingleton.getInstance().getRSA();
        }
    }
    @Override
    public synchronized void actionPerformed(ActionEvent arg0)
    {
        ObjectOutputStream saida;
        try
        {
            Message msg = new Message(_cipherMode.makeCipher(_textMessage.getText()), _cipherMode);
            _client.reset();
            System.out.println("printando objeto pelo cliente");
            _client.writeObject(msg);
           
            _textMessage.setText("");
        } catch (IOException e)
        {
            e.printStackTrace();
        }
               
        
    }

}
