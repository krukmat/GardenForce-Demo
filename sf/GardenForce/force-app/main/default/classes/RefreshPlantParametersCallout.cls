/**
 * @description       : 
 * @author            : Matias Kruk
 * @group             : 
 * @last modified on  : 05-19-2021
 * @last modified by  : Matias Kruk
 * Modifications Log 
 * Ver   Date         Author        Modification
 * 1.0   05-19-2021   Matias Kruk   Initial Version
**/
public with sharing class RefreshPlantParametersCallout {
    @AuraEnabled(cacheable=true)
    public static String updatePlantMoist(String plant, Integer parameter) {
        Http http = new Http();
        HttpRequest request = new HttpRequest();
         
        // Provide the Named Credentials
        request.setEndpoint('http://image.krukforce.com/rest/setup?plant_id='+plant+'&moist='+String.valueOf(parameter));
        request.setMethod('GET');        
        System.debug(request.getEndpoint());
        HttpResponse response = http.send(request);
        if (response.getStatusCode() == 200) {
            return response.getBody();
        }
        return null;
    }
}