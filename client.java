import java.io.*;
import java.net.*;
import java.util.*;
public class client{
    public static void main(String[] args){
        try{
            Socket s=new Socket("localhost",6666);
            
            DataOutputStream dout=new DataOutputStream(s.getOutputStream());
            Scanner a=new Scanner(System.in);
            String str=a.nextLine();
            dout.writeUTF(str);
            dout.flush();
            System.out.println("Message Sent");
            dout.close();
            s.close();
    }catch(Exception e){
        System.out.println(e);

    }
}
}