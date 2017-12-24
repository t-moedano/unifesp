import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {

  public static void main(String args[]) throws Exception 
  {

    ServerSocket servidor = new ServerSocket(3000);

    System.out.println("Porta 3000 aberta!");

   
    while(true)
    {
        Socket cliente = servidor.accept();
        System.out.println("Nova conexão com o cliente " +  cliente.getInetAddress().getHostAddress());
        if(!cliente.isClosed())
        {
            HttpRequest request = new HttpRequest(cliente);
  
            Thread thread = new Thread(request);
            thread.start();
        }
       
    }
   


  }

}
