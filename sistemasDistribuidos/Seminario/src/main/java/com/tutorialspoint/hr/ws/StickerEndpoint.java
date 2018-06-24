package com.tutorialspoint.hr.ws;

import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.Namespace;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.ws.server.endpoint.annotation.Endpoint;
import org.springframework.ws.server.endpoint.annotation.PayloadRoot;
import org.springframework.ws.server.endpoint.annotation.RequestPayload;
import org.springframework.ws.server.endpoint.annotation.ResponsePayload;

import com.tutorialspoint.StickerResponse;
import com.tutorialspoint.hr.service.CheckStickerService;

@Endpoint
public class StickerEndpoint {
   private static final String NAMESPACE_URI = "http://tutorialspoint.com/hr/schemas";
   private CheckStickerService checkStickerService;

   @Autowired
   public StickerEndpoint(CheckStickerService pCheckStickerService) throws JDOMException 
   {
      this.checkStickerService = pCheckStickerService;
   }

   @PayloadRoot(namespace = NAMESPACE_URI, localPart = "StickerRequest") 
   @ResponsePayload
   public StickerResponse verifyStickers(@RequestPayload Element stickerRequest) throws Exception 
   {
      Namespace namespace = Namespace.getNamespace("hr", NAMESPACE_URI);
      String myNickName = stickerRequest.getChild("myNickName", namespace).getValue();
      String friendNickName = stickerRequest.getChild("friendNickName", namespace).getValue();
      StickerResponse response = new StickerResponse();
      String res = checkStickerService.verifyTheSticker(myNickName, friendNickName);
      response.setResponse(res);
      return response;
   }
}