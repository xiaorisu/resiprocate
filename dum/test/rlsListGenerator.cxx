
#include "resiprocate/MultipartMixedContents.hxx"
#include "resiprocate/GenericContents.hxx"
#include "resiprocate/Rlmi.hxx"
#include "resiprocate/Pidf.hxx"
#include "resiprocate/Pkcs7Contents.hxx"
#include "resiprocate/MultipartSignedContents.hxx"
#include "resiprocate/MultipartRelatedContents.hxx"
#include "resiprocate/SipMessage.hxx"
#include "resiprocate/test/TestSupport.hxx"
#include "rutil/ParseBuffer.hxx"
#include "rutil/CountStream.hxx"


#include <iostream>
#include <fstream>
#include <memory>


using namespace resip;
using namespace std;

int 
main (int argc, char** argv)
{
   {
      const Data txt(
         "--50UBfW7LSCVLtggUPe5z\r\n"
         "Content-Transfer-Encoding: binary\r\n"
         "Content-ID: <nXYxAE@pres.example.com>\r\n"
         "Content-Type: application/rlmi+xml;charset=\"UTF-8\"\r\n"
         "\r\n"
         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
         "<list xmlns=\"urn:ietf:params:xml:ns:rmli\"\r\n"
         "      uri=\"sip:adam-friends@pres.example.com\" version=\"1\"\r\n"
         "      name=\"Buddy List at COM\" fullState=\"true\">\r\n"
         "  <resource uri=\"sip:bob@example.com\" name=\"Bob Smith\">\r\n"
         "    <instance id=\"juwigmtboe\" state=\"active\"\r\n"
         "              cid=\"bUZBsM@pres.example.com\"/>\r\n"
         "  </resource>\r\n"
         "  <resource uri=\"sip:dave@example.com\" name=\"Dave Jones\">\r\n"
         "    <instance id=\"hqzsuxtfyq\" state=\"active\"\r\n"
         "              cid=\"ZvSvkz@pres.example.com\"/>\r\n"
         "  </resource>\r\n"
         "  <resource uri=\"sip:ed@example.net\" name=\"Ed at NET\" />\r\n"
         "  <resource uri=\"sip:adam-friends@example.org\"\r\n"
         "            name=\"My Friends at ORG\" />\r\n"
         "</list>\r\n"
         "\r\n"
         "--50UBfW7LSCVLtggUPe5z\r\n"
         "Content-Transfer-Encoding: binary\r\n"
         "Content-ID: <bUZBsM@pres.example.com>\r\n"
         "Content-Type: application/pidf+xml;charset=\"UTF-8\"\r\n"
         "\r\n"
         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
         "<presence xmlns=\"urn:ietf:params:xml:ns:pidf\"\r\n"
         "    entity=\"sip:bob@example.com\">\r\n"
         "  <tuple id=\"sg89ae\">\r\n"
         "    <status>\r\n"
         "      <basic>open</basic>\r\n"
         "    </status>\r\n"
         "    <contact priority=\"1.0\">sip:bob@example.com</contact>\r\n"
         "  </tuple>\r\n"
         "</presence>\r\n"
         "\r\n"
         "--50UBfW7LSCVLtggUPe5z\r\n"
         "Content-Transfer-Encoding: binary\r\n"
         "Content-ID: <ZvSvkz@pres.example.com>\r\n"
         "Content-Type: application/pidf+xml;charset=\"UTF-8\"\r\n"
         "\r\n"
         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
         "<presence xmlns=\"urn:ietf:params:xml:ns:pidf\"\r\n"
         "    entity=\"sip:dave@example.com\">\r\n"
         "  <tuple id=\"slie74\">\r\n"
         "    <status>\r\n"
         "      <basic>closed</basic>\r\n"
         "    </status>\r\n"
         "  </tuple>\r\n"
         "</presence>\r\n"
         "\r\n"
         "--50UBfW7LSCVLtggUPe5z--\r\n"
         );

      ofstream outfile;
      outfile.open("c:\\fullHeaders.bytes", ofstream::out | ofstream::trunc | ofstream::binary);
      
      Mime mpr("multipart", "related");
      mpr.param(p_type) = "application/rlmi+xml";
      mpr.param(p_boundary) = "50UBfW7LSCVLtggUPe5z";      
   
      HeaderFieldValue hfv(txt.data(), txt.size());
      MultipartRelatedContents orig(&hfv, mpr);
      
      size_t size;
      {
         CountStream cs(size);
         orig.encode(cs);
      }
      outfile << "Content-Length: " << size << "\r\n";
      orig.encodeHeaders(outfile);      
      orig.encode(outfile);      
      outfile.close();
   }
   
   return 0;
}

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
