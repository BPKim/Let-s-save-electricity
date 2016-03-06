
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Socket server on standard Java
 *
 * @author Mike
 */
public class MainServer {

	public static void main(String[] args) {

		try {

			int portNumber = 5568;

			System.out.println("Starting Java Socket Server ...");
			ServerSocket aServerSocket = new ServerSocket(portNumber);
			System.out.println("Listening at port " + portNumber + " ...");


			Socket aSocket = aServerSocket.accept();
			InetAddress clientHost = aSocket.getLocalAddress();
			int clientPort = aSocket.getPort();
			System.out.println("A client connected. host : " + clientHost + ", port : " + clientPort);
			PrintWriter pw = new PrintWriter (new OutputStreamWriter(aSocket.getOutputStream()));
			BufferedReader br =new BufferedReader(new InputStreamReader(aSocket.getInputStream()));
			while(true) 
			{
				String obj = br.readLine();
				System.out.println("Input : " + obj);
				//pw.println(obj);
				//pw.flush();
			}

		} catch(Exception ex) {
			ex.printStackTrace();
		}
	}
}
