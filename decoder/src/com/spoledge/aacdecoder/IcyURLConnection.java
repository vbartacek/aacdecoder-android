package com.spoledge.aacdecoder;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.URL;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.util.Log;


public class IcyURLConnection extends HttpURLConnection {

    private static final String LOG = "IcyURLConnection";

    protected Socket socket;
    protected OutputStream outputStream;
    protected InputStream inputStream;
    protected HashMap<String, List<String>> requestProps;
    protected HashMap<String, List<String>> headers;
    protected String responseLine;


    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////

    public IcyURLConnection( URL url ) {
        super( url );
    }


    ////////////////////////////////////////////////////////////////////////////
    // URLConnection
    ////////////////////////////////////////////////////////////////////////////

    public synchronized void connect() throws IOException {
        if (connected) throw new IOException( "Already connected" );

        socket = new Socket();
        socket.connect(
            new InetSocketAddress( url.getHost(), url.getPort() != -1 ? url.getPort() : url.getDefaultPort()),
            getConnectTimeout());

        Map<String, List<String>> requestProps = getRequestProperties();

        connected = true;

        headers = new HashMap<String, List<String>>();

        outputStream = socket.getOutputStream();
        inputStream = socket.getInputStream();

        writeLine( "GET " + ("".equals(url.getPath()) ? "/" : url.getPath()) + " HTTP/1.1" );
        writeLine( "Host: " + url.getHost());

        if (requestProps != null) {
            for (Map.Entry<String, List<String>> entry : requestProps.entrySet()) {
                for (String val : entry.getValue()) {
                    writeLine( entry.getKey() + ": " + val );
                }
            }
        }

        writeLine( "" );

        responseLine = readResponseLine();

        for (String line = readLine(); line != null && line.length() != 0;) {
            parseHeaderLine( line );
            line = readLine();
        }
    }


    @Override
    public InputStream getInputStream() {
        return inputStream;
    }


    @Override
    public OutputStream getOutputStream() {
        return outputStream;
    }


    @Override
    public String getHeaderField( String name ) {
        HashMap<String, List<String>> lmap = headers;

        if (lmap != null) {
            List<String> list = lmap.get( name );

            if (list != null && !list.isEmpty()) return list.get(0);
        }

        return null;
    }


    @Override
    public String getHeaderField( int n ) {
        return n == 0 ? responseLine : null;
    }


    @Override
    public Map<String, List<String>> getHeaderFields() {
        return headers;
    }


    @Override
    public synchronized void setRequestProperty( String key, String value ) {
        if (requestProps == null) requestProps = new HashMap<String, List<String>>();

        List<String> list = new ArrayList<String>();
        list.add( value );
        requestProps.put( key, list );
    }


    @Override
    public synchronized void addRequestProperty( String key, String value ) {
        if (requestProps == null) requestProps = new HashMap<String, List<String>>();

        List<String> list = requestProps.get( key );
        if (list == null) list = new ArrayList<String>();

        list.add( value );
        requestProps.put( key, list );
    }


    @Override
    public Map<String, List<String>> getRequestProperties() {
        return requestProps;
    }


    ////////////////////////////////////////////////////////////////////////////
    // HttpURLConnection
    ////////////////////////////////////////////////////////////////////////////

    @Override
    public synchronized void disconnect() {
        if (!connected) return;

        if (socket != null) {
            try { socket.close();} catch (IOException e){}
            socket = null;
        }

        inputStream = null;
        outputStream = null;
        headers = null;
        responseLine = null;
    }


    @Override
    public boolean usingProxy() {
        return false;
    }


    ////////////////////////////////////////////////////////////////////////////
    // Protected
    ////////////////////////////////////////////////////////////////////////////

    protected void parseHeaderLine( String line ) throws IOException {
        int len = 2;
        int n = line.indexOf( ": " );

        if (n == -1) {
            len = 1;
            n = line.indexOf( ':' );
            if (n == -1) return;
        }

        String key = line.substring( 0, n );
        String val = line.substring( n + len );

        List<String> list = headers.get( key );

        if (list != null) {
            list.add( val );
        }
        else {
            list = new ArrayList<String>();
            list.add( val );
            headers.put( key, list );
        }
    }


    protected String readResponseLine() throws IOException {
        String line = readLine();

        if (line != null) {
            int n = line.indexOf( ' ' );

            if (n != -1) {
                line = "HTTP/1.0" + line.substring( n );
            }
        }

        return line;
    }


    protected String readLine() throws IOException {
        StringBuilder sb = new StringBuilder();

        int c;
        while ((c = inputStream.read()) != -1) {
            if (c == '\r') continue;
            if (c == '\n') break;
            sb.append( (char)c );
        }

        Log.d( LOG, "IN> " + sb );

        return sb.toString();
    }


    protected void writeLine( String line ) throws IOException {
        Log.d( LOG, "OUT> " + line );
        line += '\r';
        line += '\n';
        outputStream.write( line.getBytes( "UTF-8" ));
    }

}
