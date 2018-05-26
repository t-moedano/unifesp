//
// Este arquivo foi gerado pela Arquitetura JavaTM para Implementação de Referência (JAXB) de Bind XML, v2.3.0 
// Consulte <a href="https://javaee.github.io/jaxb-v2/">https://javaee.github.io/jaxb-v2/</a> 
// Todas as modificações neste arquivo serão perdidas após a recompilação do esquema de origem. 
// Gerado em: 2018.05.20 às 12:04:16 PM BRT 
//


package com.tutorialspoint;

import javax.xml.bind.annotation.XmlRegistry;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the com.tutorialspoint package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {


    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: com.tutorialspoint
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link LeaveRequest }
     * 
     */
    public LeaveRequest createLeaveRequest() {
        return new LeaveRequest();
    }

    /**
     * Create an instance of {@link LeaveType }
     * 
     */
    public LeaveType createLeaveType() {
        return new LeaveType();
    }

    /**
     * Create an instance of {@link EmployeeType }
     * 
     */
    public EmployeeType createEmployeeType() {
        return new EmployeeType();
    }

    /**
     * Create an instance of {@link LeaveResponse }
     * 
     */
    public LeaveResponse createLeaveResponse() {
        return new LeaveResponse();
    }

}
