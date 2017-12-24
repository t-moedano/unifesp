import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.util.StringTokenizer;

public class HttpRequest implements Runnable
{

    Socket client;
    final static String CRLF = "\r\n";
    
    public HttpRequest(Socket client)
    {
        this.client = client;
    }
   
    private static void sendBytes(FileInputStream fis, OutputStream os) throws Exception
    {
        
        byte[] buffer = new byte[1024];
        int bytes = 0;
        while((bytes = fis.read(buffer)) != -1 ) 
        {
            os.write(buffer, 0, bytes);
        }
   }
    
    private static String contentType(String fileName)
    {
        if(fileName.endsWith(".htm") || fileName.endsWith(".html")) 
        {
            return "text/html";
        }
        if(fileName.endsWith(".gif")) 
        {
            return "image/gif";
        }
        if(fileName.endsWith(".jpeg")) 
        {
            return "image/jpeg";
        }
    return "application/octet-stream";
    }
    
    public void processRequest() throws Exception
    {
        DataOutputStream os = new DataOutputStream( client.getOutputStream());
        BufferedReader br = new BufferedReader(new InputStreamReader(client.getInputStream()));
        String requestLine = br.readLine();
        System.out.println(requestLine);
        String headerLine = null;
        while((headerLine = br.readLine()).length() != 0) 
        {
            System.out.println(headerLine);
        }
        
        StringTokenizer tokens = new StringTokenizer(requestLine);
        tokens.nextToken(); 
        String fileName = tokens.nextToken();
        
        
        FileInputStream fis = null;
        Boolean fileExists = true;
        try 
        {
            fis = new FileInputStream(fileName);
        } catch (FileNotFoundException e) 
        {
            fileExists = false;
        }
        
        
        if (fileExists) 
        {
            os.writeBytes("HTTP/1.1 200 OK\n"
                    +"Content-Type: " + contentType(fileName) + "\n"
                    +"\n");
            sendBytes(fis, os);
            fis.close();
            
        } 
        else 
        {
            os.writeBytes("HTTP/1.1 200 OK\n"
                    +"Content-Type: text/html\n"
                    +"\n"
                    + "<html><h1> 404 not found </h1></html>");
        }
        
        
        os.close();
        br.close();
        client.close();
    }

    @Override
    public void run()
    {
        try
        {
            processRequest();
        } catch (Exception e)
        {
            System.out.println(e);
        }
    }

}
