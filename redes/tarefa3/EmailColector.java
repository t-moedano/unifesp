

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.Socket;

public class EmailColector
{

    public static void sendCommand(String pCommand, OutputStream pOs) throws Exception
    {
        System.out.println(pCommand);
        pOs.write(pCommand.getBytes("US-ASCII"));
    }
    public static void readResponseAndValidate(BufferedReader pBr, String pNumberCode) throws Exception
    {
        String response = pBr.readLine();
        System.out.println(response);
        if(!response.startsWith(pNumberCode))
        {
            throw new Exception("error");
        }
    }
    
    public static void retrieveMessage(BufferedReader pBr, OutputStream pOs) throws Exception
    {
        String headerLine = null;
        while((headerLine = pBr.readLine()).length() != 0) 
        {
            System.out.println(headerLine);
        }
        
        sendCommand("\r\n", pOs);
        String message = null;
        while((message = pBr.readLine()).length() != 1) 
        {
            System.out.println(message);
        }
    }
    
    public static void main(String[] args)  throws Exception 
    {

      Socket cliente = new Socket("172.21.209.71", 2001);
      System.out.println("O cliente se conectou ao servidor!");
         
      InputStream is = cliente.getInputStream();
      InputStreamReader isr = new InputStreamReader(is);
      BufferedReader br = new BufferedReader(isr);
      OutputStream os = cliente.getOutputStream();
      final String POP3_MESSAGE = "+OK";
      
      /*Cumprimentos do servidor*/
      readResponseAndValidate(br, POP3_MESSAGE);
      
      /*user*/
      sendCommand("user postmaster \r\n", os);
      readResponseAndValidate(br, POP3_MESSAGE);
      
      /*password*/
      sendCommand("pass postmaster\r\n", os);
      readResponseAndValidate(br, POP3_MESSAGE);
      
      /*retrieve*/
      sendCommand("retr 150\r\n", os);
      readResponseAndValidate(br, POP3_MESSAGE);
     
      retrieveMessage(br, os);
     
      cliente.close();
      
    }
}
