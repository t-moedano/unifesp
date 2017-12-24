package tarefa1;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client 
{

   public static void main(String[] args)  throws UnknownHostException, IOException 
   {

     Socket cliente = new Socket("127.0.0.1", 3000);
     System.out.println("O cliente se conectou ao servidor!");
    	
     DataOutputStream outToServer = new DataOutputStream(cliente.getOutputStream());
     BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
     
     BufferedReader inFromServer = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
     
     String sentence = inFromUser.readLine();
     outToServer.writeBytes(sentence + '\n');
     String modifiedSentence = inFromServer.readLine();
     System.out.println("Server: " + modifiedSentence);
     
     cliente.close();
   }

 }
