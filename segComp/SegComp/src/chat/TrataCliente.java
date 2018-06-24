package chat;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Scanner;

public class TrataCliente implements Runnable {

    private ObjectInputStream cliente;
    private Servidor servidor;

    public TrataCliente(ObjectInputStream cliente, Servidor servidor) {
        this.cliente = cliente;
        this.servidor = servidor;
    }

    public synchronized void run() {
        // quando chegar uma msg, distribui pra todos
        Message msg;
        
        try
        {
            while(true)
            {
            msg = (Message) cliente.readObject();
            if(msg != null)
            servidor.distribuiMensagem(msg);
            }
        } catch (Exception e)
        {
            try
            {
                cliente.close();
            } catch (IOException e1)
            {
                // TODO Auto-generated catch block
            }
        }
    }
}
