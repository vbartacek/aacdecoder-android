package com.spoledge.aacdecoder;

import java.io.IOException;

import java.net.URL;
import java.net.URLConnection;
import java.net.URLStreamHandler;


public class IcyURLStreamHandler extends URLStreamHandler {

    ////////////////////////////////////////////////////////////////////////////
    // URLStreamHandler
    ////////////////////////////////////////////////////////////////////////////

    @Override
    protected int getDefaultPort() {
        return 80;
    }


    @Override
    protected URLConnection openConnection( URL url ) throws IOException {
        return new IcyURLConnection( url );
    }
    
}
