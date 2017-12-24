import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.Socket;

public class EmailSender
{

    public static void sendCommand(String pCommand, OutputStream pOs) throws UnsupportedEncodingException, IOException
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
            throw new Exception(pNumberCode + "not received");
        }
    }
    
    public static void main(String[] args)  throws Exception 
    {

      Socket cliente = new Socket("172.21.209.71", 2002);
      System.out.println("O cliente se conectou ao servidor!");
         
      InputStream is = cliente.getInputStream();
      InputStreamReader isr = new InputStreamReader(is);
      BufferedReader br = new BufferedReader(isr);
      OutputStream os = cliente.getOutputStream();
      
      /*Cumprimentos do servidor*/
      readResponseAndValidate(br, "220");
      
      /*HELO* it's me*/
      sendCommand("HELO Thauany\r\n", os);
      readResponseAndValidate(br, "250");
      
      /*MAIL FROM*/
      sendCommand("MAIL FROM: <tmoedano@unifesp.br>\r\n", os);
      readResponseAndValidate(br, "250");
      
      /*RCPT TO*/
      sendCommand("RCPT TO: <postmaster@D122408>\r\n", os);
      readResponseAndValidate(br, "250");
      
      /*DATA*/
      sendCommand("DATA\r\n", os);
      readResponseAndValidate(br, "354");
      
      /*SEND MESSAGE*/
      sendCommand("Han Solo Morre (enviado do meu iPad)\r\n \r\n.\r\n", os);
      readResponseAndValidate(br, "250");
      
      /*QUIT*/
      sendCommand("quit\r\n", os);
      readResponseAndValidate(br, "221");
      
      cliente.close();
      
    }
}
