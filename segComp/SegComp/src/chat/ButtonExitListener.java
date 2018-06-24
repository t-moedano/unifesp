package chat;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.Socket;

public class ButtonExitListener implements ActionListener
{

    Socket _client;
    public ButtonExitListener(Socket pClient)
    {
        _client = pClient;
    }
    @Override
    public void actionPerformed(ActionEvent e)
    {
        try
        {
            _client.close();
        } catch (IOException e1)
        {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
    }

}
