
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ClientChat
{

    public static int cport = 789, sport = 2345;
    
    public static void main(String[] a) throws IOException
    {
        byte buf[] = new byte[1024];
        DatagramSocket clientsocket = new DatagramSocket(cport);
        DatagramPacket dp = new DatagramPacket(buf, buf.length);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        InetAddress ia = InetAddress.getLocalHost();
        String str2 = "";
        System.out.println("Comece a conversar");
        while(true)
        {
            String str = new String(br.readLine());
            buf = str.getBytes();
            if(str.equals("STOP"))
            {
                clientsocket.send(new DatagramPacket(buf,str.length(), ia, sport));
                break;
            }
            
            
            if(str.startsWith("ack"))
            {    
                String[] strList = str.split("ack");
                clientsocket.send(new DatagramPacket(buf, strList[0].length(), ia, sport));
            }
            else
            {
                str = "ack"+str;
                buf = str.getBytes();
                clientsocket.send(new DatagramPacket(buf, str.length(), ia, sport));
            }
            
            /*Metodo de recebimento*/
            clientsocket.receive(dp);
            str2 = new String(dp.getData(), 0,dp.getLength());
            System.out.println("Usuario 2 " + str2);
        }
    }
}