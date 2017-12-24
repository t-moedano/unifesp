package tarefa1;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {

  public static void main(String args[]) throws IOException 
  {

    ServerSocket servidor = new ServerSocket(3000);

    System.out.println("Porta 3000 aberta!");

    Socket cliente = servidor.accept();
    System.out.println("Nova conexão com o cliente " +  cliente.getInetAddress().getHostAddress()); 
    
    Scanner scanner = new Scanner(cliente.getInputStream());
    
    DataOutputStream outToClient = new DataOutputStream(cliente.getOutputStream());
    
  
     String input = scanner.nextLine();
     char letter = input.charAt(0);
      
      if(letter == 'z')
    	  outToClient.writeByte('a');
      else
      {
    	  letter++;
    	  outToClient.writeByte((char) letter);
      }
    
    
    scanner.close();
    cliente.close();
    servidor.close();

  }

}
