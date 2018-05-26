package com.tutorialspoint.hr.ws;

import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.Namespace;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.ws.server.endpoint.annotation.Endpoint;
import org.springframework.ws.server.endpoint.annotation.PayloadRoot;
import org.springframework.ws.server.endpoint.annotation.RequestPayload;
import org.springframework.ws.server.endpoint.annotation.ResponsePayload;

import com.tutorialspoint.LeaveResponse;
import com.tutorialspoint.hr.service.HumanResourceService;

@Transactional
@Endpoint
public class LeaveEndpoint {
   private static final String NAMESPACE_URI = "http://tutorialspoint.com/hr/schemas";
   private HumanResourceService humanResourceService;

   @Autowired
   public LeaveEndpoint(HumanResourceService humanResourceService) throws JDOMException 
   {
      this.humanResourceService = humanResourceService;
   }

   @PayloadRoot(namespace = NAMESPACE_URI, localPart = "LeaveRequest") 
   @ResponsePayload
   public LeaveResponse handleLeaveRequest(@RequestPayload Element leaveRequest) throws Exception 
   {
      Namespace namespace = Namespace.getNamespace("hr", NAMESPACE_URI);
      String myNickName = leaveRequest.getChild("myNickName", namespace).getValue();
      String friendNickName = leaveRequest.getChild("friendNickName", namespace).getValue();
      System.out.println("testeendpoint");
      LeaveResponse response = new LeaveResponse();
      
      String res = humanResourceService.bookLeave(myNickName, friendNickName);
      response.setTest(res);
      return response;
   }
}