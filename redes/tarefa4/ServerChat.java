
import java.io.*;
import java.net.*;

class ServerChat
{

    public static int cport = 789, sport = 2345;

    public static void main(String[] a) throws IOException
    {
        
        DatagramSocket serversocket = new DatagramSocket(sport);
        byte buf[] = new byte[1024];
        DatagramPacket dp = new DatagramPacket(buf, buf.length);
        BufferedReader dis = new BufferedReader(new InputStreamReader(System.in));
        InetAddress ia = InetAddress.getLocalHost();
        while (true)
        {
            serversocket.receive(dp);
            String str = new String(dp.getData(), 0, dp.getLength());
            if (str.equals("STOP"))
            {
                break;
            }
            System.out.println("Usuario 1: " + str);
            String str1 = new String(dis.readLine());
            
            if(str.startsWith("ack"))
            {
                String[] strList = str1.split("ack");
                buf = str1.getBytes();
                serversocket.send(new DatagramPacket(buf, strList[0].length(), ia, cport));
            }
            else
            {
                str1 = "ack" + str1;
                buf = str1.getBytes();
                serversocket.send(new DatagramPacket(buf, str1.length(), ia, cport));
            }
        }
    }
}