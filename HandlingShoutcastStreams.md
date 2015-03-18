# Introduction #

Shoutcast streams do not return standard HTTP response which should look like:
```
HTTP/1.0 200 OK
```

but they return a special "ICY" response:
```
ICY 200 OK
```

In Android before version 4.4 (Kitkat), the Java implementation of the (Http)URLConnection was not able to parse the response code, but it was able to parse the headers and even content (returning the standard `InputStream`).

Unfortunately starting with Android 4.4 Kitkat the implementation of the HttpURLConnection has been changed, so Shoutcast streams cannot be opened using URLConnection at all.

For handling this situation we created a simple workaround solution.

# Solution #

We provide two classes:
  * [IcyURLConnection.java](https://code.google.com/p/aacdecoder-android/source/browse/trunk/decoder/src/com/spoledge/aacdecoder/IcyURLConnection.java)
  * [IcyURLStreamHandler.java](https://code.google.com/p/aacdecoder-android/source/browse/trunk/decoder/src/com/spoledge/aacdecoder/IcyURLStreamHandler.java)

The first one - IcyURLConnection - is a simple implementation of the ICY / HTTP URL connection. Maybe it should be called "HttpLikeURLConnection", because it accepts all stream responses in the format:
```
xxx yyy zzz
```

where _xxx_ can be a any word, _yyy_ is a response code and _zzz_ is a response message. Precisely using regexp:
```
^[^ ]+ \d+ .*$
```

The second one - IcyURLStreamHandler - is a utility class for creating the IcyURLConnection. The URLStreamHandler is used when Java needs to create a handler for certain protocol - like http or ftp.

So the solution is to register the IcyURLStreamHandler for URLs having a special protocol prefix. For example we want to register it for protocol prefix "icy", we can do this:
```
    try {
        java.net.URL.setURLStreamHandlerFactory( new java.net.URLStreamHandlerFactory(){
            public java.net.URLStreamHandler createURLStreamHandler( String protocol ) {
                Log.d( LOG, "Asking for stream handler for protocol: '" + protocol + "'" );
                if ("icy".equals( protocol )) return new com.spoledge.aacdecoder.IcyURLStreamHandler();
                return null;
            }
        });
    }
    catch (Throwable t) {
        Log.w( LOG, "Cannot set the ICY URLStreamHandler - maybe already set ? - " + t );
    }
```

**Important notes:**
  * The URLStreamHandlerFactory can be registered at most once for each JVM instance (see javadoc for java.net.URL).
  * When using this aacdecoder library, you **MUST** register the "icy" protocol prefix exactly as described above

Now you can open your "icy" streams:
```
    java.net.URL url = new java.net.URL( "icy://127.0.0.1:8080" );
    java.net.URLConnection conn = url.openConnection();
    ...
```

# Note about AACPlayer #

The AACPlayer assumes that the "icy" protocol is registered in the JVM. When a standard http URL is passed to AACPlayer, then it tries to open it and detects whether the response code can be parsed using the default implementation of the URLConnection. If a response code is present, then it continues and starts playing the music.

But when the response code is not present (Shoutcast stream), then it closes the stream and re-connects again using "icy" protocol prefix (replacing "http" by "icy" in the URL). If the IcyURLStreamHandler is registered, then it is selected and stream can be parsed and played.

This solution has a drawback - opening the stream twice. You can avoid it either by:
  * passing "icy" URLs to AACplayer (e.g. "icy://my.stream.server" )
  * for pre-Kitkat (Android 4.4) devices you can enable the backward compatibility option:
```
    AACPlayer player = new AACPlayer();
    player.setResponseCodeCheckEnabled( false );
```

We recommend using the first option, because the second one skips the check of the server response code.


---

