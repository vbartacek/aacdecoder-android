/*
** AACDecoder - Freeware Advanced Audio (AAC) Decoder for Android
** Copyright (C) 2011 Spolecne s.r.o., http://www.spoledge.com
**  
** This file is a part of AACDecoder.
**
** AACDecoder is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation; either version 3 of the License,
** or (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
package com.spoledge.aacplay;

import android.content.Context;
import android.widget.ArrayAdapter;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import java.util.ArrayList;


public class History {
    private static final int VERSION = 1;
    private static final String FILENAME = "history.dat";

    private Context ctx;
    private ArrayList<String> list;


    public History( Context ctx ) {
        this.ctx = ctx;
    }


    public ArrayAdapter<String> getArrayAdapter() {
        return new ArrayAdapter<String>( ctx, android.R.layout.simple_dropdown_item_1line, list );
    }


    public void addUrl( String url ) {
        if (!list.contains( url )) list.add( url );
    }


    public int size() {
        return list.size();
    }


    public void read() {
        list = new ArrayList<String>();

        try {
            DataInputStream dis = new DataInputStream( ctx.openFileInput( FILENAME ));

            dis.readInt(); // VERSION
            int n = dis.readInt();

            while (n-- > 0) list.add( dis.readUTF());
        }
        catch (IOException e) {}
    }


    public void write() {
        try {
            DataOutputStream dos = new DataOutputStream( ctx.openFileOutput( FILENAME, 0 ));

            dos.writeInt( VERSION );
            dos.writeInt( list.size());

            for (String url : list) dos.writeUTF( url );
        }
        catch (IOException e) {}
    }

}
