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

#include <jni.h>
/* Header for class com_spoledge_aacdecoder_Decoder */

#ifndef _Included_com_spoledge_aacdecoder_Decoder
#define _Included_com_spoledge_aacdecoder_Decoder

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeStart
 * Signature: (ILcom/spoledge/aacdecoder/BufferReader;Lcom/spoledge/aacdecoder/Decoder/Info;)I
 */
JNIEXPORT jint JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeStart
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeDecode
 * Signature: (I[SI)I
 */
JNIEXPORT jint JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeDecode
  (JNIEnv *, jobject, jint, jshortArray, jint);

/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeStop
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeStop
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_spoledge_aacdecoder_Decoder
 * Method:    nativeDecoderGetByName
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_spoledge_aacdecoder_Decoder_nativeDecoderGetByName
  (JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif
