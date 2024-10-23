import java.io.*;
import java.net.*;
public class server {
    public static void main(String[] args){
        try{
            ServerSocket a=new ServerSocket(6666);
            Socket s=a.accept();
            DataInputStream d=new DataInputStream(s.getInputStream());
            String str=(String)d.readUTF();
            System.out.println("Client says: "+str);
        }catch(Exception e){
            System.out.println(e);
        }
    
    }
}
