//
// Este arquivo foi gerado pela Arquitetura JavaTM para Implementação de Referência (JAXB) de Bind XML, v2.3.0 
// Consulte <a href="https://javaee.github.io/jaxb-v2/">https://javaee.github.io/jaxb-v2/</a> 
// Todas as modificações neste arquivo serão perdidas após a recompilação do esquema de origem. 
// Gerado em: 2018.05.20 às 12:04:16 PM BRT 
//


package com.tutorialspoint;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Classe Java de anonymous complex type.
 * 
 * <p>O seguinte fragmento do esquema especifica o conteúdo esperado contido dentro desta classe.
 * 
 * <pre>
 * &lt;complexType&gt;
 *   &lt;complexContent&gt;
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType"&gt;
 *       &lt;all&gt;
 *         &lt;element name="Leave" type="{http://tutorialspoint.com/hr/schemas}LeaveType"/&gt;
 *         &lt;element name="Employee" type="{http://tutorialspoint.com/hr/schemas}EmployeeType"/&gt;
 *       &lt;/all&gt;
 *     &lt;/restriction&gt;
 *   &lt;/complexContent&gt;
 * &lt;/complexType&gt;
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {

})
@XmlRootElement(name = "LeaveRequest")
public class LeaveRequest {

    @XmlElement(name = "Leave", required = true)
    protected LeaveType leave;
    @XmlElement(name = "Employee", required = true)
    protected EmployeeType employee;

    /**
     * Obtém o valor da propriedade leave.
     * 
     * @return
     *     possible object is
     *     {@link LeaveType }
     *     
     */
    public LeaveType getLeave() {
        return leave;
    }

    /**
     * Define o valor da propriedade leave.
     * 
     * @param value
     *     allowed object is
     *     {@link LeaveType }
     *     
     */
    public void setLeave(LeaveType value) {
        this.leave = value;
    }

    /**
     * Obtém o valor da propriedade employee.
     * 
     * @return
     *     possible object is
     *     {@link EmployeeType }
     *     
     */
    public EmployeeType getEmployee() {
        return employee;
    }

    /**
     * Define o valor da propriedade employee.
     * 
     * @param value
     *     allowed object is
     *     {@link EmployeeType }
     *     
     */
    public void setEmployee(EmployeeType value) {
        this.employee = value;
    }

}
